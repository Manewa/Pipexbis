/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:59:59 by namalier          #+#    #+#             */
/*   Updated: 2024/10/01 20:01:33 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	init_no_path(t_data *data, char **argv)
{
	data->path = malloc(3 * sizeof(char *));
	if (!data->path)
		return ;
	data->path[0] = ft_strdup(argv[2]);
	if (!data->path[0])
		return ;
	data->path[1] = ft_strdup(argv[3]);
	if (!data->path[1])
		return ;
	data->path[2] = NULL;
	if (!data->path[2])
		return ;
}

void	get_path(char **envp, t_data *data)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!envp)
		return ;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
	{
		data->path = NULL;
		return ;
	}
	str = ft_strdup(&envp[i][5]);
	if (!str)
		exit(2);
	data->path = ft_split(str, ':');
	free (str);
	if (!(data->path))
		exit(2);
}
