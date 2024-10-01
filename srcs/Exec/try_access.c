/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:14:13 by namalier          #+#    #+#             */
/*   Updated: 2024/10/01 18:59:14 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	init_output(t_data *data, t_cmd *cmd, int *pipefd, int output_fd)
{
	if (dup2(output_fd, STDOUT_FILENO) < 0)
	{
		ft_printf("Error : %s\n", strerror(errno));
		ft_free_both(data, cmd, pipefd, 0);
	}
	close(pipefd[1]);
}

void	init_input(t_data *data, t_cmd *cmd, int *pipefd)
{
	if (dup2(data->input_fd, STDIN_FILENO) < 0)
	{
		ft_printf("Error : %s\n", strerror(errno));
		ft_free_both(data, cmd, pipefd, 0);
	}
	close(pipefd[0]);
}
