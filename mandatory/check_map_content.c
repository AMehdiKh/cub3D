/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 21:45:09 by ael-khel          #+#    #+#             */
/*   Updated: 2023/11/01 18:42:54 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_content(t_map *map_data)
{
	int	y;
	int	x;

	ft_isolate_content(map_data);
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
			ft_check_player(map_data, x, y);
			ft_check_walls(map_data, map_data->map, x, y);
			++x;
		}
		if (map_data->max_width < x)
			map_data->max_width = x;
		++y;
	}
	map_data->max_height = y;
	if (!map_data->player_dir)
		ft_err("[!] Error:The map has no player position.", map_data);
}

void	ft_isolate_content(t_map *map_data)
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
	while (map_data->map[map_data->start + i])
	{
		map_content[i] = ft_strdup(map_data->map[map_data->start + i]);
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

void	ft_check_player(t_map *map_data, int x, int y)
{
	if (ft_strchr("NSWE", map_data->map[y][x]))
	{
		if (map_data->player_dir)
			ft_err("[!] Error: Map has more than one player", map_data);
		map_data->player_dir = map_data->map[y][x];
		map_data->player->x = (x * TILE_SIZE) + (TILE_SIZE / 2);
		map_data->player->y = (y * TILE_SIZE) + (TILE_SIZE / 2);
	}
}

void	ft_check_walls(t_map *map_data, char **map, size_t x, size_t y)
{
	if (map[y][x] == '0' || map[y][x] == map_data->player_dir)
	{
		if (x > ft_strlen(map[y - 1])
			|| (y != map_data->start && x != 0 && map[y - 1][x - 1] == ' '))
			ft_err("[!] Error: Map is not surrounded by 1", map_data);
		if (x + 1 > ft_strlen(map[y - 1])
			|| (y != map_data->start && map[y - 1][x] == ' '))
			ft_err("[!] Error: Map is not surrounded by 1", map_data);
		if (x + 2 > ft_strlen(map[y - 1])
			|| (y != map_data->start && map[y - 1][x + 1] == ' '))
			ft_err("[!] Error: Map is not surrounded by 1", map_data);
		if (x != 0 && map[y][x - 1] == ' ')
			ft_err("[!] Error: Map is not surrounded by 1", map_data);
		if (map[y][x + 1] == ' ')
			ft_err("[!] Error: Map is not surrounded by 1", map_data);
		if (x > ft_strlen(map[y + 1])
			|| (map[y + 1] && x != 0 && map[y + 1][x - 1] == ' '))
			ft_err("[!] Error: Map is not surrounded by 1", map_data);
		if (x + 1 > ft_strlen(map[y + 1])
			|| (map[y + 1] && map[y + 1][x] == ' '))
			ft_err("[!] Error: Map is not surrounded by 1", map_data);
		if (x + 2 > ft_strlen(map[y + 1])
			|| (map[y + 1] && map[y + 1][x + 1] == ' '))
			ft_err("[!] Error: Map is not surrounded by 1", map_data);
	}
}
