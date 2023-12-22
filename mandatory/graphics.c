/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:31:10 by ael-khel          #+#    #+#             */
/*   Updated: 2023/12/21 17:41:33 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_graphics(t_map *map_data)
{
	t_mlx	mlx[1];

	ft_bzero(mlx, sizeof(mlx));
	mlx->map_data = map_data;
	ft_init_mlx(mlx);
	ft_render_map(mlx);
	mlx_loop_hook(mlx->win, &ft_hooks, mlx);
	mlx_close_hook(mlx->win, &ft_esc, mlx);
	mlx_loop(mlx->win);
	ft_esc(mlx);
}

void	ft_init_mlx(t_mlx *mlx)
{
	mlx->win = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!mlx->win)
		ft_err("Error: MinilibX initialization failed", mlx->map_data);
	mlx->img = mlx_new_image(mlx->win, WIDTH, HEIGHT);
	if (!mlx->img)
	{
		mlx_terminate(mlx->win);
		ft_err("Error: Creating new image failed", mlx->map_data);
	}
	if (mlx_image_to_window(mlx->win, mlx->img, 0, 0) < 0)
	{
		mlx_terminate(mlx->win);
		ft_err("Error: Putting image to window failed", mlx->map_data);
	}
	// ft_open_textures(mlx);
	mlx->player_data->player = mlx->map_data->character;
	mlx->player_data->rotation_angle = ft_character_direction(mlx->map_data);
	mlx->player_data->rotation_speed = ROT_SPEED * (M_PI / 180);
	mlx->player_data->field_of_view = FOV_ANGLE * (M_PI / 180);
}

void	ft_open_textures(t_mlx *mlx)
{
	mlx->no_text = mlx_load_png(mlx->map_data->no_text);
	mlx->so_text = mlx_load_png(mlx->map_data->so_text);
	mlx->we_text = mlx_load_png(mlx->map_data->we_text);
	mlx->ea_text = mlx_load_png(mlx->map_data->ea_text);
	if (!mlx->no_text || !mlx->so_text || !mlx->we_text || !mlx->ea_text)
	{
		mlx_delete_texture(NULL);
		mlx_delete_texture(mlx->no_text);
		mlx_delete_texture(mlx->so_text);
		mlx_delete_texture(mlx->we_text);
		mlx_delete_texture(mlx->ea_text);
		mlx_terminate(mlx->win);
		ft_err("Error: Texture failed to open", mlx->map_data);
	}
}

void	ft_render_map(t_mlx	*mlx)
{
	t_ray	rays[WIDTH];

	ft_paint_ceiling_floor(mlx);
	ft_cast_rays(mlx, rays);
	ft_render_walls(mlx, rays);
	ft_mini_map(mlx);
	ft_draw_rays(mlx, rays);
}

void	ft_paint_ceiling_floor(t_mlx *mlx)
{
	ft_paint_pixels(mlx->img->pixels, mlx->map_data->f_color,
		mlx->img->width * mlx->img->height);
	ft_paint_pixels(mlx->img->pixels, mlx->map_data->c_color,
		mlx->img->width * (mlx->img->height / 2));
}
