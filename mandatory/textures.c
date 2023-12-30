/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:26:45 by mzoheir           #+#    #+#             */
/*   Updated: 2023/12/30 20:44:34 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t o)
{
	return (r << 24 | g << 16 | b << 8 | o);
}

void   load_pngs(t_mlx *mlx)
{
	mlx->so_text = mlx_load_png(mlx->map_data->so_text);
	if(!mlx->so_text)
    {
        printf("ERROR Loading SOUTH Texture!\n");
		exit(EXIT_FAILURE);
    }
	mlx->no_text = mlx_load_png(mlx->map_data->no_text);
	if(!mlx->no_text)
    {
        printf("ERROR Loading NORTH Texture!\n");
		exit(EXIT_FAILURE);
    }
	mlx->ea_text = mlx_load_png(mlx->map_data->ea_text);
	if(!mlx->ea_text)
    {
        printf("ERROR Loading EAST Texture!\n");
		exit(EXIT_FAILURE);
    }
	mlx->we_text = mlx_load_png(mlx->map_data->we_text);
    if(!mlx->we_text)
    {
        printf("ERROR Loading WEST Texture!\n");
		exit(EXIT_FAILURE);
    }
	
}
