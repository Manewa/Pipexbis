/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:24:19 by namalier          #+#    #+#             */
/*   Updated: 2024/10/01 18:24:31 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	pipex_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	pipex_lstlast(tmp)->next = new;
}

t_cmd	*pipex_lstlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	pipex_lstfree(t_cmd **head)
{
	t_cmd	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		ft_free_doubletab((*head)->cmd_flag);
		free((*head)->pathcmd);
		free(*head);
		*head = tmp;
	}
	return ;
}
