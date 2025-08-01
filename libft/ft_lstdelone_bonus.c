#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != NULL && del)
	{
		del(lst->content);
		free(lst);
	}
}
