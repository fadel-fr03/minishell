#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	size;
	t_list	*lst_iter;

	lst_iter = lst;
	size = 0;
	while (lst_iter != NULL)
	{
		size++;
		lst_iter = lst_iter->next;
	}
	return (size);
}
