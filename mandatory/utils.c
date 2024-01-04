/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:39:04 by ael-khel          #+#    #+#             */
/*   Updated: 2024/01/04 21:51:23 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_cord(t_cord *cord, double x, double y)
{
	cord->x = x;
	cord->y = y;
}

void	ft_paint_pixels(uint8_t *pixels, uint32_t color, size_t size)
{
	size_t	i;
	int		shift;

	shift = 3;
	i = 0;
	while (i < size * BPP)
	{
		if (shift == -1)
			shift = 3;
		pixels[i] = (color >> (8 * shift)) & 0xFF;
		--shift;
		++i;
	}
}

double	ft_normalize_angle(double *angle)
{
	*angle = remainder(*angle, (2 * M_PI));
	if (*angle < 0)
		*angle += (2 * M_PI);
	return (*angle);
}

double	ft_player_angle(t_map *map_data)
{
	if (map_data->character_dire == 'N')
		return (3 * M_PI / 2);
	else if (map_data->character_dire == 'S')
		return (M_PI_2);
	else if (map_data->character_dire == 'W')
		return (M_PI);
	else if (map_data->character_dire == 'E')
		return (0);
	return (0);
}

uint32_t	ft_rgb(uint32_t r, uint32_t g, uint32_t b, uint32_t o)
{
	return (r << 24 | g << 16 | b << 8 | o);
}
