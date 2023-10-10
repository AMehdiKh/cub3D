/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:38:30 by ael-khel          #+#    #+#             */
/*   Updated: 2023/10/10 21:46:27 by ael-khel         ###   ########.fr       */
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
			{
				ft_destroy_map_data(map_data);
				ft_err(NULL, 1);
			}
			if (*map_data->map_check->elem)
				ft_check_elements(map_data);
			ft_clear((void **)map_data->map_check->elem);
			map_data->map_check->elem = NULL;
		}
		else
			if (map_data->map[i][0] != '\0')
				return (i);
		++i;
	}
}

void	ft_check_content(t_map *map_data, int start)
{
	int		y;
	int		x;
	char	**map;

	y = start;
	map = map_data->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!ft_strchr("10 NSWE", map[y][x]))
				ft_err("[!] Error: Map has invalid characters", map_data);
			while (map[y][space] == ' ')
				++space;
			if (y == start || !map[y + 1] || x == space || !map[y][x + 1])
				if (!ft_strchr("1", map[y][x]))
					ft_err("[!] Error: Map is not surrounded by 1", map_data);
			
		}
	}
}

void	ft_check_elements(t_map *map_data)
{
	t_check	*map_check;
	char	**elem;

	map_check = map_data->map_check;
	elem = map_check->elem;
	if (!ft_strncmp(*elem, "NO", ft_strlen(*elem)) && !map_check->no_elem)
		ft_direc_elem(map_data, map_data->no_text, &map_check->no_elem);
	else if (!ft_strncmp(*elem, "SO", ft_strlen(*elem)) && !map_check->so_elem)
		ft_direc_elem(map_data, map_data->so_text, &map_check->so_elem);
	else if (!ft_strncmp(*elem, "WE", ft_strlen(*elem)) && !map_check->we_elem)
		ft_direc_elem(map_data, map_data->we_text, &map_check->we_elem);
	else if (!ft_strncmp(*elem, "EA", ft_strlen(*elem)) && !map_check->ea_elem)
		ft_direc_elem(map_data, map_data->ea_text, &map_check->ea_elem);
	else if (!ft_strncmp(*elem, "C", ft_strlen(*elem)) && !map_check->c_elem)
		ft_rgb_elem(map_data, elem, 1);
	else if (!ft_strncmp(*elem, "F", ft_strlen(*elem)) && !map_check->f_elem)
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
