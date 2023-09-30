/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 03:17:50 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/10 02:54:39 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_bfs(t_mlx *mlx)
{
	t_queue	queue[1];
	int		valid_coins;
	int		valid_exit;

	valid_coins = 0;
	valid_exit = 0;
	ft_bzero(queue, sizeof(t_queue));
	queue->visited = ft_visited(mlx);
	ft_enqueue(queue, mlx->map, mlx->p_cord->x, mlx->p_cord->y);
	while (queue->size)
	{
		ft_isvalid(queue, mlx->map);
		if (mlx->map[queue->front->cord->y][queue->front->cord->x] == 'E')
			valid_exit = 1;
		else if (mlx->map[queue->front->cord->y][queue->front->cord->x] == 'C')
			++valid_coins;
		ft_dequeue(queue);
		if (valid_exit && valid_coins == mlx->coin)
			while (queue->size)
				ft_dequeue(queue);
	}
	ft_clear((void **)queue->visited);
	if (valid_coins != mlx->coin || !valid_exit)
		ft_err(mlx->map, "\e[0;31mError: Player in the map has invalid path");
}

void	ft_isvalid(t_queue *queue, char **map)
{
	int	x;
	int	y;

	x = queue->front->cord->x;
	y = queue->front->cord->y;
	if (map[y + 1][x] != '1' && !queue->visited[y + 1][x])
		ft_enqueue(queue, map, x, y + 1);
	if (map[y - 1][x] != '1' && !queue->visited[y - 1][x])
		ft_enqueue(queue, map, x, y - 1);
	if (map[y][x + 1] != '1' && !queue->visited[y][x + 1])
		ft_enqueue(queue, map, x + 1, y);
	if (map[y][x - 1] != '1' && !queue->visited[y][x - 1])
		ft_enqueue(queue, map, x - 1, y);
}

void	ft_enqueue(t_queue *queue, char **map, int x, int y)
{
	t_node	*node;

	node = ft_newnode(queue, map, x, y);
	if (!queue->size)
		queue->front = node;
	if (queue->rear)
		queue->rear->next = node;
	queue->rear = node;
	queue->visited[y][x] = true;
	++queue->size;
}

t_node	*ft_newnode(t_queue *queue, char **map, int x, int y)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
	{
		while (queue->size)
			ft_dequeue(queue);
		ft_clear((void **)queue->visited);
		ft_err(map, NULL);
	}
	node->cord->x = x;
	node->cord->y = y;
	node->next = NULL;
	return (node);
}

void	ft_dequeue(t_queue *queue)
{
	t_node	*tmp_front;

	tmp_front = queue->front;
	queue->front = tmp_front->next;
	free(tmp_front);
	--queue->size;
}
