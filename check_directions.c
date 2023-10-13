/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:38:30 by ael-khel          #+#    #+#             */
/*   Updated: 2023/10/13 18:45:14 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_map(t_map *map_data)
{
	int		i;

	i = 0;
	while (map_data->map[i])
	{
		if (map_data->map_check->num_elem < 6)
		{
			map_data->map_check->elem = ft_split(map_data->map[i], ' ');
			if (!map_data->map_check->elem)
				ft_err(NULL, map_data);
			if (*map_data->map_check->elem)
				ft_check_elements(map_data);
			ft_clear((void **)map_data->map_check->elem);
			map_data->map_check->elem = NULL;
		}
		else
			if (map_data->map[i][0] != '\0')
				break ;
		++i;
	}
	if (!ft_all_elements(map_data->map_check))
		ft_err("[!] Error: Missed elements in the map.", map_data);
	ft_check_content(map_data, i);
}

int	ft_all_elements(t_check *map_check)
{
	return (map_check->no_elem && map_check->so_elem
		&& map_check->we_elem && map_check->ea_elem
		&& map_check->c_elem && map_check->f_elem);
}

void	ft_check_content(t_map *map_data, size_t start)
{
	size_t	y;
	size_t	x;
	char	**map;

	map = map_data->map;
	y = start;
	while (map[y])
	{
		if (!map[y][0])
			ft_err("[!] Error: The map has empty line.", map_data);
		x = 0;
		while (map[y][x])
		{
			if (!ft_strchr("10 NSWE", map[y][x]))
				ft_err("[!] Error: Map has invalid characters", map_data);
			if (ft_strchr("NSWE", map[y][x]))
			{
				if (map_data->player_pos)
					ft_err("[!] Error: Map has more than one player", map_data);
				map_data->player_pos = map[y][x];
			}
			if (y == start || !map[y + 1] || x == 0 || !map[y][x + 1])
				if (!ft_strchr("1 ", map[y][x]))
					ft_err("[!] Error: Map is not surrounded by 1", map_data);
			if (map[y][x] == '0' || map[y][x] == map_data->player_pos)
			{
				if (x > ft_strlen(map[y - 1]) || (y != start && x != 0 && map[y - 1][x - 1] == ' '))
					ft_err("[!] Error: Map is not surrounded by 1", map_data);
				if (x + 1 > ft_strlen(map[y - 1]) || (y != start && map[y - 1][x] == ' '))
					ft_err("[!] Error: Map is not surrounded by 1", map_data);
				if (x + 2 > ft_strlen(map[y - 1]) || (y != start && map[y - 1][x + 1] == ' '))
					ft_err("[!] Error: Map is not surrounded by 1", map_data);
				if (x != 0 && map[y][x - 1] == ' ')
					ft_err("[!] Error: Map is not surrounded by 1", map_data);
				if (map[y][x + 1] == ' ')
					ft_err("[!] Error: Map is not surrounded by 1", map_data);
				if (x > ft_strlen(map[y + 1]) || (map[y + 1] && x != 0 && map[y + 1][x - 1] == ' '))
					ft_err("[!] Error: Map is not surrounded by 1", map_data);
				if (x + 1 > ft_strlen(map[y + 1]) || (map[y + 1] && map[y + 1][x] == ' '))
					ft_err("[!] Error: Map is not surrounded by 1", map_data);
				if (x + 2 > ft_strlen(map[y + 1]) || (map[y + 1] && map[y + 1][x + 1] == ' '))
					ft_err("[!] Error: Map is not surrounded by 1", map_data);
			}
			++x;
		}
		++y;
	}
	if (!map_data->player_pos)
		ft_err("[!] Error: Map has no player position.", map_data);
}

void	ft_check_elements(t_map *map_data)
{
	t_check	*map_check;
	char	**elem;

	map_check = map_data->map_check;
	elem = map_check->elem;
	if (!ft_strncmp(*elem, "NO", 3) && !map_check->no_elem)
		ft_direc_elem(map_data, map_data->no_text, &map_check->no_elem);
	else if (!ft_strncmp(*elem, "SO", 3) && !map_check->so_elem)
		ft_direc_elem(map_data, map_data->so_text, &map_check->so_elem);
	else if (!ft_strncmp(*elem, "WE", 3) && !map_check->we_elem)
		ft_direc_elem(map_data, map_data->we_text, &map_check->we_elem);
	else if (!ft_strncmp(*elem, "EA", 3) && !map_check->ea_elem)
		ft_direc_elem(map_data, map_data->ea_text, &map_check->ea_elem);
	else if (!ft_strncmp(*elem, "C", 2) && !map_check->c_elem)
		ft_rgb_elem(map_data, elem, 1);
	else if (!ft_strncmp(*elem, "F", 2) && !map_check->f_elem)
		ft_rgb_elem(map_data, elem, 0);
	else
		ft_err("[!] Error: invalid map.", map_data);
	map_check->num_elem += 1;
}

void	ft_direc_elem(t_map *map_data, char *dire_text, int *dire_elem)
{
	int	i;

	i = 0;
	while (map_data->map_check->elem[i])
		++i;
	if (i != 2)
		ft_err("[!] Error: Invalid map.", map_data);
	dire_text = ft_strdup(map_data->map_check->elem[1]);
	if (!dire_text)
		ft_err("[!] Error: Invalid map.", map_data);
	*dire_elem = 1;
}
