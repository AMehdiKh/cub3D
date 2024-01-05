/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:28:15 by ael-khel          #+#    #+#             */
/*   Updated: 2024/01/05 21:19:20 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include "../LibFT/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define WIDTH 1920
# define HEIGHT 1080
# define MOVE_SPEED 5
# define ROT_SPEED 3
# define BPP 4
# define TILE_SIZE 32
# define FOV_ANGLE 60
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

	int			f_elem;
	int			c_elem;
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

	uint32_t	c_color;
	uint32_t	f_color;

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
	int			x_index;
	int			y_index;
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
	uint32_t		*text_color;
	t_cord			wall_hit[1];
	double			ray_angle;
	double			ray_distance;
	uint32_t		color;
	int				wall_top_pixel;
	int				wall_bottom_pixel;
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
	uint32_t		*north_color;
	uint32_t		*south_color;
	uint32_t		*west_color;
	uint32_t		*east_color;
	t_map			*map_data;
	t_player		player_data[1];
	double			map_scale;
	t_ray			*rays;
	t_casting		*cast;
	uint32_t		pos_text_x;
	uint32_t		pos_text_y;
}	t_mlx;

// main.c
void		ft_check_arg(int ac, char *av);

// parse_map.c
void		ft_parse_map(t_map *map_data, char *map_name);
void		ft_open_map(t_map *map_data, char *map_name);
void		ft_count_map_lines(t_map *map_data, char *map_name);

// check_map.c
void		ft_check_map(t_map *map_data);
void		ft_check_elements(t_map *map_data);
int			ft_all_elements(t_check *map_check);

// check_map_elements.c
void		ft_direc_elem(t_map *map_data, char **dire_text, int *dire_elem);
void		ft_rgb_elem(t_map *map_data, char **elem, int option);
void		ft_check_rgb(t_map *map_data, char *elem, uint32_t *color);
void		ft_rgb_init(t_map *map_data, char *elem, uint32_t *color, int *i);

// check_map_content.c
void		ft_check_content(t_map *map_data, int start);
void		ft_isolate_content(t_map *map_data, int start);
void		ft_check_character(t_map *map_data, int x, int y);
void		ft_check_walls(t_map *map_data, char **map, size_t x, size_t y);

// player_movements.c
void		ft_player_movements(void *param);
void		ft_move_straight(t_mlx *mlx, int pixel);
void		ft_move_sides(t_mlx *mlx, int pixel);
void		ft_turn(t_mlx *mlx, int pixel);

// graphics.c
void		ft_graphics(t_map *map_data);
void		ft_init_mlx(t_mlx *mlx);
void		ft_render_map(t_mlx	*mlx);
void		ft_paint_ceiling_floor(t_mlx *mlx);

// ray_casting.c
void		ft_cast_rays(t_mlx *mlx, t_ray *rays);
void		ft_wall_hit(t_ray *ray, t_casting *cast);
void		ft_ray_directions(t_casting *cast);
double		ft_cord_distance(t_cord *p1, t_cord *p2);
void		ft_init_ray_directions(t_ray *ray, t_casting *cast);

// h_v_intersection.c
void		ft_calc_h_inter(t_casting *cast);
void		ft_h_intersection(t_casting *cast);
void		ft_calc_v_inter(t_casting *cast);
void		ft_v_intersection(t_casting *cast);
void		ft_init_ray_texture(t_mlx *mlx, t_ray *ray);

// render_walls.c
void		ft_load_textures(t_mlx *mlx);
double		ft_text_x_offset(t_ray *ray);
void		ft_render_walls(t_mlx *mlx, t_ray *rays);
void		ft_scale_cord_text(t_mlx *mlx, t_ray *ray, int x);
uint32_t	ft_get_pixel_color(t_ray *ray, int y_offset, int x_offset);

// mini_map.c
void		ft_mini_map(t_mlx *mlx);
void		ft_scale_mini_map(t_mlx *mlx, t_map *map_data);
void		ft_square(t_mlx *mlx, t_cord *square, int color);
void		ft_p_square(t_mlx *mlx, t_cord *square, int color, int padding);

// destroy_data.c
void		ft_esc(void *param);
int			ft_err(char *str, t_map *map_data);
void		ft_clear(void **ptr);
void		ft_destroy_map_data(t_map *map_data);

// utils.c
void		ft_init_cord(t_cord *cord, double x, double y);
void		ft_paint_pixels(uint8_t *pixels, uint32_t color, size_t size);
double		ft_normalize_angle(double *angle);
double		ft_player_angle(t_map *map_data);
uint32_t	ft_rgb(uint32_t r, uint32_t g, uint32_t b, uint32_t o);

#endif