#include "libft.h"

int	ft_length_to_nl(t_list_gnl *lst)
{
	int	len;
	int	i;

	len = 0;
	while (lst != NULL)
	{
		i = 0;
		while (lst->content[i] != '\0')
		{
			len++;
			if (lst->content[i] == '\n')
				return (len);
			i++;
		}
		lst = lst->next;
	}
	return (len);
}

void	ft_append_tail(t_list_gnl **list, char *str)
{
	if (*list == NULL)
	{
		*list = (t_list_gnl *)malloc(sizeof(t_list_gnl));
		if (*list == NULL)
			return ;
		(*list)->content = str;
		(*list)->next = NULL;
	}
	else
	{
		ft_append_tail(&((*list)->next), str);
	}
}

int	ft_free_str(char *str, int len)
{
	if (str == NULL || len == 0)
	{
		if (str != NULL)
			free(str);
		return (1);
	}
	return (0);
}

t_list_gnl	*ft_last_node(t_list_gnl *list)
{
	if (list == NULL)
		return (NULL);
	if (list->next != NULL)
		return (ft_last_node(list->next));
	return (list);
}

int	ft_contains_nl(t_list_gnl *list)
{
	int	i;

	i = 0;
	if (list == NULL)
		return (0);
	while (list != NULL)
	{
		while (list->content[i] != '\0')
		{
			if (list->content[i] == '\n')
			{
				return (1);
			}
			i++;
		}
		list = list->next;
		i = 0;
	}
	return (0);
}
