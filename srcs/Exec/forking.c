#include "../../includes/pipex.h"

void	parent_process(int *pipefd)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

void	child_process(t_data *data, list *cmd, int *pipefd, char **envp)
{
	if (access(cmd->pathcmd, F_OK | X_OK) == 0)
	{
		if (cmd->next)
		{
			init_input(data, cmd, pipefd);
			init_output(data, cmd, pipefd, pipefd[1]);
		}
		else
			init_output(data, cmd, pipefd, data->output_fd);
		if (execve(cmd->pathcmd, cmd->cmd_flag, envp) == -1)
		{
			ft_printf("Error : %s\n", strerror(errno));
			ft_free_both(data, cmd, pipefd);
		}
	}
	else
		ft_printf("Error : %s\n", strerror(errno));
}

void	fork_n_pipe(t_data *data, list **cmd, char **envp)
{
	int	pipefd[2];
	int	pid;

	pid = 1;
	while ((*cmd))
	{
		if (pipe(pipefd) == -1)
			ft_free_both(data, *cmd, NULL);
		pid = fork();
		if (pid < 0)
			ft_free_both(data, *cmd, pipefd);
		else if (pid == 0)
		{
			child_process(data, *cmd, pipefd, envp);
		}
		else
		{
			parent_process(pipefd);
		}
		(*cmd) = (*cmd)->next;
	}
}

/*
   void	fork_n_pipe(t_data *data, list *cmd, char **envp)
   {
   int		pipefd[2];
   int		pid;
   int		pid2;

   pid = 1;
   pid2 = 1;
   if (pipe(pipefd) == -1)
   ft_free_both(data, cmd, NULL);
   pid = fork();
   if (pid < 0)
   ft_free_both(data, cmd, pipefd);
   else if (pid != 0)
   {
   pid2 = fork();
   if (pid2 < 0)
   ft_free_both(data, cmd, pipefd);
   }
   if (pid2 == 0)
   {
   if (access(cmd->pathcmd, F_OK | X_OK) == 0)
   {
   first_process(data, cmd, pipefd);
   last_process(data, cmd, pipefd, pipefd[1]);
   printf("Pouet\n");
   }
   else
   ft_printf("%s\n", strerror(errno));
   }
   if (pid == 0)
   {
   cmd = cmd->next;
   if (access(cmd->pathcmd, F_OK | X_OK) == 0)
   {
   printf("|Pouet|\n");
   close (pipefd[0]);
   close(data->input_fd);
   last_process(data, cmd, pipefd, data->output_fd);
   }
   else
   ft_printf("Error : %s\n", strerror(errno));
   }
   if ((pid == 0 || pid2 == 0) && access(cmd->pathcmd, F_OK | X_OK) == 0)
   {
   if (execve(cmd->pathcmd, cmd->cmd_flag, envp) == -1)
   {
   ft_printf("Error : %s\n", strerror(errno));
   ft_free_both(data, cmd, pipefd);
   }
   else
   ft_printf("Error : %s\n", strerror(errno));
   }
   ft_free_fds(pipefd, data);
//	while (wait(NULL) > 0)
//		;
//	wait(&pid2);
//	wait(&pid);
ft_free_both(data, cmd, NULL);
}*/
