/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:26:45 by mzoheir           #+#    #+#             */
/*   Updated: 2023/12/27 11:27:56 by mzoheir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t o)
{
	return (r << 24 | g << 16 | b << 8 | o);
}

void	fill_colors(uint32_t **texture,
	mlx_texture_t *text, uint32_t *t)
{
    static int i;
	static uint32_t	j;
	if ((uint32_t)i < text->bytes_per_pixel * text->height * text->width)
	{
		texture[*t][(j)++] = ft_pixel(text->pixels[i],
				text->pixels[i + 1], text->pixels[i + 2],
				text->pixels[i + 3]);
		if (j == text->width)
		{
			(*t)++;
			j = 0;
		}
		i += 4;
	}
}

uint32_t	**fill_texture(mlx_texture_t *text)
{
    int i;
	uint32_t	x;
    uint32_t **text_color;
    
	i = 0;
	x = 0;
	text_color = malloc(sizeof(uint32_t *) * text->height);
	if (!text_color)
		return (0);
	while (i < (int)text->height)
	{
		text_color[i] = malloc(sizeof(uint32_t) * text->width);
		if (!text_color[i])
			return (0);
		i++;
	}
	i = 0;
	while (i < (int)(text->height * text->width
		* text->bytes_per_pixel))
	{
		fill_colors(text_color, text, &x);
		i += 4;
	}
	return (text_color);
}

void	load_texture(t_mlx *mlx)
{
	mlx->north_color = fill_texture(mlx->no_text);
	mlx->south_color = fill_texture(mlx->so_text);
	mlx->east_color = fill_texture(mlx->ea_text);
	mlx->west_color = fill_texture(mlx->we_text);
	// if(!mlx->north_color)
    //     // free all
	// if(!mlx->south_color)
	// 	// free all
	// if(!mlx->east_color)
	// 	// free all
	// if(!mlx->west_color)
	// 	// free all
}

void   load_pngs(t_mlx *mlx)
{
	mlx->so_text = mlx_load_png("Textures/Donuts.png");
	mlx->no_text = mlx_load_png("Textures/Donuts.png");
	mlx->ea_text = mlx_load_png("Textures/Donuts.png");
	mlx->we_text = mlx_load_png("Textures/Donuts.png");
    if(!mlx->so_text || !mlx->ea_text || !mlx->no_text || !mlx->we_text)
    {
        //free all
        printf("ERROR Loading Textures!\n");
    }
	
}

