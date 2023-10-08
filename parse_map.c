/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:40:49 by ael-khel          #+#    #+#             */
/*   Updated: 2023/10/08 17:41:59 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_arg(int ac, char *av)
{
	if (ac != 2)
		ft_err("[!] Error: It must be like this: ./cub3d [map_name].cub", 1);
	if (ft_strlen(av) <= 4)
		ft_err("[!] Error: The map's name format is incorrect", 1);
	if (ft_strncmp(".cub", av + (ft_strlen(av) - 4), 4))
		ft_err("[!] Error: The map must be in [.cub] format", 1);
}

char	*ft_open_map(char *map_name)
{
	int		fd;
	int		nbyte;
	char	*line;
	char	*buffer;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		ft_err(NULL, 1);
	line = NULL;
	buffer = ft_calloc(4096, 1);
	if (!buffer)
		return (close(fd), free(buffer), ft_err(NULL, 1), NULL);
	nbyte = 1;
	while (nbyte)
	{
		nbyte = read(fd, buffer, 4096);
		if (nbyte < 0)
			return (close(fd), free(buffer), free(line), ft_err(NULL, 1), NULL);
		buffer[nbyte] = '\0';
		line = ft_strjoin_gnl(line, buffer);
		if (!line)
			return (close(fd), free(buffer), ft_err(NULL, 1), NULL);
	}
	return (close(fd), free(buffer), line);
}

int	ft_parse_map(t_map *map_data, char *line)
{
	int		i;

	i = -1;
	while (line[++i])
		if (line[i] == '\t')
			return (free(line),
				ft_err("[!] Error: The map has TAB character", 1));
	map_data->map = ft_split(line, '\n');
	free(line);
	if (!map_data->map)
		ft_err(NULL, 1);
	if (!*map_data->map)
	{
		free(map_data->map);
		ft_err("[!] Error: The map is empty", 1);
	}
}

