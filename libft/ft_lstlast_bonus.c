#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*c_lst;

	c_lst = lst;
	if (lst == NULL)
		return (lst);
	while (c_lst->next != NULL)
		c_lst = c_lst->next;
	return (c_lst);
}
