#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst == NULL || *lst == NULL)
		return ;
	temp = *lst;
	if (temp->next != NULL)
		ft_lstclear(&(temp->next), del);
	del(temp->content);
	free(temp);
	*lst = NULL;
}
