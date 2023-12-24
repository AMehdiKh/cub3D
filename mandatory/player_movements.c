/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:20:45 by ael-khel          #+#    #+#             */
/*   Updated: 2023/12/24 18:45:08 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hooks(void *param)
{
	t_mlx	*mlx;
	t_cord  cor;
	
	ft_init_cord(&cor,0,0);
	mlx = param;
	if (mlx_is_key_down(mlx->win, MLX_KEY_W))
		ft_move_straight(mlx, 1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_S))
		ft_move_straight(mlx, -1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_D))
		ft_move_sides(mlx, 1, cor);
	if (mlx_is_key_down(mlx->win, MLX_KEY_A))
		ft_move_sides(mlx, -1, cor);
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
	if (mlx->map_data->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != 1)
		ft_init_cord(player_data->player, x, y);
	x = player_data->player->x;
	y = (player_data->player->y + sin(player_data->rotation_angle)
			* (pixel * MOVE_SPEED));
	if (mlx->map_data->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != 1)
		ft_init_cord(player_data->player, x, y);
	ft_render_map(mlx);
}

void	ft_move_sides(t_mlx *mlx, int pixel, t_cord cor)
{

	cor.y = mlx->player_data->player->y;
	if (pixel == -1)
		cor.x = mlx->player_data->player->x + cos(mlx->player_data->rotation_angle 
			- (M_PI/2)) *  MOVE_SPEED;
	else
		cor.x = mlx->player_data->player->x + cos(mlx->player_data->rotation_angle 
			+ (M_PI/2)) *  MOVE_SPEED;
	if (mlx->map_data->map[(int)(cor.y / TILE_SIZE)][(int)(cor.x / TILE_SIZE)] != 1)
		ft_init_cord(mlx->player_data->player, cor.x, cor.y);
	cor.x = mlx->player_data->player->x;
	if (pixel == 1)
		cor.y = mlx->player_data->player->y + sin(mlx->player_data->rotation_angle 
			+ (M_PI/2)) *  MOVE_SPEED;
	else
		cor.y = mlx->player_data->player->y + sin(mlx->player_data->rotation_angle 
			- (M_PI/2)) *  MOVE_SPEED;
	if (mlx->map_data->map[(int)(cor.y / TILE_SIZE)][(int)(cor.x / TILE_SIZE)] != 1)
		ft_init_cord(mlx->player_data->player, cor.x, cor.y);
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
