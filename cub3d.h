/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:28:15 by ael-khel          #+#    #+#             */
/*   Updated: 2023/10/10 18:33:56 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include "LibFT/libft.h"

typedef struct s_check
{
	char	**elem;

	int		no_elem;
	int		so_elem;
	int		we_elem;
	int		ea_elem;

	int		f_elem;
	int		c_elem;
	int		digit_count;
	int		digit;

	int		num_elem;

}	t_check;

typedef struct s_map
{
	t_check		map_check[1];

	char		*no_text;
	char		*so_text;
	char		*we_text;
	char		*ea_text;

	int			c_color;
	int			f_color;

	char		player_pos;

	char		**map;

}	t_map;

// parse_map.c
void	ft_check_arg(int ac, char *av);
char	*ft_open_map(char *map_name);
void	ft_parse_map(t_map *map_data, char *line);
// check_directions.c
void	ft_check_map(t_map *map_data);
void	ft_check_elements(t_map *map_data);
void	ft_direc_elem(t_map *map_data, char *dire_text, int *dire_elem);
// check_rgb.c
void	ft_rgb_elem(t_map *map_data, char **elem, int option);
void	ft_check_rgb(t_map *map_data, char *elem, int *color);
void	ft_rgb_init(t_map *map_data, char *elem, int *color, int *i);
// utils.c
int		ft_err(char *str, int option);
void	ft_clear(void **ptr);
void	ft_destroy_map_data(t_map *map_data);

#endif