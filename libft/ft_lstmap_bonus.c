#include "libft.h"

static t_list	*ft_recursive_map(t_list *lst, void *(*f)(void *),
		void (*del)(void *))
{
	t_list	*new_elem;

	if (lst == NULL)
		return (NULL);
	new_elem = ft_lstnew(f(lst->content));
	if (new_elem == NULL)
	{
		return (NULL);
	}
	new_elem->next = ft_recursive_map(lst->next, f, del);
	if (new_elem->next == NULL && lst->next != NULL)
	{
		del(new_elem->content);
		free(new_elem);
		return (NULL);
	}
	return (new_elem);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mapped;

	mapped = ft_recursive_map(lst, f, del);
	if (mapped == NULL)
		ft_lstclear(&mapped, del);
	return (mapped);
}
