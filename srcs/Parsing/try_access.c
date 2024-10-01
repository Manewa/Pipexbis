/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:58:36 by namalier          #+#    #+#             */
/*   Updated: 2024/10/01 19:58:57 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

char	*try_access(t_data *data, t_cmd *cmd, char *cmd_no_flag)
{
	size_t	i;

	i = 0;
	while (data->path[i])
	{
		cmd->pathcmd = ft_cpypath(cmd_no_flag, data->path[i]);
		if (!(cmd->pathcmd))
			ft_free_both(data, cmd, NULL, 0);
		if (access(cmd->pathcmd, F_OK | X_OK) == -1)
		{
			free(cmd->pathcmd);
			i++;
		}
		else
			return (cmd->pathcmd);
	}
	return (NULL);
}
