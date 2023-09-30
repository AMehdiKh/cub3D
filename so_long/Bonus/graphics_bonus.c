/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:15:41 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/15 00:43:14 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_graphics(t_mlx *mlx)
{
	mlx->mid_map = mlx->x / 2;
	mlx->str_x = (72 * mlx->mid_map) + 32;
	ft_mlx_init(mlx, mlx->x * 72, mlx->y * 72);
	ft_put_sprite(mlx);
	mlx_key_hook(mlx->win, &ft_hooks, mlx);
	mlx_close_hook(mlx->win, &ft_close, mlx);
	mlx_loop_hook(mlx->win, &ft_loop, mlx);
	mlx_loop(mlx->win);
}

void	ft_mlx_init(t_mlx *mlx, int x, int y)
{
	mlx->win = mlx_init(x, y, "Inferno", false);
	if (!mlx->win)
		ft_err(mlx->map, "\e[0;31mError: MinilibX initialization failed");
	mlx->img = mlx_new_image(mlx->win, x, y);
	if (!mlx->img)
	{
		mlx_terminate(mlx->win);
		ft_err(mlx->map, "\e[0;31mError: Creating new image failed");
	}
	if (mlx_image_to_window(mlx->win, mlx->img, 0, 0) < 0)
	{
		mlx_terminate(mlx->win);
		ft_err(mlx->map, "\e[0;31mError: Putting image to window failed");
	}
}

void	ft_put_sprite(t_mlx *mlx)
{
	int	x;
	int	y;

	y = -1;
	while (mlx->map[++y])
	{
		x = -1;
		while (mlx->map[y][++x])
		{
			if (mlx->map[y][x] == '0')
				ft_draw_image(mlx, "./textures/space.png", x, y);
			else if (mlx->map[y][x] == 'P')
				ft_draw_image(mlx, "./textures/star_right.png", x, y);
			else if (mlx->map[y][x] == 'E')
				ft_draw_image(mlx, "./textures/d_closed.png", x, y);
			else if (mlx->map[y][x] == 'C')
				ft_draw_image(mlx, "./textures/coin.png", x, y);
		}
	}
}

void	ft_hooks(mlx_key_data_t keydata, void *param)
{
	t_mlx	*mlx;
	int		x;
	int		y;

	mlx = param;
	x = mlx->p_cord->x;
	y = mlx->p_cord->y;
	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		mlx->key = keydata.key;
	if (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_UP)
			ft_up(mlx, &x, &y);
		else if (keydata.key == MLX_KEY_DOWN)
			ft_down(mlx, &x, &y);
		else if (keydata.key == MLX_KEY_LEFT)
			ft_left(mlx, &x, &y);
		else if (keydata.key == MLX_KEY_RIGHT)
			ft_right(mlx, &x, &y);
		if ((x == mlx->e_cord->x && y == mlx->e_cord->y && !mlx->coin)
			|| (x == mlx->x_cord->x && y == mlx->x_cord->y && mlx->enemy)
			|| keydata.key == MLX_KEY_ESCAPE)
			ft_esc(mlx, x, y);
	}
}

void	ft_loop(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	ft_torches_ani(mlx);
	ft_eye_ani(mlx);
	if (mlx->moves != mlx->last_move)
		ft_moves_str(mlx);
	if (mlx->coin != mlx->last_coin)
		ft_coins_str(mlx);
	if (mlx->enemy)
		ft_enemy(mlx);
}
