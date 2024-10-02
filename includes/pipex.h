/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:44:38 by namalier          #+#    #+#             */
/*   Updated: 2024/10/02 15:49:11 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libs.h"
# include "Libft/libft.h"
# include "structs.h"

/*********		pipex			*********/

void	init_no_path(t_data *data, char **argv);
void	get_path(char **envp, t_data *data);
int		max_arg_double(char **argv);
int		main(int argc, char **argv, char **envp);

/*********		access_cmd2		*********/

t_cmd	*full_path_cmd(t_cmd *cmd, char **cmd_n_flags);
char	*ft_cpypath(char *argv, char *path);
char	*try_access(t_data *data, t_cmd *cmd, char *cmd_no_flag);
int		name_only_cmd(t_data *data, t_cmd *cmd, char **cmd_n_flags);
t_cmd	*create_node(char *argv, t_data *data);
void	access_cmd(t_data *data, char **argv, t_cmd **head);

/*********		access_files	*********/

void	access_output(t_data *data, char *argv);
void	access_input(t_data *data, char *argv);

/*********		ft_error		*********/

void	ft_free_error(t_data *data);
void	ft_free_fds(int *pipefd, t_data *data);
void	ft_free_both(t_data *data, t_cmd *cmd, int *pipefd, int end);

/*********		lst				**********/

void	pipex_lstadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*pipex_lstlast(t_cmd *lst);
void	pipex_lstfree(t_cmd **head);

/*********		forking			**********/

void	parent_process(int *pipefd);
void	child_process(t_data *data, t_cmd *cmd, int *pipefd);
void	fork_n_pipe(t_data *data, t_cmd **cmd);

/*********		try_access		*********/

void	init_input(t_data *data, t_cmd *cmdp, int *pipefd);
void	init_output(t_data *data, t_cmd *cmd, int *pipefd, int output_fd);

/**********		cmd_n_flags		**********/

char **check_cmd_n_flags(char *argv);

#endif
