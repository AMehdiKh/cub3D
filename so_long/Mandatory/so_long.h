/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:31:12 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/06 16:46:52 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../LibFT/libft.h"

typedef struct s_cord
{
	int		x;
	int		y;
}	t_cord;

typedef struct s_node
{
	t_cord			cord[1];
	struct s_node	*next;
}	t_node;

typedef struct s_queue
{
	t_node		*front;
	t_node		*rear;
	bool		**visited;
	int			size;
}	t_queue;

typedef struct s_mlx
{
	mlx_image_t	*img;
	mlx_t		*win;
	keys_t		key;
	t_cord		p_cord[1];
	t_cord		s_cord[1];
	t_cord		e_cord[1];
	char		**map;
	int			x;
	int			y;
	int			player;
	int			coin;
	int			exit;
	int			moves;
	int			max_width;
	int			max_height;
}	t_mlx;

void	ft_check_arg(t_mlx *mlx, char *av);

char	**ft_parse(char *map_name);
char	**ft_check_newline(char *line);
char	*ft_line(int fd);

void	map_check(t_mlx *mlx);
void	ft_count_items(t_mlx *mlx, int x, int y);

void	ft_bfs(t_mlx *mlx);
bool	**ft_visited(t_mlx *mlx);
void	ft_isvalid(t_queue *queue, char **map);
t_node	*ft_newnode(t_queue *queue, char **map, int x, int y);
void	ft_enqueue(t_queue *queue, char **map, int x, int y);
void	ft_dequeue(t_queue *queue);

void	ft_graphics(t_mlx *mlx);
void	ft_mlx_init(t_mlx *mlx, int x, int y);
void	ft_put_sprite(t_mlx *mlx);
void	ft_draw_image(t_mlx *mlx, char *png_path, int x, int y);
int		ft_exit_sprite(t_mlx *mlx, t_cord *e);
int		ft_star_sprite(t_mlx *mlx, t_cord *s);
void	ft_player_sprite(t_mlx *mlx, t_cord *p);

void	ft_hooks(mlx_key_data_t keydata, void *param);
void	ft_right(t_mlx *mlx, int *x, int *y);
void	ft_left(t_mlx *mlx, int *x, int *y);
void	ft_down(t_mlx *mlx, int *x, int *y);
void	ft_up(t_mlx *mlx, int *x, int *y);
void	ft_esc(t_mlx *mlx, int x, int y);

void	ft_close(void *param);

void	*ft_free_return(void *ptr1, void *ptr2);
void	ft_err(char **ptr, char *str);
void	ft_clear(void **ptr);
char	*ft_strjoin_long(char *s1, char *s2);

#endif