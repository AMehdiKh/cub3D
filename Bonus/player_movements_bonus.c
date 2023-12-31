/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:20:45 by ael-khel          #+#    #+#             */
/*   Updated: 2024/01/05 02:35:01 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_player_movements(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx->win, MLX_KEY_W))
		ft_move_straight(mlx, 1);
	else if (mlx_is_key_down(mlx->win, MLX_KEY_S))
		ft_move_straight(mlx, -1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_D))
		ft_move_sides(mlx, 1);
	else if (mlx_is_key_down(mlx->win, MLX_KEY_A))
		ft_move_sides(mlx, -1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_RIGHT))
		ft_turn(mlx, 1);
	else if (mlx_is_key_down(mlx->win, MLX_KEY_LEFT))
		ft_turn(mlx, -1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_ESCAPE))
		ft_esc(mlx);
	ft_render_map(mlx);
}

void	ft_move_straight(t_mlx *mlx, int pixel)
{
	double	x;
	double	y;

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
}

void	ft_turn(t_mlx *mlx, int pixel)
{
	t_player	*player_data;

	player_data = mlx->player_data;
	player_data->rotation_angle += (pixel * player_data->rotation_speed);
	ft_normalize_angle(&player_data->rotation_angle);
}

void	ft_mouse_rotation(double xpos, double ypos, void *param)
{
	t_mlx		*mlx;
	static int	old_xpos;
	static int	i;

	mlx = param;
	if (old_xpos == 0)
		old_xpos = xpos;
	if (i++ == 1)
	{
		if (xpos < old_xpos
			&& xpos > 0 && xpos < WIDTH && ypos > 0 && ypos < HEIGHT)
			mlx->player_data->rotation_angle
				-= (mlx->player_data->rotation_speed * 1);
		if (xpos > old_xpos
			&& xpos > 0 && xpos < WIDTH && ypos > 0 && ypos < HEIGHT)
			mlx->player_data->rotation_angle
				+= (mlx->player_data->rotation_speed * 1);
		ft_normalize_angle(&mlx->player_data->rotation_angle);
		i = 0;
		old_xpos = xpos;
		ft_render_map(mlx);
	}
}
