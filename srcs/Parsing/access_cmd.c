/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:04:52 by namalier          #+#    #+#             */
/*   Updated: 2024/10/03 19:01:30 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

t_cmd	*full_path_cmd(t_cmd *cmd, char **cmd_n_flags)
{
	char	**only_cmd;
	size_t	i;

	cmd->pathcmd = ft_strdup(cmd_n_flags[0]);
	if (!(cmd->pathcmd))
		return (NULL);
	only_cmd = ft_split(cmd->pathcmd, '/');
	if (!only_cmd)
		return (NULL);
	if (!only_cmd[0])
		return (free(only_cmd), NULL);
	i = max_arg_double(only_cmd) - 1;
	cmd->cmd_flag[0] = ft_strdup(only_cmd[i]);
	if (!(cmd->cmd_flag[0]))
		return (NULL);
	i = 1;
	while (cmd_n_flags[i])
	{
		cmd->cmd_flag[i] = ft_strdup(cmd_n_flags[i]);
		if (!(cmd->cmd_flag[i]))
			return (NULL);
		i++;
	}
	ft_free_doubletab(only_cmd);
	return (cmd);
}

char	*ft_cpypath(char *argv, char *path)
{
	size_t	i;
	size_t	j;
	char	*cpath;

	i = 0;
	j = 0;
	cpath = malloc((ft_strlen(argv) + ft_strlen(path) + 2) * sizeof(char));
	if (!cpath)
		return (NULL);
	while (path[i])
	{
		cpath[i] = path[i];
		i++;
	}
	cpath[i++] = '/';
	while (argv[j])
		cpath[i++] = argv[j++];
	cpath[i] = '\0';
	return (cpath);
}

int	name_only_cmd(t_data *data, t_cmd *cmd, char **cmd_n_flags)
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

t_cmd	*create_node(char *argv, t_data *data)
{
	t_cmd	*node;
	char	**cmd_n_flags;

	cmd_n_flags = check_cmd_n_flags(argv);
	if (!cmd_n_flags)
		return (NULL);
	node = malloc(sizeof(*node));
	if (!node)
		return (ft_free_doubletab(cmd_n_flags));
	node->next = NULL;
	node->cmd_flag = malloc((max_arg_double(cmd_n_flags) + 1) * sizeof(char *));
	if (!(node->cmd_flag))
		return (ft_free_doubletab(cmd_n_flags));
	node->cmd_flag[max_arg_double(cmd_n_flags)] = NULL;
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

void	access_cmd(t_data *data, char **argv, t_cmd **head)
{
	size_t	i;
	t_cmd	*add;

	i = 3;
	free(*head);
	(*head) = create_node(argv[2], data);
	if (!(*head))
	{
		ft_free_fds(NULL, data);
		ft_free_error(data);
	}
	while (argv[i + 1])
	{
		add = create_node(argv[i], data);
		if (!add)
			ft_free_both(data, (*head), NULL, 0);
		add->head = *head;
		pipex_lstadd_back(head, add);
		i++;
	}
}
