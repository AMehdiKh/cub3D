/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:47:09 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/15 11:22:02 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_check_spec(const char *format, t_printf *tab)
{
	tab->spec = *format;
	if (*format == '%')
		ft_putchar('%', tab);
	else if (*format == 'c')
		ft_putchar(va_arg(tab->ap, int), tab);
	else if (*format == 's')
		ft_putstr(va_arg(tab->ap, char *), tab);
	else if (*format == 'u')
		ft_putnbr(va_arg(tab->ap, unsigned int), tab);
	else if (*format == 'd' || *format == 'i')
		ft_putnbr(va_arg(tab->ap, int), tab);
	else if (*format == 'x' || *format == 'X')
		ft_puthex(va_arg(tab->ap, unsigned int), tab);
	else if (*format == 'p')
	{
		ft_putstr("0x", tab);
		ft_puthex(va_arg(tab->ap, unsigned long), tab);
	}
	if (*format)
		++format;
	return (format);
}

int	ft_printf(const char *format, ...)
{
	t_printf	tab[1];

	tab->len = 0;
	va_start(tab->ap, format);
	while (*format)
	{
		if (*format == '%')
			format = ft_check_spec(format + 1, tab);
		else
			tab->len += write(1, format++, 1);
	}
	va_end(tab->ap);
	return (tab->len);
}
