/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:40:49 by ael-khel          #+#    #+#             */
/*   Updated: 2023/10/11 15:05:39 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_arg(int ac, char *av)
{
	if (ac != 2)
		ft_err("[!] Error: It must be like this: ./cub3d [map_name].cub", NULL);
	if (ft_strlen(av) <= 4)
		ft_err("[!] Error: The map's name format is incorrect", NULL);
	if (ft_strncmp(".cub", av + (ft_strlen(av) - 4), 4))
		ft_err("[!] Error: The map must be in [.cub] format", NULL);
}

char	*ft_open_map(char *map_name)
{
	int		fd;
	int		nbyte;
	char	*line;
	char	*buffer;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		ft_err(NULL, NULL);
	line = NULL;
	buffer = ft_calloc(4096, 1);
	if (!buffer)
		return (close(fd), free(buffer), ft_err(NULL, NULL), NULL);
	nbyte = 1;
	while (nbyte)
	{
		nbyte = read(fd, buffer, 4096);
		if (nbyte < 0)
			return (close(fd), free(buffer), free(line), ft_err(NULL, NULL), NULL);
		buffer[nbyte] = '\0';
		line = ft_strjoin_gnl(line, buffer);
		if (!line)
			return (close(fd), free(buffer), ft_err(NULL, NULL), NULL);
	}
	return (close(fd), free(buffer), line);
}

void	ft_parse_map(t_map *map_data, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
		{
			free(line);
			ft_err("[!] Error: The map has TAB character", NULL);
		}
		++i;
	}
	map_data->map = ft_split(line, '\n');
	free(line);
	if (!map_data->map)
		ft_err(NULL, NULL);
	if (!*map_data->map)
	{
		free(map_data->map);
		ft_err("[!] Error: The map is empty", NULL);
	}
}
