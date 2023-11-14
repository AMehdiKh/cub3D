/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:25:12 by ael-khel          #+#    #+#             */
/*   Updated: 2023/10/25 20:50:18 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LibFT/libft.h"
#include "cub3d.h"

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
