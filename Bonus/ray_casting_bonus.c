/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:09:17 by ael-khel          #+#    #+#             */
/*   Updated: 2024/01/04 14:52:20 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	}
	else
	{
		ft_init_cord(ray->wall_hit, cast->v_insec->x, cast->v_insec->y);
		ray->ray_distance = cast->v_distance;
		ray->ray_type = V_RAY;
	}
	ft_init_ray_directions(ray, cast);
}

void	ft_init_ray_directions(t_ray *ray, t_casting *cast)
{
	ray->ray_up = cast->ray_up;
	ray->ray_down = cast->ray_down;
	ray->ray_right = cast->ray_right;
	ray->ray_left = cast->ray_left;
}

void	ft_ray_directions(t_casting *cast)
{
	cast->ray_down = cast->ray_angle > 0 && cast->ray_angle < M_PI;
	cast->ray_up = !cast->ray_down * -1;
	cast->ray_right = cast->ray_angle < 0.5 * M_PI
		|| cast->ray_angle > 1.5 * M_PI;
	cast->ray_left = !cast->ray_right * -1;
}

double	ft_cord_distance(t_cord *p1, t_cord *p2)
{
	return (sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2)));
}
