/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:39:04 by ael-khel          #+#    #+#             */
/*   Updated: 2024/01/03 21:21:18 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_esc(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	ft_destroy_map_data(mlx->map_data);
	if (mlx->no_text)
		mlx_delete_texture(mlx->no_text);
	if (mlx->so_text)
		mlx_delete_texture(mlx->so_text);
	if (mlx->we_text)
		mlx_delete_texture(mlx->we_text);
	if (mlx->ea_text)
		mlx_delete_texture(mlx->ea_text);
	mlx_terminate(mlx->win);
	exit(EXIT_SUCCESS);
}

int	ft_err(char *str, t_map *map_data)
{
	if (str)
		ft_putendl_fd(str, 2);
	else if (errno)
		perror("[!] Error");
	ft_destroy_map_data(map_data);
	exit(EXIT_FAILURE);
}

void	ft_clear(void **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
			free(ptr[i++]);
		free(ptr);
	}
}

void	ft_destroy_map_data(t_map *map_data)
{
	if (map_data)
	{
		ft_clear((void **)map_data->map_check->elem);
		ft_clear((void **)map_data->map);
		free(map_data->no_text);
		free(map_data->so_text);
		free(map_data->we_text);
		free(map_data->ea_text);
	}
}

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

double	ft_cord_distance(t_cord *p1, t_cord *p2)
{
	return (sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2)));
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
