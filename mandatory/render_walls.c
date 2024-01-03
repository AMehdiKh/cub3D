/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:56:41 by ael-khel          #+#    #+#             */
/*   Updated: 2024/01/03 21:17:45 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_load_textures(t_mlx *mlx)
{
	mlx->no_text = mlx_load_png(mlx->map_data->no_text);
	mlx->so_text = mlx_load_png(mlx->map_data->so_text);
	mlx->we_text = mlx_load_png(mlx->map_data->we_text);
	mlx->ea_text = mlx_load_png(mlx->map_data->ea_text);
	if (!mlx->no_text || !mlx->so_text || !mlx->we_text || !mlx->ea_text)
		ft_esc(mlx);
}

void	ft_init_ray_texture(t_mlx *mlx, t_ray *ray)
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

uint32_t	ft_get_pixel_color(t_ray *ray, int y_offset, int x_offset)
{
	int	pos;

	pos = (y_offset * ray->texture->width + x_offset) * BPP;
	if (pos < 0 || 
		pos > (int)(ray->texture->height * (ray->texture->width * BPP)) - BPP)
		return (0);
	return (ft_rgb(ray->texture->pixels[pos], ray->texture->pixels[pos + 1],
			ray->texture->pixels[pos + 2], ray->texture->pixels[pos + 3]));
}

void	ft_scale_cord_text(t_mlx *mlx, t_ray *ray, int x)
{
	double	x_offset;
	double	y_offset;
	int		line_height;
	int		y;

	line_height = ray->wall_bottom_pixel - ray->wall_top_pixel;
	y = ray->wall_top_pixel;
	if (ray->wall_top_pixel < 0)
		y = 0;
	if (ray->ray_type == H_RAY)
		x_offset = fmod(ray->wall_hit->x, TILE_SIZE) * ray->texture->width
			/ TILE_SIZE;
	else if (ray->ray_type == V_RAY)
		x_offset = fmod(ray->wall_hit->y, TILE_SIZE) * ray->texture->width
			/ TILE_SIZE;
	while (y < ray->wall_bottom_pixel && y < HEIGHT)
	{
		y_offset = (1 - ((double)(ray->wall_bottom_pixel - y) / line_height))
			* ray->texture->height;
		mlx_put_pixel(mlx->img, x, y,
			ft_get_pixel_color(ray, y_offset, x_offset));
		y++;
	}
}

void	ft_render_walls(t_mlx *mlx, t_ray *rays)
{
	double	dis_projection;
	double	projected_wall_height;
	int		wall_strip_height;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		ft_init_ray_texture(mlx, &rays[x]);
		rays[x].ray_distance *= cos(rays[x].ray_angle
				- mlx->player_data->rotation_angle);
		dis_projection = (WIDTH / 2) / tan(mlx->player_data->field_of_view / 2);
		projected_wall_height = (TILE_SIZE / rays[x].ray_distance)
			* dis_projection;
		wall_strip_height = (int)projected_wall_height;
		rays[x].wall_top_pixel = (HEIGHT / 2) - (wall_strip_height / 2);
		rays[x].wall_bottom_pixel = (HEIGHT / 2) + (wall_strip_height / 2);
		ft_scale_cord_text(mlx, &rays[x], x);
		++x;
	}
}
