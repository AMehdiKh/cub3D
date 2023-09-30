/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:39:04 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/04 15:46:25 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_printf
{
	va_list	ap;
	int		len;
	int		spec;
}	t_printf;

int			ft_printf(const char *format, ...);
const char	*ft_check_spec(const char *format, t_printf *tab);
void		ft_putchar(char c, t_printf *tab);
void		ft_putstr(char *s, t_printf *tab);
void		ft_putnbr(long n, t_printf *tab);
void		ft_puthex(unsigned long n, t_printf *tab);

void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);

int			ft_nbrlen(int n);
char		*ft_itoa(int n);

char		**ft_split(char const *s, char c);
size_t		word_count(char const *s, char c);
char		**ft_alloc(char **ptr, const char *s, char c, size_t wc);
void		*ft_clear_split(char **ptr, size_t x);

int			ft_strchr(const char *s, int c);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memset(void *s, int c, size_t len);

void		ft_putendl_fd(char *s, int fd);

#endif