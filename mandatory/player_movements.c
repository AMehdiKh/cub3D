/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:20:45 by ael-khel          #+#    #+#             */
/*   Updated: 2023/12/20 15:31:17 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hooks(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx->win, MLX_KEY_W))
		ft_move_straight(mlx, 1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_S))
		ft_move_straight(mlx, -1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_D))
		ft_move_sides(mlx, -1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_A))
		ft_move_sides(mlx, 1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_RIGHT))
		ft_turn(mlx, 1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_LEFT))
		ft_turn(mlx, -1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_ESCAPE))
		ft_esc(mlx);
}

void	ft_move_straight(t_mlx *mlx, int pixel)
{
	t_player	*player_data;
	double		x;
	double		y;

	player_data = mlx->player_data;
	x = (player_data->player->x + cos(player_data->rotation_angle)
			* (pixel * MOVE_SPEED));
	y = player_data->player->y;
	if (ft_strchr("NEWS0", mlx->map_data->map[y / TILE_SIZE][x / TILE_SIZE]))
	{
		ft_init_cord(player_data->player, x, y);
		ft_render_map(mlx);
	}
	x = player_data->player->x;
	y = (player_data->player->y + sin(player_data->rotation_angle)
			* (pixel * MOVE_SPEED));
	if (ft_strchr("NEWS0", mlx->map_data->map[y / TILE_SIZE][x / TILE_SIZE]))
	{
		ft_init_cord(player_data->player, x, y);
		ft_render_map(mlx);
	}
}

void	ft_move_sides(t_mlx *mlx, int pixel)
{
	t_cord	*player;
	double	x;
	double	y;

	player = mlx->player_data->player;
	x = player->x + sin(mlx->player_data->rotation_angle)
		* (pixel * MOVE_SPEED);
	y = player->y;
	if (ft_strchr("NEWS0", mlx->map_data->map[y / TILE_SIZE][x / TILE_SIZE]))
	{
		ft_init_cord(player, x, y);
		ft_render_map(mlx);
	}
	x = player->x;
	y = player->y + cos(mlx->player_data->rotation_angle)
		* (pixel * MOVE_SPEED);
	if (ft_strchr("NEWS0", mlx->map_data->map[y / TILE_SIZE][x / TILE_SIZE]))
	{
		ft_init_cord(player, x, y);
		ft_render_map(mlx);
	}
}

void	ft_turn(t_mlx *mlx, int pixel)
{
	t_player	*player_data;

	player_data = mlx->player_data;
	player_data->rotation_angle += (pixel * player_data->rotation_speed);
	ft_normalize_angle(&player_data->rotation_angle);
	ft_render_map(mlx);
}
