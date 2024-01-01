/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:20:45 by ael-khel          #+#    #+#             */
/*   Updated: 2024/01/01 16:56:44 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hooks(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx->win, MLX_KEY_W))
		ft_move_straight(mlx, 1);
	else if (mlx_is_key_down(mlx->win, MLX_KEY_S))
		ft_move_straight(mlx, -1);
	else if (mlx_is_key_down(mlx->win, MLX_KEY_D))
		ft_move_sides(mlx, 1);
	else if (mlx_is_key_down(mlx->win, MLX_KEY_A))
		ft_move_sides(mlx, -1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_RIGHT))
		ft_turn(mlx, 1);
	else if (mlx_is_key_down(mlx->win, MLX_KEY_LEFT))
		ft_turn(mlx, -1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_ESCAPE))
		ft_esc(mlx);
}

void	ft_move_straight(t_mlx *mlx, int pixel)
{
	double		x;
	double		y;

	x = mlx->player_data->player->x + cos(mlx->player_data->rotation_angle)
		* (pixel * MOVE_SPEED);
	y = mlx->player_data->player->y;
	if (mlx->map_data->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != '1')
		ft_init_cord(mlx->player_data->player, x, y);
	x = mlx->player_data->player->x;
	y = mlx->player_data->player->y + sin(mlx->player_data->rotation_angle)
		* (pixel * MOVE_SPEED);
	if (mlx->map_data->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != '1')
		ft_init_cord(mlx->player_data->player, x, y);
	ft_render_map(mlx);
}

void	ft_move_sides(t_mlx *mlx, int pixel)
{
	double	x;
	double	y;

	x = mlx->player_data->player->x;
	if (pixel == 1)
		y = mlx->player_data->player->y + sin(mlx->player_data->rotation_angle 
				+ M_PI / 2) * MOVE_SPEED;
	else
		y = mlx->player_data->player->y + sin(mlx->player_data->rotation_angle
				- M_PI / 2) * MOVE_SPEED;
	if (mlx->map_data->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != '1')
		ft_init_cord(mlx->player_data->player, x, y);
	y = mlx->player_data->player->y;
	if (pixel == 1)
		x = mlx->player_data->player->x + cos(mlx->player_data->rotation_angle
				+ M_PI / 2) * MOVE_SPEED;
	else
		x = mlx->player_data->player->x + cos(mlx->player_data->rotation_angle 
				- M_PI / 2) * MOVE_SPEED;
	if (mlx->map_data->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != '1')
		ft_init_cord(mlx->player_data->player, x, y);
	ft_render_map(mlx);
}

void	ft_turn(t_mlx *mlx, int pixel)
{
	t_player	*player_data;

	player_data = mlx->player_data;
	player_data->rotation_angle += (pixel * player_data->rotation_speed);
	ft_normalize_angle(&player_data->rotation_angle);
	ft_render_map(mlx);
}