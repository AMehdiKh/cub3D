/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:56:41 by ael-khel          #+#    #+#             */
/*   Updated: 2023/12/30 19:17:09 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_ray_texture(t_mlx *mlx, t_ray *ray)
{
	if (ray->ray_type == H_RAY && ray->ray_down)
		ray->texture = mlx->so_text;
	else if (ray->ray_type == H_RAY && ray->ray_up)
		ray->texture = mlx->no_text;
	else if (ray->ray_type == V_RAY && ray->ray_left)
		ray->texture = mlx->we_text;
	else if (ray->ray_type == V_RAY && ray->ray_right)
		ray->texture = mlx->ea_text;
}

uint32_t get_color(t_ray *ray, int y_offset , int x_offset)
{
	int pos;
	
	pos = (y_offset * ray->texture->width + x_offset) * 4;
	if (pos < 0 || pos > (int)(ray->texture->height * (ray->texture->width * 4)) - 4)
		return (0);
	return (ft_pixel(ray->texture->pixels[pos], ray->texture->pixels[pos + 1],
		ray->texture->pixels[pos + 2], ray->texture->pixels[pos + 3]));
}

void scale_cord_text(t_mlx *mlx, int top_pixel, int bot_pixel, t_ray *rays, int i)
{
	float x_offset;
	float y_offset;
	int line_height;

	int y = top_pixel;
	if (top_pixel < 0)
		y = 0;
	if (rays->ray_type == H_RAY)
		x_offset = fmod(rays->wall_hit->x, TILE_SIZE) * rays->texture->width / TILE_SIZE;
	else if (rays->ray_type == V_RAY)
		x_offset = fmod(rays->wall_hit->y, TILE_SIZE) * rays->texture->width / TILE_SIZE;
	while(y < bot_pixel && y < HEIGHT)
	{
		line_height = bot_pixel - top_pixel;
		y_offset = (1 - ((float)(bot_pixel - y) / line_height)) * rays->texture->height;
		mlx_put_pixel(mlx->img, i, y, get_color(rays, y_offset, x_offset));
		y++;
	}
}

void	ft_render_walls(t_mlx *mlx, t_ray *rays)      
{
	double	dis_projection;
	double	projected_wall_height;
	double	wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		ft_ray_texture(mlx, &rays[i]);
		rays[i].ray_distance *= cos(rays[i].ray_angle - mlx->player_data->rotation_angle);
		dis_projection = (WIDTH / 2) / tan(mlx->player_data->field_of_view / 2);
		projected_wall_height = (TILE_SIZE / rays[i].ray_distance) * dis_projection;
		wall_strip_height = (TILE_SIZE / rays[i].ray_distance) * (((double)HEIGHT / 2) / (tan(30 * M_PI / 180)));
		wall_top_pixel = (HEIGHT / 2) - (wall_strip_height / 2);
		wall_bottom_pixel = (HEIGHT / 2) + (wall_strip_height / 2);
		scale_cord_text(mlx, wall_top_pixel, wall_bottom_pixel,&rays[i], i);
		++i;
	}
}