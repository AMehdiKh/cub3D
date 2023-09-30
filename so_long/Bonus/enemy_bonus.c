/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 04:23:47 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/15 06:23:36 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_enemy(t_mlx *mlx)
{
	static int	clock;

	if (clock % 20 == 0)
		ft_check_enemy(mlx, mlx->x_cord->x, mlx->x_cord->y);
	++clock;
}

void	ft_check_enemy(t_mlx *mlx, int x, int y)
{
	if (ft_valid_enemy(mlx, 1, x + 1, y))
		ft_emove(mlx, x + 1, y);
	if (ft_valid_enemy(mlx, 1, x + 1, y - 1))
		ft_emove(mlx, x + 1, y - 1);
	if (ft_valid_enemy(mlx, 1, x - 1, y - 1))
		ft_emove(mlx, x - 1, y - 1);
	if (ft_valid_enemy(mlx, 1, x, y + 1))
		ft_emove(mlx, x, y + 1);
	if (ft_valid_enemy(mlx, 0, x - 1, y))
		ft_emove(mlx, x - 1, y);
	if (ft_valid_enemy(mlx, 0, x - 1, y + 1))
		ft_emove(mlx, x - 1, y + 1);
	if (ft_valid_enemy(mlx, 0, x + 1, y + 1))
		ft_emove(mlx, x + 1, y + 1);
	if (ft_valid_enemy(mlx, 0, x, y - 1))
		ft_emove(mlx, x, y - 1);
}

int	ft_valid_enemy(t_mlx *mlx, int index, int x, int y)
{
	int		px;
	int		py;

	mlx->random = rand() % 2;
	px = mlx->p_cord->x;
	py = mlx->p_cord->y;
	return ((mlx->map[y][x] != '1' && index == mlx->random)
	|| (x == px && y == py));
}

void	ft_emove(t_mlx *mlx, int x, int y)
{
	int		pre_x;
	int		pre_y;

	pre_x = mlx->x_cord->x;
	pre_y = mlx->x_cord->y;
	mlx->x_cord->x = x;
	mlx->x_cord->y = y;
	if (mlx->map[pre_y][pre_x] == 'C')
		ft_draw_image(mlx, "./textures/coin.png", pre_x, pre_y);
	else if (mlx->map[pre_y][pre_x] == 'E')
		ft_exit_sprite(mlx, mlx->e_cord);
	else if (mlx->map[pre_y][pre_x] == 'P')
		ft_draw_image(mlx, "./textures/star.png", pre_x, pre_y);
	else
		ft_draw_image(mlx, "./textures/space.png", pre_x, pre_y);
	ft_draw_image(mlx, "./textures/enemy.png", x, y);
	if (mlx->p_cord->x == x && mlx->p_cord->y == y)
		ft_esc(mlx, x, y);
}
