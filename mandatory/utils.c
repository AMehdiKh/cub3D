/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:39:04 by ael-khel          #+#    #+#             */
/*   Updated: 2023/11/17 14:48:29 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_err(char *str, t_map *map_data)
{
	if (str)
		ft_putendl_fd(str, 2);
	else if (errno)
		perror("[!] Error");
	ft_destroy_map_data(map_data);
	exit(EXIT_FAILURE);
}

void	ft_clear(void **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
			free(ptr[i++]);
		free(ptr);
	}
}

void	ft_destroy_map_data(t_map *map_data)
{
	if (map_data)
	{
		ft_clear((void **)map_data->map_check->elem);
		ft_clear((void **)map_data->map);
		free(map_data->no_text);
		free(map_data->so_text);
		free(map_data->we_text);
		free(map_data->ea_text);
	}
}
