/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:40:49 by ael-khel          #+#    #+#             */
/*   Updated: 2023/10/15 20:03:31 by ael-khel         ###   ########.fr       */
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

void	ft_count_map_lines(t_map *map_data, char *map_name)
{
	char	*line;
	int		fd;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		ft_err(NULL, NULL);
	line = "1337";
	while (line)
	{
		line = get_next_line(fd);
		if (line)
			++map_data->map_check->line_count;
		free(line);
	}
	close(fd);
	if (map_data->map_check->line_count == 0)
		ft_err("[!] Error: The map is empty", NULL);
}

void	ft_open_map(t_map *map_data, char *map_name)
{
	int		line_count;
	int		fd;
	int		i;

	ft_count_map_lines(map_data, map_name);
	line_count = map_data->map_check->line_count;
	map_data->map = ft_calloc((line_count + 1), sizeof(char *));
	if (!map_data->map)
		ft_err(NULL, NULL);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		ft_err(NULL, map_data);
	i = 0;
	while (i < line_count)
		map_data->map[i++] = get_next_line(fd);
	close(fd);
}

void	ft_parse_map(t_map *map_data, char *map_name)
{
	int		i;
	int		j;

	ft_open_map(map_data, map_name);
	i = 0;
	while (map_data->map[i])
	{
		j = 0;
		while (map_data->map[i][j])
		{
			if (map_data->map[i][j] == '\t')
				ft_err("[!] Error: The map has TAB character", map_data);
			if (map_data->map[i][j] == '\n' && !map_data->map[i + 1])
				ft_err("[!] Error: The Map has empty lines", map_data);
			if (map_data->map[i][j] == '\n')
				map_data->map[i][j] = '\0';
			++j;
		}
		++i;
	}
}
