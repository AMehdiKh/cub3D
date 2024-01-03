/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:25:12 by ael-khel          #+#    #+#             */
/*   Updated: 2024/01/02 19:32:36 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_arg(int ac, char *av)
{
	if (ac != 2)
		ft_err("[!] Error: It must be like this: ./cub3d [map_name].cub", NULL);
	if (ft_strlen(av) <= 4)
		ft_err("[!] Error: The map's name format is incorrect", NULL);
	if (ft_strncmp(".cub", av + (ft_strlen(av) - 4), 4))
		ft_err("[!] Error: The map must be in [.cub] format", NULL);
}

int	main(int ac, char **av)
{
	t_map	map_data[1];

	ft_bzero(map_data, sizeof(map_data));
	ft_check_arg(ac, av[1]);
	ft_parse_map(map_data, av[1]);
	ft_check_map(map_data);
	ft_graphics(map_data);

	return (EXIT_SUCCESS);
}
