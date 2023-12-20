/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:31:10 by ael-khel          #+#    #+#             */
/*   Updated: 2023/12/20 17:13:42 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_graphics(t_map *map_data)
{
	t_mlx	mlx[1];

	ft_bzero(mlx, sizeof(mlx));
	mlx->map_data = map_data;
	ft_init_mlx(mlx, map_data->map_width, map_data->map_height);
	ft_render_map(mlx);
	mlx_loop_hook(mlx->win, &ft_hooks, mlx);
	mlx_close_hook(mlx->win, &ft_esc, mlx);
	mlx_loop(mlx->win);
	ft_esc(mlx);
}

void	ft_init_mlx(t_mlx *mlx, int x, int y)
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
	mlx->player_data->player = mlx->map_data->character;
	mlx->player_data->rotation_angle = ft_character_direction(mlx->map_data);
	mlx->player_data->rotation_speed = ROT_SPEED * (M_PI / 180);
	mlx->player_data->field_of_view = FOV_ANGLE * (M_PI / 180);
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

int	ft_size_mini_map(t_map	*map_data)
{
	int	width_limit;
	int	height_limit;
	int	tile_size;

	tile_size = 64;
	width_limit = WIDTH / 8;
	height_limit = HEIGHT / 8;
	while (tile_size > 4)
	{
		if (map_data->map_width * tile_size < width_limit
			&& map_data->map_height * tile_size < height_limit)
			return (tile_size);
		--tile_size;
	}
	return (-1);
}
void	ft_mini_map(t_mlx *mlx)
{
	t_map	*map_data;
	t_cord	square[1];
	int		tile_size;
	int		y;
	int		x;

	map_data = mlx->map_data;
	tile_size = 0;
	// ft_size_mini_map(map_data);
	// if (tile_size < 0)
	// 	exit(1);
	y = 0;
	while (map_data->map[y])
	{
		x = 0;
		while (map_data->map[y][x])
		{
			ft_init_cord(square, x * TILE_SIZE, y * TILE_SIZE);
			if (map_data->map[y][x] == '1')
				ft_square(mlx, square, tile_size, 0x772f1aff);
			else
				ft_square(mlx, square, tile_size, 0x55a630ff);
			++x;
		}
		++y;
	}
	ft_player_square(mlx, mlx->player_data->player, 0xd90429FF, 2);
}

void	ft_square(t_mlx *mlx, t_cord *square, int tile_size, int color)
{
	int	x_start;
	int	y_start;
	int	x_end;
	int	y_end;

	y_start = square->y * SCALE;
	y_end = y_start + (TILE_SIZE * SCALE);
	x_end = (square->x * SCALE) + (TILE_SIZE * SCALE);
	while (y_start < y_end)
	{
		x_start = square->x * SCALE;
		while (x_start < x_end)
		{
			mlx_put_pixel(mlx->img, x_start, y_start, color);
			if (y_start == square->y * SCALE || x_start == square->x * SCALE)
				mlx_put_pixel(mlx->img, x_start, y_start, 0x222222ff);
			++x_start;
		}
		++y_start;
	}
}

void	ft_player_square(t_mlx *mlx, t_cord *square, int color, int padding)
{
	int	x_start;
	int	y_start;
	int	x_end;
	int	y_end;

	y_start = square->y * SCALE - padding;
	y_end = square->y * SCALE + padding;
	x_end = square->x * SCALE + padding;
	while (y_start < y_end)
	{
		x_start = square->x * SCALE - padding;
		while (x_start < x_end)
		{
			mlx_put_pixel(mlx->img, x_start, y_start, color);
			++x_start;
		}
		++y_start;
	}
}
void	ft_paint_ceiling_floor(t_mlx *mlx)
{
	ft_paint_pixels(mlx->img->pixels, mlx->map_data->f_color, mlx->img->width * mlx->img->height);
	ft_paint_pixels(mlx->img->pixels, mlx->map_data->c_color, mlx->img->width * (mlx->img->height / 2));
}

void	ft_paint_pixels(uint8_t *pixels, unsigned color, size_t size)
{
	size_t	i;
	int		shift;

	shift = 3;
	i = 0;
	while (i < size * BPP)
	{
		if (shift == -1)
			shift = 3;
		pixels[i] = (color >> (8 * shift)) & 0xFF;
		--shift;
		++i;
	}
}

void	ft_render_walls(t_mlx *mlx, t_ray *rays)
{
	double	dis_projection;
	double	projected_wall_height;
	double	perp_dis;
	int		wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		i;
	
	i = 0;
	while (i < WIDTH)
	{
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

double	ft_cord_distance(t_cord *p1, t_cord *p2)
{
	return (sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2)));
}

double	ft_normalize_angle(double *angle)
{
	*angle = remainder(*angle, (2 * M_PI));
	if (*angle < 0)
		*angle += (2 * M_PI);
	return (*angle);
}

double	ft_character_direction(t_map *map_data)
{
	if (map_data->character_dire == 'N')
		return (3 * M_PI / 2);
	else if (map_data->character_dire == 'S')
		return (M_PI_2);
	else if (map_data->character_dire == 'W')
		return (M_PI);
	else if (map_data->character_dire == 'E')
		return (0);
	return (0);
}

void	ft_init_cord(t_cord *cord, double x, double y)
{
	cord->x = x;
	cord->y = y;
}

void	ft_esc(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	ft_destroy_map_data(mlx->map_data);
	mlx_terminate(mlx->win);
	exit(EXIT_SUCCESS);
}
