/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:59:51 by ael-khel          #+#    #+#             */
/*   Updated: 2022/10/15 10:59:51 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrlen(int n)
{
	int	nbrlen;

	nbrlen = (n == 0);
	while (n)
	{
		++nbrlen;
		n /= 10;
	}
	return (nbrlen);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		nbrlen;

	nbrlen = ft_nbrlen(n);
	str = malloc(nbrlen + 1);
	if (!str)
		return (NULL);
	str[nbrlen--] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		str[nbrlen--] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}
