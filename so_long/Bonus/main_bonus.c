/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 07:35:40 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/15 03:19:59 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	main(int ac, char **av)
{
	t_mlx	mlx[1];

	if (ac != 2)
		ft_err(NULL, "\e[0;31mError: More or less than one map entered");
	ft_check_arg(ft_memset(mlx, 0, sizeof(t_mlx)), av[1]);
	mlx->map = ft_parse(av[1]);
	map_check(mlx);
	ft_bfs(mlx);
	ft_graphics(mlx);
	return (0);
}

void	ft_check_arg(t_mlx *mlx, char *av)
{
	mlx_t	*win;

	if (ft_strlen(av) <= 4)
		ft_err(NULL, "\e[0;31mError: Map's name is incorrect");
	if (ft_strncmp(".ber", av + (ft_strlen(av) - 4), 4))
		ft_err(NULL, "\e[0;31mError: The map must be in [.ber] format");
	win = mlx_init(1, 1, "this is only for fetching monitor size", false);
	if (!win)
		ft_err(NULL, "\e[0;31mError: MLX init for monitor size failed");
	mlx_get_monitor_size(0, &mlx->max_width, &mlx->max_height);
	mlx_terminate(win);
}

char	**ft_parse(char *map_name)
{
	int	fd;

	map_name = ft_strjoin("./maps/", map_name);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		fd = open(map_name + 7, O_RDONLY);
		if (fd < 0)
		{
			free(map_name);
			ft_err(NULL, NULL);
		}
	}
	free(map_name);
	return (ft_check_newline(ft_line(fd)));
}

char	*ft_line(int fd)
{
	char	*buffer;
	char	*line;
	int		nbyte;

	buffer = ft_calloc(4096, 1);
	line = ft_calloc(1, 1);
	nbyte = 1;
	if (!buffer || !line)
		ft_free_return(line, buffer);
	if (!buffer || !line)
		ft_err(NULL, NULL);
	while (nbyte)
	{
		nbyte = read(fd, buffer, 4096);
		if (nbyte < 0)
		{
			ft_free_return(line, buffer);
			ft_err(NULL, NULL);
		}
		buffer[nbyte] = '\0';
		line = ft_strjoin_long(line, buffer);
	}
	close(fd);
	free(buffer);
	return (line);
}

char	**ft_check_newline(char *line)
{
	char	**map;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1] == '\n')
		{
			free(line);
			ft_err(NULL, "\e[0;31mError: The map has invalid characters");
		}
		++i;
	}
	map = ft_split(line, '\n');
	free(line);
	if (!map)
		ft_err(map, NULL);
	if (!*map)
		ft_err(map, "\e[0;31mError: The map is empty");
	return (map);
}
