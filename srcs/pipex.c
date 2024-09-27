/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:31:09 by namalier          #+#    #+#             */
/*   Updated: 2024/09/27 22:47:23 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_path(char **envp, t_data *data)
{
	size_t	i;
	char	*str;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		exit (2);
	str = ft_strdup(&envp[i][5]);
	if (!str)
		exit(2);
	data->path = ft_split(str, ':');
	free (str);
	if (!(data->path))
		exit(2);
}

int	max_arg_double(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int main(int argc, char **argv, char** envp)
{
	t_data	data;
	list	*head;


	if (argc != 5)
		return (ft_printf("Error\nNot 5 args"), 0);
	head = malloc(sizeof(*head));
	if (!head)
		return (1);
	get_path(envp, &data);
	access_input(&data, argv[1]);
	access_output(&data, argv[max_arg_double(argv) - 1]);
	access_cmd(&data, argv, &head);
	fork_n_pipe(&data, &head, envp);
	while (wait(NULL) > 0)
		;
	return (0);
}
