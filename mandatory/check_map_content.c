/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 21:45:09 by ael-khel          #+#    #+#             */
/*   Updated: 2023/12/21 17:15:37 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_content(t_map *map_data, int start)
{
	int	y;
	int	x;

	ft_isolate_content(map_data, start);
	y = 0;
	while (map_data->map[y])
	{
		if (map_data->map[y][0] == '\0')
			ft_err("[!] Error: The Map has empty lines", map_data);
		x = 0;
		while (map_data->map[y][x])
		{
			if (!ft_strchr("10 NSWE", map_data->map[y][x]))
				ft_err("[!] Error: Map has invalid characters", map_data);
			ft_check_character(map_data, x, y);
			ft_check_walls(map_data, map_data->map, x, y);
			++x;
		}
		if (map_data->map_width < x * TILE_SIZE)
			map_data->map_width = x * TILE_SIZE ;
		++y;
	}
	map_data->map_height = y * TILE_SIZE;
	if (!map_data->character_dire)
		ft_err("[!] Error:The map has no player position.", map_data);
}

void	ft_isolate_content(t_map *map_data, int start)
{
	char	**map_content;
	int		i;

	i = 0;
	while (map_data->map[i])
		++i;
	map_content = ft_calloc((i + 1), sizeof(char *));
	if (!map_content)
		ft_err(NULL, map_data);
	i = 0;
	while (map_data->map[start + i])
	{
		map_content[i] = ft_strdup(map_data->map[start + i]);
		if (!map_content[i])
		{
			ft_clear((void **)map_content);
			ft_err(NULL, map_data);
		}
		++i;
	}
	ft_clear((void **)map_data->map);
	map_data->map = map_content;
}

void	ft_check_character(t_map *map_data, int x, int y)
{
	if (ft_strchr("NSWE", map_data->map[y][x]))
	{
		if (map_data->character_dire)
			ft_err("[!] Error: Map has more than one player", map_data);
		map_data->character_dire = map_data->map[y][x];
		map_data->character->x = (x * TILE_SIZE) + (TILE_SIZE / 2);
		map_data->character->y = (y * TILE_SIZE) + (TILE_SIZE / 2);
	}
}

void	ft_check_walls(t_map *map_data, char **map, size_t x, size_t y)
{
	if (map[y][x] == '0' || map[y][x] == map_data->character_dire)
	{
		if (map[y][x + 1] == '\0' || map[y][x + 1] == ' ')
			ft_err("[1] Error: Map is not surrounded by '1'", map_data);
		if (x == 0 || map[y][x - 1] == ' ')
			ft_err("[2] Error: Map is not surrounded by '1'", map_data);
		if (x + 1 > ft_strlen(map[y + 1]) || map[y + 1][x] == ' ')
			ft_err("[3] Error: Map is not surrounded by '1'", map_data);
		if (y == 0 || x + 1 > ft_strlen(map[y - 1]) || map[y - 1][x] == ' ')
			ft_err("[4] Error: Map is not surrounded by '1'", map_data);
		if (x + 2 > ft_strlen(map[y + 1]) || map[y + 1][x + 1] == ' ')
			ft_err("[5] Error: Map is not surrounded by '1'", map_data);
		if (x > ft_strlen(map[y + 1]) || (x != 0 && map[y + 1][x - 1] == ' '))
			ft_err("[6] Error: Map is not surrounded by '1'", map_data);
		if (y == 0 || x + 2 > ft_strlen(map[y - 1]) || map[y - 1][x + 1] == ' ')
			ft_err("[7] Error: Map is not surrounded by '1'", map_data);
		if (y == 0 || x > ft_strlen(map[y - 1])
			|| (x != 0 && map[y - 1][x - 1] == ' '))
			ft_err("[8] Error: Map is not surrounded by '1'", map_data);
	}
}
