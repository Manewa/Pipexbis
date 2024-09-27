#include "../../includes/pipex.h"

void	access_output(t_data *data, char *argv)
{
	if (access(argv, F_OK) == 0)
	{
		if (access(argv, W_OK) != 0)
			ft_free_error(data);
	}
	data->output_fd = open(argv, O_WRONLY | O_TRUNC | O_CREAT, 0664);
}

void	access_input(t_data *data, char *argv)
{
	if (access(argv, F_OK | R_OK) == 0)
		data->input_fd = open(argv, O_RDONLY);
	else
		ft_free_error(data);
	if (data->input_fd == -1)
		ft_free_error(data);
}
