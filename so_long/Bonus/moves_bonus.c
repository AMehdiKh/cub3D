/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:33:58 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/15 03:23:32 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_right(t_mlx *mlx, int *x, int *y)
{
	if (mlx->map[*y][*x + 1] == '1')
	{
		ft_player_sprite(mlx, mlx->p_cord);
		return ;
	}
	if (mlx->map[*y][*x] != 'E')
		ft_draw_image(mlx, "./textures/space.png", *x, *y);
	if (mlx->map[*y][*x + 1] == 'C')
	{
		mlx->map[*y][*x + 1] = '0';
		--mlx->coin;
	}
	mlx->p_cord->x = ++*x;
	ft_player_sprite(mlx, mlx->p_cord);
	++mlx->moves;
}

void	ft_left(t_mlx *mlx, int *x, int *y)
{
	if (mlx->map[*y][*x - 1] == '1')
	{
		ft_player_sprite(mlx, mlx->p_cord);
		return ;
	}
	if (mlx->map[*y][*x] != 'E')
		ft_draw_image(mlx, "./textures/space.png", *x, *y);
	if (mlx->map[*y][*x - 1] == 'C')
	{
		mlx->map[*y][*x - 1] = '0';
		--mlx->coin;
	}
	mlx->p_cord->x = --*x;
	ft_player_sprite(mlx, mlx->p_cord);
	++mlx->moves;
}

void	ft_down(t_mlx *mlx, int *x, int *y)
{
	if (mlx->map[*y + 1][*x] == '1')
		return ;
	if (mlx->map[*y][*x] != 'E')
		ft_draw_image(mlx, "./textures/space.png", *x, *y);
	if (mlx->map[*y + 1][*x] == 'C')
	{
		mlx->map[*y + 1][*x] = '0';
		--mlx->coin;
	}
	mlx->p_cord->y = ++*y;
	ft_player_sprite(mlx, mlx->p_cord);
	++mlx->moves;
}

void	ft_up(t_mlx *mlx, int *x, int *y)
{
	if (mlx->map[*y - 1][*x] == '1')
		return ;
	if (mlx->map[*y][*x] != 'E')
		ft_draw_image(mlx, "./textures/space.png", *x, *y);
	if (mlx->map[*y - 1][*x] == 'C')
	{
		mlx->map[*y - 1][*x] = '0';
		--mlx->coin;
	}
	mlx->p_cord->y = --*y;
	ft_player_sprite(mlx, mlx->p_cord);
	++mlx->moves;
}

void	ft_esc(t_mlx *mlx, int x, int y)
{
	if ((x == mlx->e_cord->x && y == mlx->e_cord->y) && !mlx->coin)
	{
		mlx_terminate(mlx->win);
		ft_mlx_init(mlx, 816, 624);
		ft_draw_image(mlx, "./textures/go_win.png", 0, 0);
		mlx_key_hook(mlx->win, &ft_close_key, mlx);
		mlx_close_hook(mlx->win, &ft_close, mlx);
		mlx_loop(mlx->win);
	}
	else if ((x == mlx->x_cord->x && y == mlx->x_cord->y) && mlx->enemy)
	{
		mlx_terminate(mlx->win);
		ft_mlx_init(mlx, 600, 600);
		ft_draw_image(mlx, "./textures/go_lose.png", 0, 0);
		mlx_key_hook(mlx->win, &ft_close_key, mlx);
		mlx_close_hook(mlx->win, &ft_close, mlx);
		mlx_loop(mlx->win);
	}
	mlx_terminate(mlx->win);
	ft_clear((void **)mlx->map);
	exit(EXIT_SUCCESS);
}
