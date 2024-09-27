
#include "../../includes/pipex.h"

void	pipex_lstadd_back(list **lst, list *new)
{
	list	*tmp;

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

list	*pipex_lstlast(list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	pipex_lstfree(list **head)
{
	list	*tmp;

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
