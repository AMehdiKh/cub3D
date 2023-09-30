/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:33:58 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/15 03:30:19 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	ft_printf("\e[0;32mPlayer move : %d\n", ++mlx->moves);
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
	ft_printf("\e[0;32mPlayer move : %d\n", ++mlx->moves);
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
	ft_printf("\e[0;32mPlayer move : %d\n", ++mlx->moves);
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
	ft_printf("\e[0;32mPlayer move : %d\n", ++mlx->moves);
}

void	ft_esc(t_mlx *mlx, int x, int y)
{
	if ((x == mlx->e_cord->x && y == mlx->e_cord->y) && !mlx->coin)
	{
		ft_printf("\n\e[0;33mYou Won!! I hope you enjoyed the game ❤️\n");
		ft_printf("\e[0;31mNOW GIVE ME MY 125/100!!\n");
	}
	mlx_terminate(mlx->win);
	ft_clear((void **)mlx->map);
	exit(EXIT_SUCCESS);
}
