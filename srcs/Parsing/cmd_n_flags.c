/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_n_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:44:38 by namalier          #+#    #+#             */
/*   Updated: 2024/10/02 16:08:17 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

char	**check_cmd_n_flags(char *argv)
{
	char	**cmd_n_flags;

	cmd_n_flags = ft_split(argv, ' ');
	if (!cmd_n_flags)
		return (NULL);
	if (!cmd_n_flags[0])
	{
		free(cmd_n_flags);
		return (NULL);
	}
	return (cmd_n_flags);
}
