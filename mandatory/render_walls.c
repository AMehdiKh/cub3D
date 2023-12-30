/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:56:41 by ael-khel          #+#    #+#             */
/*   Updated: 2023/12/30 19:01:37 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_ray_texture(t_mlx *mlx, t_ray *ray)
{
	if (ray->ray_type == H_RAY && ray->ray_down)
	{
		ray->text_color = mlx->south_color;
		ray->texture = mlx->so_text;
	}
	else if (ray->ray_type == H_RAY && ray->ray_up)
	{
		ray->text_color = mlx->north_color;
		ray->texture = mlx->no_text;
	}
	else if (ray->ray_type == V_RAY && ray->ray_left)
	{
		ray->text_color = mlx->west_color;
		ray->texture = mlx->we_text;
	}
	else if (ray->ray_type == V_RAY && ray->ray_right)
	{
		ray->text_color = mlx->east_color;
		ray->texture = mlx->ea_text;
	}
}

uint32_t get_color(t_ray *ray, int y_offset , int x_offset)
{

	// uint32_t p;

	// p = ((uint32_t *)ray->texture->pixels)[ray->texture->width * y_offset + x_offset];
	// return ((p & 0xFF000000) >> 24 | (p & 0x00FF0000) >> 8
	// 	| (p & 0x0000FF00) << 8 | (p & 0x000000FF) << 24);
	
	int pos;
	
	// pos = (y_offset * ray->texture->width + x_offset) * ray->texture->bytes_per_pixel;
	pos = y_offset * ray->texture->width + x_offset;

	if (pos < 0 || pos > (int)(ray->texture->height * (ray->texture->width * 4)) - 4)
		return (0);
	// return (ft_pixel(ray->texture->pixels[pos], ray->texture->pixels[pos + 1], ray->texture->pixels[pos + 2], ray->texture->pixels[pos + 3]));
	return (ray->text_color[pos]);
}

void scale_cord_text(t_mlx *mlx, int top_pixel, int bot_pixel, double wall_strip_height, t_ray *rays, int i)
{
	float x_offset;
	float y_offset;

	(void)wall_strip_height;

	int y = top_pixel;
	if (top_pixel < 0)
		y = 0;
	if (rays->ray_type == H_RAY)
		x_offset = fmod(rays->wall_hit->x, TILE_SIZE) * rays->texture->width / TILE_SIZE;
		// x_offset = (rays->texture->width / TILE_SIZE)
		// 	* (rays->wall_hit->x - (int)(rays->wall_hit->x / TILE_SIZE) * TILE_SIZE);
	else if (rays->ray_type == V_RAY)
		x_offset = fmod(rays->wall_hit->y, TILE_SIZE) * rays->texture->width / TILE_SIZE;
		// x_offset = (rays->texture->width / TILE_SIZE)
		// 	* (rays->wall_hit->y - (int)(rays->wall_hit->y / TILE_SIZE) * TILE_SIZE);
	// mlx->pos_text_y = 1 - (((HEIGHT- top_pixel) / line_size) * rays->texture->width) / TILE_SIZE;
	
	// printf("[%d] top_pixel = %d, bot_pixel = %d, line_size = %d, text_y = %d, texture_height = %u \n", i, top_pixel, bot_pixel, bot_pixel-top_pixel, mlx->pos_text_y, rays->texture->height);

	while(y < bot_pixel && y < HEIGHT)
	{
		int line_height;

		line_height = bot_pixel - top_pixel;
		// y = top_pixel;
		// y_offset = (1.0 - (bot_pixel - top_pixel)/wall_strip_height) * (rays->texture->width);
		// y_offset = (bot_pixel - y) * (rays->texture->height / (wall_strip_height));
		y_offset = (1 - ((float)(bot_pixel - y) / line_height)) * rays->texture->height;
		// color = get_color(rays,y_offset, x_offset);
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
	// 	printf("NO:%p, WE:%p, EA:%p SO:%p\n", mlx->north_color,mlx->west_color,mlx->east_color,mlx->south_color);
	// 	printf("ray color: %p\n",rays[i].text_color);
	// }
		rays[i].ray_distance *= cos(rays[i].ray_angle - mlx->player_data->rotation_angle);
		dis_projection = (WIDTH / 2) / tan(mlx->player_data->field_of_view / 2);
		projected_wall_height = (TILE_SIZE / rays[i].ray_distance) * dis_projection;
		wall_strip_height = (TILE_SIZE / rays[i].ray_distance) * (((double)HEIGHT / 2) / (tan(30 * M_PI / 180)));
		wall_top_pixel = (HEIGHT / 2) - (wall_strip_height / 2);
		// wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;
		// wall_top_pixel = wall_top_pixel * (wall_top_pixel > 0);
		wall_bottom_pixel = (HEIGHT / 2) + (wall_strip_height / 2);
		// wall_bottom_pixel = wall_bottom_pixel > HEIGHT ? HEIGHT : wall_bottom_pixel;
		// wall_bottom_pixel = wall_bottom_pixel < 0 ? 0 : wall_bottom_pixel;
		scale_cord_text(mlx, wall_top_pixel, wall_bottom_pixel,wall_strip_height, &rays[i], i);
		// dda(mlx, i, wall_top_pixel, i, wall_bottom_pixel, rays[i].color);

		++i;
	}
	// if (mlx->north_color == rays[100].text_color || mlx->east_color == rays[100].text_color
	// 		|| mlx->south_color == rays[100].text_color || mlx->west_color == rays[100].text_color)
	// {
	// 	uint32_t *colors = rays[100].text_color;
	// 	// uint32_t *colors = mlx->east_color;
	// 	for(uint32_t k = 0;k < rays->texture->height;k++)
	// 	{
	// 		for(uint32_t f = 0;f < rays->texture->width;f++)
	// 		{
	// 			mlx_put_pixel(mlx->img,f,k, *colors);
	// 			colors++;
	// 		}
	// 	}
	// }
}