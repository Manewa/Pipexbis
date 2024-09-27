#include "../../includes/pipex.h"

void	init_output(t_data *data, list *cmd, int *pipefd, int output_fd)
{
	if (dup2(output_fd, STDOUT_FILENO) < 0)
	{
		ft_printf("Error : %s\n", strerror(errno));
		ft_free_both(data, cmd, pipefd);
	}
	if (pipefd[1] != output_fd)
		close(pipefd[1]);
}

void	init_input(t_data *data, list *cmd, int *pipefd)
{
	if (dup2(data->input_fd, STDIN_FILENO) < 0)
	{
		ft_printf("Error : %s\n", strerror(errno));
		ft_free_both(data, cmd, pipefd);
	}
	close(data->input_fd);
	close(pipefd[0]);
}
