/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:56:41 by ael-khel          #+#    #+#             */
/*   Updated: 2024/01/05 21:16:33 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_load_textures(t_mlx *mlx)
{
	mlx->no_text = mlx_load_png(mlx->map_data->no_text);
	if (!mlx->no_text)
		ft_esc(mlx);
	mlx->so_text = mlx_load_png(mlx->map_data->so_text);
	if (!mlx->so_text)
		ft_esc(mlx);
	mlx->we_text = mlx_load_png(mlx->map_data->we_text);
	if (!mlx->we_text)
		ft_esc(mlx);
	mlx->ea_text = mlx_load_png(mlx->map_data->ea_text);
	if (!mlx->ea_text)
		ft_esc(mlx);
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
	x_offset = ft_text_x_offset(ray);
	while (y < ray->wall_bottom_pixel && y < HEIGHT)
	{
		y_offset = (1 - ((double)(ray->wall_bottom_pixel - y) / line_height))
			* ray->texture->height;
		mlx_put_pixel(mlx->img, x, y,
			ft_get_pixel_color(ray, y_offset, x_offset));
		y++;
	}
}

double	ft_text_x_offset(t_ray *ray)
{
	double	x_offset;

	x_offset = 0;
	if (ray->ray_type == H_RAY)
	{
		x_offset = ray->texture->width - fmod(ray->wall_hit->x, TILE_SIZE)
			* ray->texture->width / TILE_SIZE;
		if (ray->ray_up)
			x_offset = fmod(ray->wall_hit->x, TILE_SIZE) * ray->texture->width
				/ TILE_SIZE;
	}
	else if (ray->ray_type == V_RAY)
	{
		x_offset = fmod(ray->wall_hit->y, TILE_SIZE)
			* ray->texture->width / TILE_SIZE;
		if (ray->ray_left)
			x_offset = ray->texture->width - fmod(ray->wall_hit->y, TILE_SIZE)
				* ray->texture->width / TILE_SIZE;
	}
	return (x_offset);
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
		wall_strip_height = (int)projected_wall_height;
		projected_wall_height = (TILE_SIZE / rays[x].ray_distance)
			* dis_projection;
		rays[x].wall_top_pixel = (HEIGHT / 2) - (wall_strip_height / 2);
		rays[x].wall_bottom_pixel = (HEIGHT / 2) + (wall_strip_height / 2);
		ft_scale_cord_text(mlx, &rays[x], x);
		++x;
	}
}
