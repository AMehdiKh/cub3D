/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:25:12 by ael-khel          #+#    #+#             */
/*   Updated: 2023/10/03 20:23:55 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	ft_err(char **ptr, char *str)
{
	if (str)
		ft_putendl_fd(str, 2);
	else if (errno)
		perror("\e[0;31mError ");
	ft_clear((void **)ptr);
	ft_printf("\e[0;32mIt must run like this : ./cub3d [map_name].cub\n");
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **env)
{
	if (ac != 2)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
