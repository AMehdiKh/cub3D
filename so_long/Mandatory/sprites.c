/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 06:37:44 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/04 17:05:15 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_draw_image(t_mlx *mlx, char *png_path, int x, int y)
{
	mlx_texture_t	*png;

	png = mlx_load_png(png_path);
	if (!png)
	{
		mlx_terminate(mlx->win);
		ft_err(mlx->map, "\e[0;31mError: Png load failed");
	}
	if (!mlx_draw_texture(mlx->img, png, x * 72, y * 72))
	{
		mlx_delete_texture(png);
		mlx_terminate(mlx->win);
		ft_err(mlx->map, "\e[0;31mError: drawing texture to the image failed");
	}
	mlx_delete_texture(png);
}

int	ft_exit_sprite(t_mlx *mlx, t_cord *e)
{
	if (mlx->coin)
	{
		if (e->x == mlx->p_cord->x && e->y == mlx->p_cord->y)
		{
			if (mlx->key == MLX_KEY_LEFT)
				ft_draw_image(mlx, "./textures/dc_left.png", e->x, e->y);
			else
				ft_draw_image(mlx, "./textures/dc_right.png", e->x, e->y);
			return (0);
		}
		else
			ft_draw_image(mlx, "./textures/d_closed.png", e->x, e->y);
	}
	else
		ft_draw_image(mlx, "./textures/d_open.png", e->x, e->y);
	return (1);
}

int	ft_star_sprite(t_mlx *mlx, t_cord *s)
{
	if (s->x == mlx->p_cord->x && s->y == mlx->p_cord->y)
	{
		if (mlx->key == MLX_KEY_LEFT)
			ft_draw_image(mlx, "./textures/star_left.png", s->x, s->y);
		else
			ft_draw_image(mlx, "./textures/star_right.png", s->x, s->y);
		return (0);
	}
	else
		ft_draw_image(mlx, "./textures/star.png", s->x, s->y);
	return (1);
}

void	ft_player_sprite(t_mlx *mlx, t_cord *p)
{
	int	star;
	int	exit;

	star = ft_star_sprite(mlx, mlx->s_cord);
	exit = ft_exit_sprite(mlx, mlx->e_cord);
	if (star && exit)
	{
		if (mlx->key == MLX_KEY_LEFT)
			ft_draw_image(mlx, "./textures/player_left.png", p->x, p->y);
		else
			ft_draw_image(mlx, "./textures/player_right.png", p->x, p->y);
	}
}
