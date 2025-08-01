#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*c_lst;

	c_lst = *lst;
	if (*lst == NULL)
		*lst = new;
	if (c_lst == NULL)
	{
		c_lst = new;
		return ;
	}
	while (c_lst->next != NULL)
		c_lst = c_lst->next;
	c_lst->next = new;
}
