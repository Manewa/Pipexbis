/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:18:10 by namalier          #+#    #+#             */
/*   Updated: 2024/09/27 19:22:26 by natgomali        ###   ########.fr       */
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

void	ft_free_both(t_data *data, list *cmd, int *pipefd)
{
	if (pipefd)
		ft_free_fds(pipefd, data);
	if (data)
		ft_free_doubletab(data->path);
	if (cmd)
		pipex_lstfree(&cmd);
	exit(2);
}
