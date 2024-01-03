/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:38:30 by ael-khel          #+#    #+#             */
/*   Updated: 2024/01/02 20:21:30 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_map(t_map *map_data)
{
	int	i;

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

void	ft_check_elements(t_map *map_data)
{
	t_check	*map_check;
	char	**elem;

	map_check = map_data->map_check;
	elem = map_check->elem;
	if (!ft_strncmp(*elem, "NO", 3) && !map_check->no_elem)
		ft_direc_elem(map_data, &map_data->no_text, &map_check->no_elem);
	else if (!ft_strncmp(*elem, "SO", 3) && !map_check->so_elem)
		ft_direc_elem(map_data, &map_data->so_text, &map_check->so_elem);
	else if (!ft_strncmp(*elem, "WE", 3) && !map_check->we_elem)
		ft_direc_elem(map_data, &map_data->we_text, &map_check->we_elem);
	else if (!ft_strncmp(*elem, "EA", 3) && !map_check->ea_elem)
		ft_direc_elem(map_data, &map_data->ea_text, &map_check->ea_elem);
	else if (!ft_strncmp(*elem, "C", 2) && !map_check->c_elem)
		ft_rgb_elem(map_data, elem, 1);
	else if (!ft_strncmp(*elem, "F", 2) && !map_check->f_elem)
		ft_rgb_elem(map_data, elem, 0);
	else
		ft_err("[!] Error: invalid map.", map_data);
	map_check->num_elem += 1;
}

int	ft_all_elements(t_check *map_check)
{
	return (map_check->no_elem && map_check->so_elem
		&& map_check->we_elem && map_check->ea_elem
		&& map_check->c_elem && map_check->f_elem);
}
