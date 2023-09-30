/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:38:18 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/15 06:19:12 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_torches_ani(t_mlx *mlx)
{
	char		*str[4];
	static int	clock;
	static int	i;

	if (mlx->coin)
	{
		if (clock % 8 == 0)
		{
			str[0] = "./textures/torch0.png";
			str[1] = "./textures/torch1.png";
			str[2] = "./textures/torch2.png";
			str[3] = "./textures/torch3.png";
			ft_torches(mlx, str[i++]);
			if (i == 4)
				i = 0;
		}
		++clock;
	}
	else if (!mlx->coin && clock)
	{
		ft_torches(mlx, "./textures/torch4.png");
		clock = 0;
	}
}

void	ft_torches(t_mlx *mlx, char *str)
{
	int	x;
	int	y;

	x = -1;
	while (++x < mlx->x)
	{	
		if (mlx->mid_map == x)
		{
			ft_draw_image(mlx, "./textures/moves.png", x, 0);
			ft_draw_image(mlx, "./textures/moves.png", x, mlx->y - 1);
			continue ;
		}
		ft_draw_image(mlx, str, x, 0);
		ft_draw_image(mlx, str, x, mlx->y - 1);
	}
	y = -1;
	while (++y < mlx->y)
	{
		ft_draw_image(mlx, str, 0, y);
		ft_draw_image(mlx, str, mlx->x - 1, y);
	}
}

void	ft_eye_ani(t_mlx *mlx)
{
	char		*str[2];
	static int	clock;
	static int	eye;
	int			x;
	int			y;

	str[0] = "./textures/eye_left.png";
	str[1] = "./textures/eye_right.png";
	if (clock % 60 == 0)
	{
		y = 0;
		while (++y < mlx->y - 1)
		{
			x = 0;
			while (++x < mlx->x - 1)
				if (mlx->map[y][x] == '1')
					ft_draw_image(mlx, str[eye], x, y);
		}
		eye += 1;
		if (eye == 2)
			eye = 0;
	}
	++clock;
}

void	ft_moves_str(t_mlx *mlx)
{
	char	*str;
	int		px;

	px = 0;
	if (mlx->moves > 999)
		px = 15;
	else if (mlx->moves > 99)
		px = 10;
	else if (mlx->moves > 9)
		px = 5;
	if (mlx->moves_img)
		mlx_delete_image(mlx->win, mlx->moves_img);
	str = ft_itoa(mlx->moves);
	if (!str)
		ft_close(mlx);
	mlx->moves_img = mlx_put_string(mlx->win, str, mlx->str_x - px, 38);
	mlx->last_move = mlx->moves;
	free(str);
}

void	ft_coins_str(t_mlx *mlx)
{
	char	*str;
	int		str_y;
	int		px;

	px = 0;
	if (mlx->coin > 99)
		px = 10;
	else if (mlx->coin > 9)
		px = 5;
	if (mlx->coins_img)
		mlx_delete_image(mlx->win, mlx->coins_img);
	str = ft_itoa(mlx->coin);
	if (!str)
		ft_close(mlx);
	str_y = ((mlx->y - 1) * 72) + 38;
	mlx->coins_img = mlx_put_string(mlx->win, str, mlx->str_x - px, str_y);
	mlx->last_coin = mlx->coin;
	free(str);
}
