/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:58:06 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/06 16:18:09 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_check(t_mlx *mlx)
{
	char	**map;

	map = mlx->map;
	while (map[mlx->y])
	{
		mlx->x = -1;
		while (map[mlx->y][++mlx->x])
			ft_count_items(mlx, mlx->x, mlx->y);
		if (map[++mlx->y])
			if (mlx->x != (int)ft_strlen(map[mlx->y]))
				ft_err(map, "\e[0;31mError: The map is not rectangular");
	}
	if ((mlx->y * 72) > mlx->max_height || (mlx->x * 72) > mlx->max_width)
		ft_err(map, "\e[0;31mError: The map is bigger than monitor size");
	if (mlx->player != 1 || mlx->exit != 1 || mlx->coin < 1)
		ft_err(map, "\e[0;31mError: The number of items in map is incorrect");
}

void	ft_count_items(t_mlx *mlx, int x, int y)
{
	char	**map;

	map = mlx->map;
	if (!ft_strchr("10PCE", map[y][x]))
		ft_err(map, "\e[0;31mError: The map has invalid characters");
	if (y == 0 || !(map[y + 1]) || x == 0 || !(map[y][x + 1]))
		if (map[y][x] != '1')
			ft_err(map, "\e[0;31mError: The map is not surrounded by 1");
	if (map[y][x] == 'C')
		++mlx->coin;
	else if (map[y][x] == 'P')
	{
		mlx->p_cord->x = x;
		mlx->p_cord->y = y;
		mlx->s_cord->x = x;
		mlx->s_cord->y = y;
		++mlx->player;
	}
	else if (map[y][x] == 'E')
	{
		mlx->e_cord->y = y;
		mlx->e_cord->x = x;
		++mlx->exit;
	}
}

bool	**ft_visited(t_mlx *mlx)
{
	bool	**visited;
	int		i;

	visited = ft_calloc(mlx->y + 1, sizeof(bool *));
	if (!visited)
		ft_err(mlx->map, NULL);
	i = 0;
	while (i < mlx->y)
	{
		visited[i] = ft_calloc(mlx->x, sizeof(bool));
		if (!visited[i])
		{
			while (i--)
				free(visited[i]);
			free(visited);
			ft_err(mlx->map, NULL);
		}
		++i;
	}
	return (visited);
}
