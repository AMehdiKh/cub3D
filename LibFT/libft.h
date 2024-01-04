/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 07:54:13 by Ael-khel          #+#    #+#             */
/*   Updated: 2023/12/27 12:50:21 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

// [*] ft_dprintf

typedef struct s_dprintf
{
	va_list	ap;
	int		fd;
	int		len;
	int		spec;
}	t_dprintf;

int			ft_dprintf(int fd, const char *format, ...);

const char	*ft_check_spec(const char *format, t_dprintf *tab);

void		ft_putchar_dpf(char c, t_dprintf *tab);
void		ft_putstr_dpf(char *s, t_dprintf *tab);
void		ft_putnbr_dpf(long n, t_dprintf *tab);
void		ft_puthex_dpf(unsigned long n, t_dprintf *tab);

// [*] get_next_line

char		*get_next_line(int fd);
char		*ft_check_nl(char **reserve);
char		*ft_strjoin_gnl(char *reserve, char *buffer);
char		*ft_strdup_gnl(char **str);
void		ft_strlcpy_gnl(char *dst, const char *src, size_t size);
int			ft_strchr_gnl(char *s, int c);
size_t		ft_strlen_gnl(const char *s);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

// [*] LibFT

size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);

char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
char		*ft_itoa(int n);

void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		*ft_memmove(void *dst, const void *src, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memset(void *s, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);
void		ft_putendl_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_bzero(void *s, size_t n);

int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_atoi(const char *s);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);

#endif