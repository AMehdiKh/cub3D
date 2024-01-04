/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_elements_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:15:13 by ael-khel          #+#    #+#             */
/*   Updated: 2024/01/04 15:04:47 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_direc_elem(t_map *map_data, char **dire_text, int *dire_elem)
{
	int	i;

	i = 0;
	while (map_data->map_check->elem[i])
		++i;
	if (i != 2)
		ft_err("[!] Error: Invalid file path structure.", map_data);
	*dire_text = ft_strdup(map_data->map_check->elem[1]);
	if (!*dire_text)
		ft_err(NULL, map_data);
	*dire_elem = 1;
}

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
		ft_err("[!] Error: RGB color have less than 3 values.", map_data);
	if (map_data->map_check->comma_count != 2)
		ft_err("[!] Error: Invalid RGB color structure.", map_data);
	map_data->map_check->digit_count = 0;
	map_data->map_check->comma_count = 0;
	map_data->map_check->digit = 0;
	if (option)
		map_data->map_check->c_elem = 1;
	else
		map_data->map_check->f_elem = 1;
}

void	ft_check_rgb(t_map *map_data, char *elem, uint32_t *color)
{
	int	i;

	i = 0;
	while (elem[i])
	{
		if (ft_isdigit(elem[i]))
		{
			ft_rgb_init(map_data, elem, color, &i);
			map_data->map_check->digit = 1;
		}
		else if (elem[i] == ',' && map_data->map_check->digit == 1)
		{
			map_data->map_check->comma_count += 1;
			map_data->map_check->digit = 0;
		}
		else
			ft_err("[!] Error: Invalid character in RGB color.", map_data);
		++i;
	}
}

void	ft_rgb_init(t_map *map_data, char *elem, uint32_t *color, int *i)
{
	uint32_t	rgb;

	rgb = 0;
	while (ft_isdigit(elem[*i]))
	{
		rgb = (rgb * 10) + (elem[*i] - 48);
		++*i;
	}
	if (rgb > 255)
		ft_err("[!] Error: RGB color is larger than 255.", map_data);
	*color |= (rgb << (8 * (3 - map_data->map_check->digit_count)));
	map_data->map_check->digit_count += 1;
	if (map_data->map_check->digit_count == 3)
		*color |= 0xFF;
	if (map_data->map_check->digit_count > 3)
		ft_err("[!] Error: RGB color have more than 3 values.", map_data);
	*i -= 1;
}
