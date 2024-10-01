/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:18:10 by namalier          #+#    #+#             */
/*   Updated: 2024/10/01 18:24:08 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_free_error(t_data *data)
{
	if (data->path)
		ft_free_doubletab(data->path);
	ft_printf("Error\n");
	exit(2);
}

void	ft_free_fds(int *pipefd, t_data *data)
{
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	close(data->input_fd);
	close(data->output_fd);
}

void	ft_free_both(t_data *data, t_cmd *cmd, int *pipefd, int end)
{
	if (data->input_fd)
		ft_free_fds(pipefd, data);
	if (data->path)
		ft_free_doubletab(data->path);
	pipex_lstfree(&cmd);
	if (end == 0)
		exit(2);
}
