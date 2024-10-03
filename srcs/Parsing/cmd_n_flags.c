/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_n_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:44:38 by namalier          #+#    #+#             */
/*   Updated: 2024/10/03 19:17:29 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	only_a(char *cmd_n_flags)
{
	size_t	i;

	i = 0;
	while (cmd_n_flags[i] == '/')
		i++;
	if (cmd_n_flags[i])
		return (0);
	else
		return (1);
}

char	**check_cmd_n_flags(char *argv)
{
	char	**cmd_n_flags;

	cmd_n_flags = ft_split(argv, ' ');
	if (!cmd_n_flags)
		return (NULL);
	if (!cmd_n_flags[0] || only_a(cmd_n_flags[0]))
	{
		ft_free_doubletab(cmd_n_flags);
		cmd_n_flags = malloc(2 * sizeof(char *));
		cmd_n_flags[0] = ft_strdup("a");
		cmd_n_flags[1] = NULL;
	}
	return (cmd_n_flags);
}
