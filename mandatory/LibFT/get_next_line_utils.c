/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:36:17 by ael-khel          #+#    #+#             */
/*   Updated: 2023/10/04 19:20:40 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		++i;
	return (i);
}

int	ft_strchr_gnl(char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
		if (*s++ == (unsigned char)c)
			return (1);
	return (0);
}

void	ft_strlcpy_gnl(char *dst, const char *src, size_t size)
{
	if (size && dst)
	{
		while (--size && *src)
			*dst++ = *src++;
		*dst = '\0';
	}
}

char	*ft_strjoin_gnl(char *reserve, char *buffer)
{
	char	*tmp;

	tmp = malloc(ft_strlen_gnl(reserve) + ft_strlen_gnl(buffer) + 1);
	if (!tmp)
		return (free(reserve), NULL);
	ft_strlcpy_gnl(tmp, reserve, ft_strlen_gnl(reserve) + 1);
	ft_strlcpy_gnl((tmp + ft_strlen_gnl(tmp)),
		buffer, ft_strlen_gnl(buffer) + 1);
	return (free(reserve), tmp);
}

char	*ft_strdup_gnl(char **str)
{
	char	*dup;

	if (!*str)
		return (NULL);
	dup = malloc(ft_strlen_gnl(*str) + 1);
	if (!dup)
		return (free(*str), *str = NULL, NULL);
	ft_strlcpy_gnl(dup, *str, ft_strlen_gnl(*str) + 1);
	return (free(*str), *str = NULL, dup);
}
