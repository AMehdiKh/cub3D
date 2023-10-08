/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:38:30 by ael-khel          #+#    #+#             */
/*   Updated: 2023/10/08 19:01:21 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_map(t_map *map_data)
{
	char	**element;
	int		i;

	i = 0;
	while (map_data->map[i] && map_data->map_check->num_elem < 6)
	{
		element = ft_split(map_data->map[i], ' ');
		if (!element)
		{
			ft_destroy_map_data(map_data);
			ft_err(NULL, 1);
		}
		if (*element)
			ft_check_elements(map_data, element);
		ft_clear((void **)element);
		++i;
	}
}

void	ft_check_elements(t_map *map_data, char **elem)
{
	t_check	*map_check;

	map_check = map_data->map_check;
	if (!ft_strncmp(*elem, "NO", ft_strlen(*elem)) && !map_check->no_elem)
		ft_direc(map_data, elem, map_data->no_text, &map_check->no_elem);
	else if (!ft_strncmp(*elem, "SO", ft_strlen(*elem)) && !map_check->so_elem)
		ft_direc(map_data, elem, map_data->so_text, &map_check->so_elem);
	else if (!ft_strncmp(*elem, "WE", ft_strlen(*elem)) && !map_check->we_elem)
		ft_direc(map_data, elem, map_data->we_text, &map_check->we_elem);
	else if (!ft_strncmp(*elem, "EA", ft_strlen(*elem)) && !map_check->ea_elem)
		ft_direc(map_data, elem, map_data->ea_text, &map_check->ea_elem);
	else if (!ft_strncmp(*elem, "C", ft_strlen(*elem)) && !map_check->c_elem)
		ft_colors_elem(map_data, elem, &map_data->c_color, &map_check->c_elem);
	else if (!ft_strncmp(*elem, "F", ft_strlen(*elem)) && !map_check->f_elem)
		ft_colors_elem(map_data, elem, &map_data->f_color, &map_check->f_elem);
	else
	{
		ft_clear((void **)elem);
		ft_destroy_map_data(map_data);
		ft_err("[!] Error: invalid map.", 1);
	}
	map_check->num_elem += 1;
}

void	ft_colors_elem(t_map *map_data, char **elem, int *fc_clr, int *fc_elem)
{
	int	rgb;
	int	i;
	int	j;
	int	

	i = 1;
	while (elem[i])
	{
		j = 0;
		while (element[i][j])
		{
			if (ft_isdigit(element[i][j]))
			{
				
				++j;
			}
			else
			{
				
			}
			++j;
		}
		++i;
	}
	ft_clear((void **) elem);
	ft_destroy_map_data(map_data);
	ft_err("[!] Error: Invalid map.", 1);
	*fc_elem = 1;
}

void	ft_direc(t_map *map_data, char **elem, char *dire_text, int *dire_elem)
{
	int	i;

	i = 0;
	while (elem[i])
		++i;
	if (i != 2)
	{
		ft_clear((void **) elem);
		ft_destroy_map_data(map_data);
		ft_err("[!] Error: Invalid map.", 1);
	}
	dire_text = ft_strdup(elem[1]);
	if (!dire_text)
	{
		ft_clear((void **) elem);
		ft_destroy_map_data(map_data);
		ft_err("[!] Error: Invalid map.", 1);
	}
	*dire_elem = 1;
}

void	ft_destroy_map_data(t_map *map_data)
{
	free(map_data->no_text);
	free(map_data->so_text);
	free(map_data->we_text);
	free(map_data->ea_text);
	ft_clear((void **)map_data->map);
}
