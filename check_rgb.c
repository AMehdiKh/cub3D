/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:15:13 by ael-khel          #+#    #+#             */
/*   Updated: 2023/10/12 19:44:20 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rgb_elem(t_map *map_data, char **elem, int option)
{
	int	i;

	i = 1;
	while (elem[i])
	{
		if (option)
			ft_check_rgb(map_data, elem[i], &map_data->c_color);
		else
			ft_check_rgb(map_data, elem[i], &map_data->f_color);
		++i;
	}
	if (map_data->map_check->digit_count != 3)
		ft_err("[!] Error: Invalid map.", map_data);
	if (map_data->map_check->comma_count != 2)
		ft_err("[!] Error: Invalid map.", map_data);
	map_data->map_check->digit_count = 0;
	map_data->map_check->comma_count = 0;
	map_data->map_check->digit = 0;
	if (option)
		map_data->map_check->c_elem = 1;
	else
		map_data->map_check->f_elem = 1;
}

void	ft_check_rgb(t_map *map_data, char *elem, int *color)
{
	int	i;

	i = 0;
	while (elem[i])
	{
		if (ft_isdigit(elem[i]))
			ft_rgb_init(map_data, elem, color, &i);
		else if (elem[i] == ',' && map_data->map_check->digit == 1)
		{
			map_data->map_check->comma_count += 1 ;
			map_data->map_check->digit = 0;
		}
		else
			ft_err("[!] Error: Invalid map.", map_data);
		++i;
	}
}

void	ft_rgb_init(t_map *map_data, char *elem, int *color, int *i)
{
	int	rgb;

	rgb = 0;
	map_data->map_check->digit = 1;
	while (ft_isdigit(elem[*i]))
	{
		rgb = (rgb * 10) + (elem[*i] - 48);
		++*i;
	}
	if (rgb > 255)
		ft_err("[!] Error: Invalid map.", map_data);
	*color |= (rgb << (8 * map_data->map_check->digit_count));
	map_data->map_check->digit_count += 1;
	if (map_data->map_check->digit_count > 3)
		ft_err("[!] Error: Invalid map.", map_data);
	*i -= 1;
}
