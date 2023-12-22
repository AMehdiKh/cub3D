/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:56:41 by ael-khel          #+#    #+#             */
/*   Updated: 2023/12/21 17:39:59 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_ray_texture(t_mlx *mlx, t_ray *ray)
{
	if (ray->ray_type == H_RAY && ray->ray_up)
		ray->texture = mlx->no_text;
	else if (ray->ray_type == H_RAY && ray->ray_down)
		ray->texture = mlx->so_text;
	else if (ray->ray_type == V_RAY && ray->ray_left)
		ray->texture = mlx->we_text;
	else if (ray->ray_type == V_RAY && ray->ray_right)
		ray->texture = mlx->ea_text;
}

void	ft_render_walls(t_mlx *mlx, t_ray *rays)
{
	double	dis_projection;
	double	projected_wall_height;
	int		wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		i;
	
	i = 0;
	while (i < WIDTH)
	{
		ft_ray_texture(mlx, rays + i);
		rays[i].ray_distance *= cos(rays[i].ray_angle - mlx->player_data->rotation_angle);
		dis_projection = (WIDTH / 2) / tan(mlx->player_data->field_of_view / 2);
		projected_wall_height = (TILE_SIZE / rays[i].ray_distance) * dis_projection;
		wall_strip_height = (int)projected_wall_height;
		wall_top_pixel = (HEIGHT / 2) - (wall_strip_height / 2);
		wall_top_pixel = wall_top_pixel > HEIGHT ? HEIGHT : wall_top_pixel;
		wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;

		wall_bottom_pixel = (HEIGHT / 2) + (wall_strip_height / 2);
		wall_bottom_pixel = wall_bottom_pixel < 0 ? 0 : wall_bottom_pixel;
		wall_bottom_pixel = wall_bottom_pixel > HEIGHT ? HEIGHT : wall_bottom_pixel;
		// wall_bottom_pixel = wall_bottom_pixel > HEIGHT ? HEIGHT : wall_bottom_pixel;
		printf("[%d] top = %d, bottom = %d\n", i, wall_top_pixel, wall_bottom_pixel);
		dda(mlx, i, wall_top_pixel, i, wall_bottom_pixel, rays[i].color);

		// for (int y = wall_top_pixel; y < wall_bottom_pixel; y++)
		// 	mlx_put_pixel(mlx->img, i, y, 0xff4578ff);
		++i;
	}
}

// void	ft_draw_texture(int8_t pixels, int start, int end, int wall)
// {
// 	size_t	i;
// 	size_t	j;
// 	int		count;
// 	int		shift;

// 	count = 0;
// 	i = (start * WIDTH * BPP) + (wall * BPP);
// 	while (count < end - start)
// 	{
// 		j = 0;
// 		while (j < BPP)
// 		{
// 			pixels[i + j] = ;
// 			++j;
// 		}
// 		i += WIDTH * BPP;
// 		++count;
// 	}
// }