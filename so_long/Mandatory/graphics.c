/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:15:41 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/15 06:27:56 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_graphics(t_mlx *mlx)
{
	ft_mlx_init(mlx, mlx->x * 72, mlx->y * 72);
	ft_put_sprite(mlx);
	mlx_key_hook(mlx->win, &ft_hooks, mlx);
	mlx_close_hook(mlx->win, &ft_close, mlx);
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
			if (y == 0 || !(mlx->map[y + 1]) || x == 0 || !(mlx->map[y][x + 1]))
				ft_draw_image(mlx, "./textures/torch0.png", x, y);
			else if (mlx->map[y][x] == '0')
				ft_draw_image(mlx, "./textures/space.png", x, y);
			else if (mlx->map[y][x] == 'P')
				ft_draw_image(mlx, "./textures/star_right.png", x, y);
			else if (mlx->map[y][x] == 'E')
				ft_draw_image(mlx, "./textures/d_closed.png", x, y);
			else if (mlx->map[y][x] == 'C')
				ft_draw_image(mlx, "./textures/coin.png", x, y);
			else if (mlx->map[y][x] == '1')
				ft_draw_image(mlx, "./textures/eye_left.png", x, y);
		}
	}
}

void	ft_hooks(mlx_key_data_t keydata, void *param)
{
	t_mlx		*mlx;
	int			x;
	int			y;

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
		if ((y == mlx->e_cord->y && x == mlx->e_cord->x && !mlx->coin)
			|| keydata.key == MLX_KEY_ESCAPE)
			ft_esc(mlx, x, y);
	}
}

void	ft_close(void *param)
{
	ft_esc(param, 0, 0);
}
