/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_v_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:21:40 by ael-khel          #+#    #+#             */
/*   Updated: 2024/01/04 11:23:07 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calc_h_inter(t_casting *cast)
{
	cast->y_first = floor(cast->player->y / TILE_SIZE) * TILE_SIZE
		+ (TILE_SIZE * cast->ray_down);
	cast->x_first = cast->player->x
		+ (cast->y_first - cast->player->y) / tan(cast->ray_angle);
	cast->y_step = (TILE_SIZE * cast->ray_up) + (TILE_SIZE * cast->ray_down);
	cast->x_step = TILE_SIZE / tan(cast->ray_angle);
	if ((cast->ray_left && cast->x_step > 0)
		|| (cast->ray_right && cast->x_step < 0))
		cast->x_step *= -1;
}

void	ft_h_intersection(t_casting *cast)
{
	cast->h_found_wall = 0;
	ft_ray_directions(cast);
	ft_calc_h_inter(cast);
	ft_init_cord(cast->h_insec, cast->x_first, cast->y_first);
	while (cast->h_insec->y >= 0 && cast->h_insec->y < cast->height
		&& cast->h_insec->x >= 0 && cast->h_insec->x < cast->width)
	{
		cast->x_index = floor(cast->h_insec->x / TILE_SIZE);
		cast->y_index = floor((cast->h_insec->y + cast->ray_up) / TILE_SIZE);
		if (cast->y_index < 0)
			cast->y_index = 0;
		if (cast->x_index < (int)ft_strlen(cast->map[cast->y_index])
			&& cast->map[cast->y_index][cast->x_index] == '1')
		{
			cast->h_found_wall = 1;
			break ;
		}
		cast->h_insec->x += cast->x_step;
		cast->h_insec->y += cast->y_step;
	}
}

void	ft_calc_v_inter(t_casting *cast)
{
	cast->x_first = floor(cast->player->x / TILE_SIZE) * TILE_SIZE
		+ (TILE_SIZE * cast->ray_right);
	cast->y_first = cast->player->y
		+ (cast->x_first - cast->player->x) * tan(cast->ray_angle);
	cast->x_step = (TILE_SIZE * cast->ray_left) + (TILE_SIZE * cast->ray_right);
	cast->y_step = TILE_SIZE * tan(cast->ray_angle);
	if ((cast->ray_up && cast->y_step > 0)
		|| (cast->ray_down && cast->y_step < 0))
		cast->y_step *= -1;
}

void	ft_v_intersection(t_casting *cast)
{
	cast->v_found_wall = 0;
	ft_ray_directions(cast);
	ft_calc_v_inter(cast);
	ft_init_cord(cast->v_insec, cast->x_first, cast->y_first);
	while (cast->v_insec->y >= 0 && cast->v_insec->y < cast->height
		&& cast->v_insec->x >= 0 && cast->v_insec->x < cast->width)
	{
		cast->x_index = floor((cast->v_insec->x + cast->ray_left) / TILE_SIZE);
		cast->y_index = floor(cast->v_insec->y / TILE_SIZE);
		if (cast->x_index < 0)
			cast->x_index = 0;
		if (cast->x_index < (int)ft_strlen(cast->map[cast->y_index])
			&& cast->map[cast->y_index][cast->x_index] == '1')
		{
			cast->v_found_wall = 1;
			break ;
		}
		cast->v_insec->y += cast->y_step;
		cast->v_insec->x += cast->x_step;
	}
}
