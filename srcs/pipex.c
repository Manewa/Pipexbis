/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:31:09 by namalier          #+#    #+#             */
/*   Updated: 2024/10/01 19:58:00 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

	if (argc != 5)
		return (ft_printf("Error\nInvalid args\n"), 0);
	get_path(envp, &data);
	if (!data.path)
		init_no_path(&data, argv);
	access_input(&data, argv[1]);
	access_output(&data, argv[max_arg_double(argv) - 1]);
	head = malloc(sizeof(*head));
	if (!head)
	{
		ft_free_fds(NULL, &data);
		ft_free_error(&data);
	}
	access_cmd(&data, argv, &head);
	fork_n_pipe(&data, &head);
	while (wait(NULL) > 0)
		;
	ft_free_both(&data, head, NULL, 1);
	return (0);
}
