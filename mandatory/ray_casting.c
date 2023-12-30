/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:09:17 by ael-khel          #+#    #+#             */
/*   Updated: 2023/12/27 19:22:14 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LibFT/libft.h"
#include "cub3d.h"
#include <stdio.h>

void	ft_cast_rays(t_mlx *mlx, t_ray *rays)
{
	t_player	*player_data;
	t_casting	cast[1];
	int			i;

	player_data = mlx->player_data;
	cast->width = mlx->map_data->map_width;
	cast->height = mlx->map_data->map_height;
	cast->map = mlx->map_data->map;
	cast->player = player_data->player;
	cast->ray_angle = player_data->rotation_angle
		- player_data->field_of_view / 2;
	i = 0;
	while (i < WIDTH)
	{
		rays[i].ray_angle = ft_normalize_angle(&cast->ray_angle);
		ft_wall_hit((rays + i), cast);
		cast->ray_angle += player_data->field_of_view / WIDTH;
		++i;
	}
}

void	ft_wall_hit(t_ray *ray, t_casting *cast)
{
	ft_h_intersection(cast);
	ft_v_intersection(cast);
	ray->ray_down = cast->ray_down;
	ray->ray_up = cast->ray_up;
	ray->ray_left = cast->ray_left;
	ray->ray_right = cast->ray_right;
	if (cast->h_found_wall)
		cast->h_distance = ft_cord_distance(cast->player, cast->h_insec);
	else
		cast->h_distance = INT_MAX;
	if (cast->v_found_wall)
		cast->v_distance = ft_cord_distance(cast->player, cast->v_insec);
	else
		cast->v_distance = INT_MAX;
	if (cast->h_distance <= cast->v_distance)
	{
		ft_init_cord(ray->wall_hit, cast->h_insec->x, cast->h_insec->y);
		ray->ray_distance = cast->h_distance;
		ray->ray_type = H_RAY;
		ray->color = 0x48bfe3ff;
	}
	else
	{
		ft_init_cord(ray->wall_hit, cast->v_insec->x, cast->v_insec->y);
		ray->ray_distance = cast->v_distance;
		ray->ray_type = V_RAY;
		ray->color = 0xfb8500ff;
	}
}

void	ft_v_intersection(t_casting *cast)
{
	cast->v_found_wall = 0;
	ft_ray_directions(cast);
	cast->x_first = floor(cast->player->x / TILE_SIZE) * TILE_SIZE
		+ (TILE_SIZE * cast->ray_right);
	cast->y_first = cast->player->y
		+ (cast->x_first - cast->player->x) * tan(cast->ray_angle);
	cast->y_step = TILE_SIZE * tan(cast->ray_angle);
	if ((cast->ray_up && cast->y_step > 0)
		|| (cast->ray_down && cast->y_step < 0))
		cast->y_step *= -1;
	cast->x_step = (TILE_SIZE * cast->ray_left) + (TILE_SIZE * cast->ray_right);
	ft_init_cord(cast->v_insec, cast->x_first, cast->y_first);
	while (cast->v_insec->y >= 0 && cast->v_insec->y < cast->height
		&& cast->v_insec->x >= 0 && cast->v_insec->x < cast->width)
	{
		cast->x_index = floor((cast->v_insec->x + cast->ray_left) / TILE_SIZE);
		cast->y_index = floor(cast->v_insec->y / TILE_SIZE);
		if (cast->map[cast->y_index][cast->x_index] == '1')
		{
			cast->v_found_wall = 1;
			break ;
		}
		cast->v_insec->y += cast->y_step;
		cast->v_insec->x += cast->x_step;
	}
}

void	ft_h_intersection(t_casting *cast)
{
	cast->h_found_wall = 0;
	ft_ray_directions(cast);
	cast->y_first = floor(cast->player->y / TILE_SIZE) * TILE_SIZE
		+ (TILE_SIZE * cast->ray_down);
	cast->x_first = cast->player->x
		+ (cast->y_first - cast->player->y) / tan(cast->ray_angle);
	cast->y_step = (TILE_SIZE * cast->ray_up) + (TILE_SIZE * cast->ray_down);
	cast->x_step = TILE_SIZE / tan(cast->ray_angle);
	if ((cast->ray_left && cast->x_step > 0)
		|| (cast->ray_right && cast->x_step < 0))
		cast->x_step *= -1;
	ft_init_cord(cast->h_insec, cast->x_first, cast->y_first);
	while (cast->h_insec->y >= 0 && cast->h_insec->y < cast->height
		&& cast->h_insec->x >= 0 && cast->h_insec->x < cast->width)
	{
		cast->x_index = floor(cast->h_insec->x / TILE_SIZE);
		cast->y_index = floor((cast->h_insec->y + cast->ray_up) / TILE_SIZE);
		if (cast->y_index < 0)
			cast->y_index = 0;
		// printf("Ypixel = %F, Yindex = %d\nXpixel = %F, Xindex = %d\nwidth = %d, height = %d\n", cast->h_insec->y, cast->y_index, cast->h_insec->x, cast->x_index, cast->width, cast->height);
		if (cast->x_index < (int)ft_strlen(cast->map[cast->y_index]) && cast->map[cast->y_index][cast->x_index] == '1')
		{
			cast->h_found_wall = 1;
			break ;
		}
		cast->h_insec->x += cast->x_step;
		cast->h_insec->y += cast->y_step;
	}
}

void	ft_ray_directions(t_casting *cast)
{
	cast->ray_down = cast->ray_angle > 0 && cast->ray_angle < M_PI;
	cast->ray_up = !cast->ray_down * -1;
	cast->ray_right = cast->ray_angle < 0.5 * M_PI
		|| cast->ray_angle > 1.5 * M_PI;
	cast->ray_left = !cast->ray_right * -1;
}