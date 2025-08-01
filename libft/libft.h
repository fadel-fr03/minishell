#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_list_gnl
{
	char				*content;
	struct s_list_gnl	*next;
}					t_list_gnl;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *nptr);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char const *s, int fd);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s1);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strcat(char *dest, const char *src);
size_t				ft_strlen(const char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strrchr(const char *s, int c);
char				**ft_split(char const *s, char c);
char				*ft_strtrim(char const *s1, char const *set);
int					ft_tolower(int c);
int					ft_toupper(int c);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
// Get Next Line
char				*get_next_line(int fd);
t_list_gnl			*ft_last_node(t_list_gnl *list);
int					ft_length_to_nl(t_list_gnl *lst);
void				ft_append_tail(t_list_gnl **list, char *str);
char				*ft_create_string_from_lst(t_list_gnl *lst);
void				ft_create_list(int fd, t_list_gnl **list);
int					ft_contains_nl(t_list_gnl *list);
int					ft_free_str(char *str, int len);
// Printf
int					ft_check_format(va_list args, const char format, int fd);
int					ft_print_percent(int fd);
int					ft_printf(const char *fmt, ...);
int					ft_print_char(char c, int fd);
int					ft_print_decimal(int number, int fd);
int					ft_print_string(char *str, int fd);
int					ft_print_unsigned(unsigned int number, int fd);
int					ft_print_pointer(void *p, int fd);
int					ft_putnbr_base(unsigned int nbr, char *base, int fd);
int					ft_fprintf(int fd, const char *fmt, ...);
int					ft_sprintf(char *str, const char *fmt, ...);
int					get_divisor(int num);
int					convert_number_to_str(char *str, int num, int divisor);

#endif