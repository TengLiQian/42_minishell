/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:37:36 by jolai             #+#    #+#             */
/*   Updated: 2024/05/20 20:17:14 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

//LIBFT files:
//char//
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

//memory//
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *str, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t num, size_t size);

//string 1//
int		ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *small, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

//string 2//
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

//file descriptor//
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

//bonus//
int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//ft_printf files//
//ft_printf.c:
int		ft_printf(const char *str, ...);
void	ft_ptrconvert(unsigned long long value, int *count);
void	check_specifier(int *count, const char s, va_list ap);

//ft_printstuff.c:
void	ft_printchars(va_list ap, char type, int *count);
void	ft_printnbr(long long num, int *count, char *base);

//get_next_line files//
//get_next_line_bonus.c:
void	reset_buffer(char *buffer, char *remainder, int position);
char	*separate_remainder(char *buffer, char *temp);
char	*get_next_line(int fd);

//get_next_line_utils_bonus.c
char	*ft_strndup(char *s, size_t len);
char	*ft_strjoin_free(char *s1, char *s2);
size_t	ft_find_newline(char const *s);

//extra stuff:
void	free_2d_c(char **array);

#endif
