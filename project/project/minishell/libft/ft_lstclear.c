#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;

	if (!lst || !(*del))
		return ;
	current = *lst;
	while (current)
	{
		(*del)(current->content);
		current = current->next;
		free(*lst);
		*lst = current;
	}
	lst = NULL;
}
