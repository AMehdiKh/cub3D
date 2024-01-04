/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:51:42 by ael-khel          #+#    #+#             */
/*   Updated: 2024/01/04 14:52:20 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_mini_map(t_mlx *mlx)
{
	t_map	*map_data;
	t_cord	square[1];
	int		y;
	int		x;

	map_data = mlx->map_data;
	ft_scale_mini_map(mlx, map_data);
	y = 0;
	while (map_data->map[y])
	{
		x = 0;
		while (map_data->map[y][x])
		{
			ft_init_cord(square, x * TILE_SIZE, y * TILE_SIZE);
			if (map_data->map[y][x] == '1')
				ft_square(mlx, square, 0x772f1aff);
			else
				ft_square(mlx, square, 0x55a630ff);
			++x;
		}
		++y;
	}
	ft_p_square(mlx, mlx->player_data->player, 0xd90429FF, 2);
}

void	ft_scale_mini_map(t_mlx *mlx, t_map *map_data)
{
	int		width_limit;
	int		height_limit;
	double	scale;

	if (map_data->map_width >= WIDTH || map_data->map_height >= HEIGHT)
	{
		ft_putendl_fd("Error: The map is larger than it should be", 2);
		ft_esc(mlx);
	}
	width_limit = WIDTH / 4;
	height_limit = HEIGHT / 4;
	scale = 1;
	while (scale <= 256)
	{
		mlx->map_scale = 1 / scale;
		if (map_data->map_width * mlx->map_scale < width_limit
			&& map_data->map_height * mlx->map_scale < height_limit)
			return ;
		scale += scale ;
	}
	ft_putendl_fd("[!] Error: The map is larger than it should be", 2);
	ft_esc(mlx);
}

void	ft_square(t_mlx *mlx, t_cord *square, int color)
{
	int	x_start;
	int	y_start;
	int	x_end;
	int	y_end;

	y_start = square->y * mlx->map_scale;
	y_end = y_start + (TILE_SIZE * mlx->map_scale);
	x_end = (square->x * mlx->map_scale) + (TILE_SIZE * mlx->map_scale);
	while (y_start < y_end)
	{
		x_start = square->x * mlx->map_scale;
		while (x_start < x_end)
		{
			mlx_put_pixel(mlx->img, x_start, y_start, color);
			if (y_start == square->y * mlx->map_scale
				|| x_start == square->x * mlx->map_scale)
				mlx_put_pixel(mlx->img, x_start, y_start, 0x222222ff);
			++x_start;
		}
		++y_start;
	}
}

void	ft_p_square(t_mlx *mlx, t_cord *square, int color, int padding)
{
	int	x_start;
	int	y_start;
	int	x_end;
	int	y_end;

	y_start = square->y * mlx->map_scale - padding;
	y_end = square->y * mlx->map_scale + padding;
	x_end = square->x * mlx->map_scale + padding;
	while (y_start < y_end)
	{
		x_start = square->x * mlx->map_scale - padding;
		while (x_start < x_end)
		{
			mlx_put_pixel(mlx->img, x_start, y_start, color);
			++x_start;
		}
		++y_start;
	}
}
