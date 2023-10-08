/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:28:15 by ael-khel          #+#    #+#             */
/*   Updated: 2023/10/08 17:58:20 by ael-khel         ###   ########.fr       */
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
	int		no_elem;
	int		so_elem;
	int		we_elem;
	int		ea_elem;

	int		f_elem;
	int		c_elem;

	int		num_elem;

}	t_check;

typedef struct s_map
{
	t_check		map_check[1];

	char		*no_text;
	char		*so_text;
	char		*we_text;
	char		*ea_text;

	int			f_color;
	int			c_color;

	char		**map;

	char		player_pos;

}	t_map;

// parse_map.c
void	ft_check_arg(int ac, char *av);
char	*ft_open_map(char *map_name);
int		ft_parse_map(t_map *map_data, char *line);
void	ft_check_elements(t_map *map_data, char **element);
// utils.c
void	ft_clear(void **ptr);
int		ft_err(char *str, int option);
void	ft_destroy_map_data(t_map *map_data);
// check_map.c
void	ft_check_map(t_map *map_data);
void	ft_check_elements(t_map *map_data, char **elem);
void	ft_direc(t_map *map_data, char **elem, char *dire_text, int *dire_elem);

#endif