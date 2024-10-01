/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:14:39 by namalier          #+#    #+#             */
/*   Updated: 2024/10/01 18:58:03 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	parent_process(int *pipefd)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

void	last_arg(t_data *data, t_cmd *cmd, int *pipefd)
{
	close(data->input_fd);
	close(pipefd[0]);
	init_output(data, cmd, pipefd, data->output_fd);
	close(data->output_fd);
}

void	first_arg(t_data *data, t_cmd *cmd, int *pipefd)
{
	init_input(data, cmd, pipefd);
	init_output(data, cmd, pipefd, pipefd[1]);
	close(data->input_fd);
	close(data->output_fd);
}

void	child_process(t_data *data, t_cmd *cmd, int *pipefd, char **envp)
{
	if (cmd->pathcmd && access(cmd->pathcmd, F_OK | X_OK) == 0)
	{
		if (cmd->next)
			first_arg(data, cmd, pipefd);
		else
			last_arg(data, cmd, pipefd);
		if (execve(cmd->pathcmd, cmd->cmd_flag, envp) == -1)
			ft_free_both(data, cmd, NULL, 0);
	}
	else if (cmd->next)
	{	
		first_arg(data, cmd, pipefd);
		ft_free_both(data, cmd, NULL, 0);
	}
	else
	{
		last_arg(data, cmd, pipefd);
		ft_free_both(data, cmd->head, NULL, 0);
	}
}

void	fork_n_pipe(t_data *data, t_cmd **cmd, char **envp)
{
	int		pipefd[2];
	int		pid;
	t_cmd	*tmp;

	pid = 1;
	tmp = *cmd;
	while ((*cmd))
	{
		if (pipe(pipefd) == -1)
			ft_free_both(data, *cmd, NULL, 0);
		pid = fork();
		if (pid < 0)
			ft_free_both(data, *cmd, pipefd, 0);
		else if (pid == 0)
		{
			child_process(data, *cmd, pipefd, envp);
		}
		else
			parent_process(pipefd);
		(*cmd) = (*cmd)->next;
	}
	*cmd = tmp;
}
