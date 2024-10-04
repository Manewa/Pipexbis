/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:31:09 by namalier          #+#    #+#             */
/*   Updated: 2024/10/04 16:00:58 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	tmp_exit(int *exit_status, int status)
{
	int	tmp;

	if (WIFEXITED(status))
	{
		tmp = WEXITSTATUS(status);
		if (tmp != 0)
			*exit_status = WEXITSTATUS(status);
	}
}

int	max_arg_double(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_cmd	*head;
	int		status;
	int		exit_status;

	exit_status = 0;
	if (argc != 5)
		return (ft_printf("Error\nInvalid args\n"), 0);
	get_path(envp, &data);
	if (!data.path)
		init_no_path(&data, argv);
	access_input(&data, argv[1]);
	access_output(&data, argv[max_arg_double(argv) - 1]);
	access_cmd(&data, argv, &head);
	fork_n_pipe(&data, &head);
	while (waitpid(-1, &status, 0) > 0)
		tmp_exit(&exit_status, status);
	ft_free_both(&data, head, NULL, 1);
	if (exit_status)
		exit(exit_status);
	return (0);
}
