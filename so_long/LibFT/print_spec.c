/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 02:40:56 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/15 11:21:53 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c, t_printf *tab)
{
	tab->len += write(1, &c, 1);
}

void	ft_putstr(char *s, t_printf *tab)
{
	if (!s)
		s = "(null)";
	while (*s)
		tab->len += write(1, s++, 1);
}

void	ft_putnbr(long n, t_printf *tab)
{
	if (n < 0)
	{
		ft_putchar('-', tab);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10, tab);
	ft_putchar((n % 10) + 48, tab);
}

void	ft_puthex(unsigned long n, t_printf *tab)
{
	if (n >= 16)
		ft_puthex(n / 16, tab);
	if (tab->spec != 'X')
		tab->len += write(1, &"0123456789abcdef"[n % 16], 1);
	else
		tab->len += write(1, &"0123456789ABCDEF"[n % 16], 1);
}
