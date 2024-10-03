/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:18:10 by namalier          #+#    #+#             */
/*   Updated: 2024/10/03 18:17:45 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_free_error(t_data *data)
{
	if (data->path)
		ft_free_doubletab(data->path);
	write(2, "Error\n", 6);
	if (errno)
	{
		write (2, strerror(errno), ft_strlen(strerror(errno)));
		write (2, "\n", 1);
	}
	else
		write (2, "Wrong args or malloc\n", 21);
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
	if (errno && end == 0)
	{
		write(2, "Error\n", 6);
		write (2, strerror(errno), ft_strlen(strerror(errno)));
		write (2, "\n", 1);
	}
	if (end == 0)
		exit(2);
}
