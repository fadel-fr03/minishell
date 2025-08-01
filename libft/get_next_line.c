#include "libft.h"

char	*ft_create_string_from_lst(t_list_gnl *lst)
{
	int		len;
	char	*str;
	int		i;
	int		j;

	j = 0;
	len = ft_length_to_nl(lst);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (ft_free_str(str, len))
		return (NULL);
	while (lst != NULL)
	{
		i = 0;
		while (lst->content[i] != '\0')
		{
			str[j] = lst->content[i];
			if (lst->content[i] == '\n')
				break ;
			i++;
			j++;
		}
		lst = lst->next;
	}
	str[len] = '\0';
	return (str);
}

void	ft_free_list(t_list_gnl **list)
{
	t_list_gnl	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
}

void	ft_reset_lst(t_list_gnl **list)
{
	t_list_gnl	*last_node;
	t_list_gnl	*new_node;
	int			i;
	int			j;
	char		*buffer;

	i = 0;
	j = 0;
	last_node = ft_last_node(*list);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	new_node = (t_list_gnl *)malloc(sizeof(t_list_gnl));
	while (last_node->content[j] != '\0' && last_node->content[j] != '\n')
		j++;
	while (last_node->content[j] != '\0' && last_node->content[j + 1] != '\0')
	{
		j++;
		buffer[i] = last_node->content[j];
		i++;
	}
	buffer[i] = '\0';
	new_node->content = buffer;
	new_node->next = NULL;
	ft_free_list(list);
	*list = new_node;
}

void	ft_create_list(int fd, t_list_gnl **list)
{
	char	*buffer;
	int		bytes_read;

	while (!ft_contains_nl(*list))
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		ft_append_tail(list, buffer);
	}
}

char	*get_next_line(int fd)
{
	char				*str;
	static t_list_gnl	*lst = NULL;

	str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_create_list(fd, &lst);
	str = ft_create_string_from_lst(lst);
	if (str != NULL)
	{
		ft_reset_lst(&lst);
	}
	else
	{
		ft_free_list(&lst);
	}
	return (str);
}
