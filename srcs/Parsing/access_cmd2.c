/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_cmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:04:52 by namalier          #+#    #+#             */
/*   Updated: 2024/09/27 22:14:13 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

// Full Path et name_only permettent de faire un char ** avec 
// 1) le path + nom sur pathcmd
// 2) seulement le nom et les flags ensuite sur cmd_flag
//
// Full path requiert un path entier en argument (/usr/bin/ls)
// name only ne prend que le "ls"
//
// pathcmd et cmd_flag sont donc parse pour etre utilisables avec execve
// Pour l'instant, seule la premiere node de la liste (premiere commande) ne peut etre recupere
// Il faut faire la meme avec les suivantes (Fait depuis le while dans access_cmd)
//
// AUCUNE ERREUR N'EST VRAIMENT BIEN GERE NI LEAKS NI MOTS D'ERREUR

list	*full_path_cmd(list *cmd, char **cmd_n_flags)
{
	char	**only_cmd;
	size_t	i;

	cmd->pathcmd = ft_strdup(cmd_n_flags[0]);
	if (!(cmd->pathcmd))
		return (ft_free_doubletab(cmd_n_flags));
	only_cmd = ft_split(cmd->pathcmd, '/');
	if (!only_cmd)
		return (ft_free_doubletab(cmd_n_flags));
	i = max_arg_double(only_cmd) - 1;
	cmd->cmd_flag[0] = ft_strdup(only_cmd[i]);
	if (!(cmd->cmd_flag[0]))
		return (ft_free_doubletab(cmd_n_flags));
	i = 1;
	while (cmd_n_flags[i])
	{
		cmd->cmd_flag[i] = ft_strdup(cmd_n_flags[i]);
		if (!(cmd->cmd_flag[i]))
			return (ft_free_doubletab(cmd_n_flags));
		i++;
	}
	ft_free_doubletab(only_cmd);
	return (cmd);
}

char	*ft_cpypath(char *argv, char *path)
{
	size_t	i;
	size_t	j;
	char	*Cpath;

	i = 0;
	j = 0;
	Cpath = malloc((ft_strlen(argv) + ft_strlen(path) + 2) * sizeof(char));
	if (!Cpath)
		return(NULL);
	while (path[i])
	{
		Cpath[i] = path[i];
		i++;
	}
	Cpath[i++] = '/';
	while (argv[j])
		Cpath[i++] = argv[j++];
	Cpath[i] = '\0';
	return (Cpath);
}

char	*try_access(t_data *data, list *cmd, char *cmd_no_flag)
{
	size_t	i;

	i = 0;
	while (data->path[i])
	{
		cmd->pathcmd = ft_cpypath(cmd_no_flag, data->path[i]);
		if (!(cmd->pathcmd))
			ft_free_both(data, cmd, NULL);
		if (access(cmd->pathcmd, F_OK | X_OK) == -1)
		{
			free(cmd->pathcmd);
			i++;
		}
		else
			return (cmd->pathcmd);
	}
	ft_printf("Error\nCommand not found");
	exit(2);
}

int	name_only_cmd(t_data *data, list *cmd, char **cmd_n_flags)
{
	size_t	i;

	i = 0;
	while (cmd_n_flags[i])
	{
		cmd->cmd_flag[i] = ft_strdup(cmd_n_flags[i]);
		if (!(cmd->cmd_flag[i]))
			return (0);
		i++;
	}
	cmd->pathcmd = try_access(data, cmd, cmd_n_flags[0]);
	return (1);
}

list	*create_node(char *argv, t_data *data)
{
	list	*node;
	char	**cmd_n_flags;

	cmd_n_flags = ft_split(argv, ' ');
	if (!cmd_n_flags)
		return (NULL);
	node = malloc(sizeof(*node));
	if (!node)
		return (ft_free_doubletab(cmd_n_flags));
	node->next = NULL;
	node->cmd_flag = malloc((max_arg_double(cmd_n_flags) + 1) * sizeof(char *));
	node->cmd_flag[max_arg_double(cmd_n_flags)] = NULL;
	if (!(node->cmd_flag))
		return (ft_free_doubletab(cmd_n_flags));
	if (ft_strchr(cmd_n_flags[0], '/'))
	{
		if (!(full_path_cmd(node, cmd_n_flags)))
			return (ft_free_doubletab(cmd_n_flags));
	}
	else
		if (name_only_cmd(data, node, cmd_n_flags) == 0)
			return (ft_free_doubletab(cmd_n_flags));
	ft_free_doubletab(cmd_n_flags);
	return (node);	
}

void	access_cmd(t_data *data, char **argv, list **head)
{
	size_t	i;
	list	*add;

	i = 3;
	(*head) = create_node(argv[2], data);
	if (!(*head))
		ft_free_error(data);
	while (argv[i + 1])
	{
		add = create_node(argv[i], data);
		if (!add)
			ft_free_both(data, (*head), NULL);
		pipex_lstadd_back(head, add);
		i++;
	}
}
