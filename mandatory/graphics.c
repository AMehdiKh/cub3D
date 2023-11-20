/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:45:21 by ael-khel          #+#    #+#             */
/*   Updated: 2023/11/17 23:56:16 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <bits/posix2_lim.h>
#include <cstdint>
#include <math.h>
#include <stdio.h>

void	ft_graphics(t_map *map_data)
{
	t_mlx	mlx[1];

	ft_bzero(mlx, sizeof(mlx));
	mlx->map_data = map_data;
	ft_init_mlx(mlx, map_data->map_width, map_data->map_height);
	ft_mini_map(mlx);
	mlx_loop_hook(mlx->win, &ft_hooks, mlx);
	mlx_close_hook(mlx->win, &ft_esc, mlx);
	mlx_loop(mlx->win);
	ft_esc(mlx);
}

void	ft_init_mlx(t_mlx *mlx, int x, int y)
{
	mlx->win = mlx_init(x * TILE_SIZE, y * TILE_SIZE, "Cub3D", false);
	if (!mlx->win)
		ft_err("Error: MinilibX initialization failed", mlx->map_data);
	mlx->img = mlx_new_image(mlx->win, x * TILE_SIZE, y * TILE_SIZE);
	if (!mlx->img)
	{
		mlx_terminate(mlx->win);
		ft_err("Error: Creating new image failed", mlx->map_data);
	}
	if (mlx_image_to_window(mlx->win, mlx->img, 0, 0) < 0)
	{
		mlx_terminate(mlx->win);
		ft_err("Error: Putting image to window failed", mlx->map_data);
	}
	mlx->player_data->player = mlx->map_data->character;
	mlx->player_data->rotation_angle = ft_character_direction(mlx->map_data);
	mlx->player_data->rotation_speed = 2 * (M_PI / 180);
	mlx->player_data->move_speed = 3;
	mlx->player_data->field_of_view = 40 * (M_PI / 180);
	mlx->player_data->wall_strip_width = 1;
	mlx->player_data->num_rays = (x * TILE_SIZE) / mlx->player_data->wall_strip_width;
}

void	ft_mini_map(t_mlx *mlx)
{
	t_map	*map_data;
	t_cord	square[1];
	int		y;
	int		x;

	map_data = mlx->map_data;
	y = 0;
	while (map_data->map[y])
	{
		x = 0;
		while (map_data->map[y][x])
		{
			ft_init_cord(square, x * TILE_SIZE, y * TILE_SIZE);
			if (map_data->map[y][x] == '1')
				ft_square(mlx, square, 0xE04B5AFF);
			else
				ft_square(mlx, square, 0xE49756FF);
			++x;
		}
		++y;
	}
	ft_player_square(mlx, mlx->player_data->player, 0x9A4C68FF, 4);
	ft_cast_rays(mlx);
}

void	ft_cast_rays(t_mlx	*mlx)
{
	t_player	*player_data;
	t_cord		wall_hit[1];
	double		ray_angle;
	int			i;

	player_data = mlx->player_data;
	ray_angle = player_data->rotation_angle - (player_data->field_of_view / 2);
	i = 0;
	while (ray_angle < player_data->rotation_angle + (player_data->field_of_view / 2))
	{

		// ft_V_intersection();
		ft_H_intersection(mlx->map_data->map, player_data);
		// wall_hitft_nearest_point();
		dda(mlx, player_data->player, wall_hit);
		ray_angle += player_data->field_of_view / player_data->num_rays;
		++i;
	}
}

void	ft_H_intersection(char **map, t_cord *player, double ray_angle)
{
	t_cord	intersection[1];
	int		ray_facing_up;
	int		ray_facing_down;
	int		ray_facing_right;
	int		ray_facing_left;
	int		x_step;
	int		y_step;
	int		x_first;
	int		y_first;

	ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
	ray_facing_up = !ray_facing_down * -1;
	ray_facing_right = ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI;
	ray_facing_left = !ray_facing_right * -1;

	x_step = (TILE_SIZE / tan(ray_angle) * ray_facing_left) + (TILE_SIZE / tan(ray_angle) * ray_facing_right);
	y_step = (TILE_SIZE * ray_facing_up) + (TILE_SIZE * ray_facing_down);
	y_first = (player->y / TILE_SIZE) * TILE_SIZE + (TILE_SIZE * ray_facing_down);
	x_first = player->x + (ft_abs(y_first - player->y) / tan(ray_angle) * ray_facing_left) + (ft_abs(y_first - player->y) / tan(ray_angle) * ray_facing_right);
	ft_init_cord(intersection, x_first, y_first);
	while (map[intersection->y / TILE_SIZE][intersection->x / TILE_SIZE] != '1')
	{
		intersection->x += x_step;
		intersection->y += y_step;
	}
}
int	ft_abs(int value)
{
	if (value < 0)
		return (-value);
	return (value);
}

void	ft_cast_rays(t_mlx	*mlx)
{
	t_player	*player_data;
	double		ray_angle;
	int			i;
	int			x;
	int			y;

	player_data = mlx->player_data;
	ray_angle = (player_data->rotation_angle - (player_data->field_of_view / 2));
	ray_angle = ft_normalize_angle(ray_angle);
	i = 0;
	while (i < player_data->num_rays)
	{
		x = mlx->player_data->player->x + cos(ray_angle) * 100;
		y = mlx->player_data->player->y + sin(ray_angle) * 100;
		dda(mlx, player_data->player->x, player_data->player->y, x, y);
		ray_angle += player_data->field_of_view / player_data->num_rays;
		ray_angle = ft_normalize_angle(ray_angle);
		++i;
	}
	printf("%F\n", ray_angle);
}

double	ft_normalize_angle(double angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

void	ft_player_square(t_mlx *mlx, t_cord *square, int color, int padding)
{
	int	x_start;
	int	y_start;
	int	x_end;
	int	y_end;

	y_start = square->y - padding;
	y_end = square->y + padding;
	x_end = square->x + padding;
	while (y_start < y_end)
	{
		x_start = square->x - padding;
		while (x_start < x_end)
		{
			mlx_put_pixel(mlx->img, x_start, y_start, color);
			++x_start;
		}
		++y_start;
	}
}

void	ft_square(t_mlx *mlx, t_cord *square, int color)
{
	int	x_start;
	int	y_start;
	int	x_end;
	int	y_end;

	y_start = square->y;
	y_end = square->y + TILE_SIZE;
	x_end = square->x + TILE_SIZE;
	while (y_start < y_end)
	{
		x_start = square->x;
		while (x_start < x_end)
		{
			mlx_put_pixel(mlx->img, x_start, y_start, color);
			if (y_start % TILE_SIZE == 0 || x_start % TILE_SIZE == 0)
				mlx_put_pixel(mlx->img, x_start, y_start, 0x222222FF);
			++x_start;
		}
		++y_start;
	}
}

double	ft_character_direction(t_map *map_data)
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

void	ft_hooks(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx->win, MLX_KEY_W))
		ft_move_straight(mlx, 1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_S))
		ft_move_straight(mlx, -1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_D))
		ft_move_sides(mlx, 1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_A))
		ft_move_sides(mlx, -1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_RIGHT))
		ft_turn(mlx, 1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_LEFT))
		ft_turn(mlx, -1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_ESCAPE))
		ft_esc(mlx);
}

void	ft_move_sides(t_mlx *mlx, int pixel)
{
	int			x;
	int			y;

	x = (mlx->player_data->player->x + pixel * mlx->player_data->move_speed);
	y = (mlx->player_data->player->y);
	if (ft_strchr("NEWS0", mlx->map_data->map[y / TILE_SIZE][x / TILE_SIZE]))
	{
		mlx->player_data->player->x = x;
		ft_mini_map(mlx);
	}
}

void	ft_move_straight(t_mlx *mlx, int pixel)
{
	t_player	*player_data;
	int			x;
	int			y;

	player_data = mlx->player_data;
	x = (player_data->player->x + cos(player_data->rotation_angle)
			* (pixel * player_data->move_speed));
	y = (player_data->player->y + sin(player_data->rotation_angle)
			* (pixel * player_data->move_speed));
	if (ft_strchr("NEWS0", mlx->map_data->map[y / TILE_SIZE][x / TILE_SIZE]))
	{
		ft_init_cord(player_data->player, x, y);
		ft_mini_map(mlx);
	}
}

void	ft_turn(t_mlx *mlx, int pixel)
{
	t_player	*player_data;

	player_data = mlx->player_data;
	player_data->rotation_angle += (pixel * player_data->rotation_speed);
	ft_mini_map(mlx);
}

void	ft_init_cord(t_cord *cord, int x, int y)
{
	cord->x = x;
	cord->y = y;
}

void	ft_esc(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	ft_destroy_map_data(mlx->map_data);
	mlx_terminate(mlx->win);
	exit(EXIT_SUCCESS);
}
