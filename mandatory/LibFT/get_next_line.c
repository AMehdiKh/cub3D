/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:30:22 by ael-khel          #+#    #+#             */
/*   Updated: 2023/10/04 19:30:50 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_check_nl(char **reserve)
{
	char	*line;
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	while (*(*reserve + i) != '\n')
		++i;
	line = malloc(i + 2);
	if (!line)
		return (free(*reserve), *reserve = NULL, NULL);
	ft_strlcpy_gnl(line, *reserve, (i + 2));
	len = ft_strlen_gnl(*reserve + i + 1);
	if (!len)
		return (free(*reserve), *reserve = NULL, line);
	else
	{
		tmp = malloc(len + 1);
		ft_strlcpy_gnl(tmp, (*reserve + i + 1), (len + 1));
		free(*reserve);
		*reserve = ft_strdup_gnl(&tmp);
		return (line);
	}
}

char	*get_next_line(int fd)
{
	static char	*reserve;
	char		*buffer;
	int			nbyte;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(reserve), reserve = NULL, NULL);
	while (1)
	{
		nbyte = read(fd, buffer, BUFFER_SIZE);
		if (nbyte < 0)
			return (free(buffer), free(reserve), reserve = NULL, NULL);
		if (!nbyte && !ft_strchr_gnl(reserve, '\n'))
			return (free(buffer), ft_strdup_gnl(&reserve));
		buffer[nbyte] = '\0';
		if (nbyte)
			reserve = ft_strjoin_gnl(reserve, buffer);
		if (ft_strchr_gnl(reserve, '\n'))
			return (free(buffer), ft_check_nl(&reserve));
	}
}
