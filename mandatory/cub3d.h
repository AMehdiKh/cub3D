/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:28:15 by ael-khel          #+#    #+#             */
/*   Updated: 2023/12/24 20:31:06 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <sys/_types/_size_t.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include "LibFT/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

// # define WIDTH 2240
# define MOVE_SPEED 5
# define ROT_SPEED 2
# define WIDTH 1800
# define HEIGHT 960
# define BPP 4
# define TILE_SIZE 32
# define FOV_ANGLE 60
# define SCALE 0.25
# define H_RAY 0
# define V_RAY 1

typedef struct s_cord
{
	double	x;
	double	y;
}	t_cord;

typedef struct s_check
{
	char		**elem;

	int			line_count;

	int			no_elem;
	int			so_elem;
	int			we_elem;
	int			ea_elem;

	uint32_t	f_elem;
	uint32_t	c_elem;
	int			comma_count;
	int			digit_count;
	int			digit;

	int			num_elem;

}	t_check;

typedef struct s_map
{
	t_check		map_check[1];
	t_cord		character[1];

	char		*no_text;
	char		*so_text;
	char		*we_text;
	char		*ea_text;

	int			c_color;
	int			f_color;

	char		character_dire;

	char		**map;

	int			map_width;
	int			map_height;

}	t_map;

typedef struct s_player
{
	t_cord		*player;
	double		rotation_speed;
	double		rotation_angle;
	double		ray_angle;
	double		field_of_view;
}	t_player;

typedef struct s_casting
{
	t_cord		h_insec[1];
	t_cord		v_insec[1];
	t_cord		*player;
	char		**map;
	double		ray_angle;
	double		x_step;
	double		y_step;
	double		x_first;
	double		y_first;
	double		h_distance;
	double		v_distance;
	size_t		x_index;
	size_t		y_index;
	int			ray_up;
	int			ray_down;
	int			ray_right;
	int			ray_left;
	int			width;
	int			height;
	int			h_found_wall;
	int			v_found_wall;
}	t_casting;

typedef struct s_ray
{
	mlx_texture_t	*texture;
	uint32_t 		**text_color;
	t_cord			wall_hit[1];
	double			ray_angle;
	double			ray_distance;
	uint32_t		color;
	int				ray_type;
	int				ray_up;
	int				ray_down;
	int				ray_right;
	int				ray_left;
}	t_ray;

typedef struct s_mlx
{
	mlx_image_t		*img;
	mlx_t			*win;
	mlx_texture_t	*no_text;
	mlx_texture_t	*so_text;
	mlx_texture_t	*we_text;
	mlx_texture_t	*ea_text;
	uint32_t 		**north_color;
	uint32_t 		**south_color;
	uint32_t 		**west_color;
	uint32_t 		**east_color;
	t_map			*map_data;
	t_player		player_data[1];
	double			map_scale;
	t_ray			*rays;
	t_casting		*cast;
	t_cord			pos_text[1];
}	t_mlx;

// parse_map.c
void	ft_check_arg(int ac, char *av);
void	ft_count_map_lines(t_map *map_data, char *map_name);
void	ft_open_map(t_map *map_data, char *map_name);
void	ft_parse_map(t_map *map_data, char *map_name);

// check_directions.c
void	ft_check_map(t_map *map_data);
void	ft_check_elements(t_map *map_data);
void	ft_direc_elem(t_map *map_data, char **dire_text, int *dire_elem);
int		ft_all_elements(t_check *map_check);
void	ft_check_content(t_map *map_data, int start);
void	ft_check_character(t_map *map_data, int x, int y);
void	ft_check_walls(t_map *map_data, char **map, size_t x, size_t y);

// check_rgb.c
void	ft_rgb_elem(t_map *map_data, char **elem, int option);
void	ft_check_rgb(t_map *map_data, char *elem, int *color);
void	ft_rgb_init(t_map *map_data, char *elem, int *color, int *i);

// utils.c
int		ft_err(char *str, t_map *map_data);
void	ft_clear(void **ptr);
void	ft_destroy_map_data(t_map *map_data);
//graphics.c
void	ft_graphics(t_map *map_data);
void	ft_init_mlx(t_mlx *mlx);
void	ft_mini_map(t_mlx *mlx);
void	ft_draw_pixels(t_mlx *mlx, int xc, int yc, int x, int y, int color);
void	ft_isolate_content(t_map *map_data, int start);
void	ft_init_cord(t_cord *cord, double x, double y);

//Textures
void	load_texture(t_mlx *mlx);
void  	load_pngs(t_mlx *mlx);
uint32_t	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t o);

double	ft_character_direction(t_map *map_data);
void	ft_turn(t_mlx *mlx, int pixel);
void	ft_move_straight(t_mlx *mlx, int pixel);
void	ft_move_sides(t_mlx *mlx, int pixel, t_cord cor);
void	ft_hooks(void *param);
void	ft_player_square(t_mlx *mlx, t_cord *square, int color, int padding);
void	bresenhams_line(t_mlx *mlx, int x1, int y1, int x2, int y2);
void	dda(t_mlx *mlx, int X0, int Y0, int X1, int Y1, int color);
void	ft_esc(void *param);
void	ft_cast_rays(t_mlx *mlx, t_ray *rays);
double	ft_normalize_angle(double *angle);
int		ft_abs(int value);
void	ft_h_intersection(t_casting *cast);
void	ft_v_intersection(t_casting *cast);
void	ft_wall_hit(t_ray *ray, t_casting *cast);
double	ft_cord_distance(t_cord *p1, t_cord *p2);
void	ft_ray_directions(t_casting *cast);
void	ft_paint_pixels(uint8_t *pixels, unsigned color, size_t size);
void	ft_render_map(t_mlx	*mlx);
void	ft_draw_rays(t_mlx *mlx, t_ray *rays);
void	ft_paint_ceiling_floor(t_mlx *mlx);
void	ft_render_walls(t_mlx *mlx, t_ray *rays);
void	ft_square(t_mlx *mlx, t_cord *square, int color);
void	ft_size_mini_map(t_mlx *mlx, t_map *map_data);
void	ft_ray_texture(t_mlx *mlx, t_ray *ray);
void	ft_open_textures(t_mlx *mlx);



#endif