/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <namalier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:18:07 by namalier          #+#    #+#             */
/*   Updated: 2024/10/01 18:11:45 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_data
{
	char		**path;
	int			input_fd;
	int			output_fd;
}					t_data;

typedef struct s_cmd
{
	char			*pathcmd;
	char			**cmd_flag;
	void			*next;
	struct s_cmd	*head;
}						t_cmd;

#endif
