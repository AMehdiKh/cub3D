/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_data_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:29:15 by ael-khel          #+#    #+#             */
/*   Updated: 2024/01/04 14:52:20 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_esc(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	ft_destroy_map_data(mlx->map_data);
	if (mlx->no_text)
		mlx_delete_texture(mlx->no_text);
	if (mlx->so_text)
		mlx_delete_texture(mlx->so_text);
	if (mlx->we_text)
		mlx_delete_texture(mlx->we_text);
	if (mlx->ea_text)
		mlx_delete_texture(mlx->ea_text);
	mlx_terminate(mlx->win);
	exit(EXIT_SUCCESS);
}

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
