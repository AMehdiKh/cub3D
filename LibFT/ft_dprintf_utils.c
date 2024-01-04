/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 02:40:56 by ael-khel          #+#    #+#             */
/*   Updated: 2023/10/04 19:24:18 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_dpf(char c, t_dprintf *tab)
{
	tab->len += write(tab->fd, &c, 1);
}

void	ft_putstr_dpf(char *s, t_dprintf *tab)
{
	if (!s)
		s = "(null)";
	while (*s)
		tab->len += write(tab->fd, s++, 1);
}

void	ft_putnbr_dpf(long n, t_dprintf *tab)
{
	if (n < 0)
	{
		ft_putchar_dpf('-', tab);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_dpf(n / 10, tab);
	ft_putchar_dpf((n % 10) + 48, tab);
}

void	ft_puthex_dpf(unsigned long n, t_dprintf *tab)
{
	if (n >= 16)
		ft_puthex_dpf(n / 16, tab);
	if (tab->spec != 'X')
		tab->len += write(tab->fd, &"0123456789abcdef"[n % 16], 1);
	else
		tab->len += write(tab->fd, &"0123456789ABCDEF"[n % 16], 1);
}
