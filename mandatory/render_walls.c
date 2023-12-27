/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:56:41 by ael-khel          #+#    #+#             */
/*   Updated: 2023/12/27 12:30:09 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_ray_texture(t_mlx *mlx, t_ray *ray)
{
	if (ray->ray_type == H_RAY && ray->ray_up)
	{
		ray->text_color = mlx->north_color;
		ray->texture = mlx->no_text;
		printf("NORTH\n");
	}
	else if (ray->ray_type == H_RAY && ray->ray_down)
	{
		ray->text_color = mlx->south_color;
		ray->texture = mlx->so_text;
		printf("SOUTH\n");
	}
	else if (ray->ray_type == V_RAY && ray->ray_left)
	{
		ray->text_color = mlx->west_color;
		ray->texture = mlx->we_text;
		printf("WEST\n");
	}
	else if (ray->ray_type == V_RAY && ray->ray_right)
	{
		ray->text_color = mlx->east_color;
		ray->texture = mlx->ea_text;
		printf("EAST\n");
	}
	else
	{
		ray->texture = NULL;
		ray->text_color = NULL;
	}
}

void scale_cord_text(t_mlx *mlx, int start, int end, t_ray *rays, int i)
{
	int line_size;
	uint32_t cord_tmp;
	
	cord_tmp = 0;
	line_size = end - start;
	if (start < 0)
		start = 0;
	if (rays->ray_type == H_RAY)
		cord_tmp = fmod(rays->wall_hit->x, TILE_SIZE);
	else if (rays->ray_type == V_RAY)
		cord_tmp = fmod(rays->wall_hit->y, TILE_SIZE);
	mlx->pos_text_x = 0;
	mlx->pos_text_x =(cord_tmp * rays->texture->width) / TILE_SIZE;
	mlx->pos_text_y =  0;
	mlx->pos_text_y =  (((line_size - start) / line_size) * rays->texture->width) / TILE_SIZE;
	start = start * (start > 0);
	start = start * (start < HEIGHT);
	// end = end * (end > 0);
	// end = end * (end < HEIGHT);
	
	while(start < end && start < HEIGHT && mlx->pos_text_y < rays->texture->height)
	{
		mlx_put_pixel(mlx->img, i, start, rays->text_color[mlx->pos_text_y][mlx->pos_text_x]);
		mlx->pos_text_y += rays->texture->height / (line_size);
		start++;
	}
}

float get_xtxt(float pos, int width)
{
	return (pos/ TILE_SIZE) - ((int)pos / TILE_SIZE) * width;
}
void	ft_render_walls(t_mlx *mlx, t_ray *rays)      
{
	double	dis_projection;
	double	projected_wall_height;
	int		wall_strip_height;
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
		wall_strip_height = (int)projected_wall_height;
		wall_top_pixel = (HEIGHT / 2) - (wall_strip_height / 2);
		wall_bottom_pixel = (HEIGHT / 2) + (wall_strip_height / 2);
		// wall_top_pixel = wall_top_pixel > HEIGHT ? HEIGHT : wall_top_pixel;
		// wall_top_pixel = wall_top_pixel * (wall_top_pixel > 0);
		// wall_bottom_pixel = wall_bottom_pixel > HEIGHT ? HEIGHT : wall_bottom_pixel;
		// wall_bottom_pixel = wall_bottom_pixel < 0 ? 0 : wall_bottom_pixel;
		
		scale_cord_text(mlx, wall_top_pixel, wall_bottom_pixel, &rays[i], i);
		++i;
		// dda(mlx, i, wall_top_pixel, i, wall_bottom_pixel, rays[i].color);
	}
}
		// printf("width:%d height:%d\n",rays[i].texture->width, rays[i].texture->height);
		
		// 	dda_with_texture(mlx, i, wall_top_pixel, i, wall_bottom_pixel,  rays[i].text_color, rays[i].texture->width, rays[i].texture->height);
		