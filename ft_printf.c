/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lykalon <lykalon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:07:54 by lykalon           #+#    #+#             */
/*   Updated: 2021/11/18 22:02:34 by lykalon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//%c print a single character. - putchar
//%s print a string of characters. - putstr
//%p The void * pointer argument is printed in hexadecimal. - 0x + putnbt_base
//%d print a decimal (base 10) number. - putnbr
//%i print an integer in base 10. - putnbr
//%u print an unsigned decimal (base 10) number. - putnbr_unsgn
//%x print a number in hexadecimal (base 16), with lowercase. - putnbr_base
//%X print a number in hexadecimal (base 16), with uppercase. - putnbr_base
//%% print a percent sign. - %

#include "ft_printf.h"

åstatic int	ft_putptr(unsigned long int n)
{
	int	count;

	count = 0;
	if (n > 15)
	{
		count += ft_putptr(n / 16);
		count += ft_putptr(n % 16);
	}
	else
	{
		if (n < 10)
			count += ft_putchar((char)(n + '0'));
		else
			count += ft_putchar((char)(n - 10 + 'a'));
	}
	return (count);
}

static int	ft_parse(va_list ap, char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count = ft_putchar((char)va_arg(ap, int));
	else if (c == 's')
		count = ft_putstr(va_arg(ap, char *));
	else if (c == 'p')
	{
		count = ft_putstr("0x");
		count += ft_putptr(va_arg(ap, unsigned long int));
	}
	else if ((c == 'd') || (c == 'i'))
		count = ft_putnbr(va_arg(ap, int));
	else if (c == 'u')
		count = ft_putnbr_unsgn(va_arg(ap, unsigned int));
	else if (c == 'x')
		count = ft_putnbr_base(va_arg(ap, unsigned int), 0);
	else if (c == 'X')
		count = ft_putnbr_base(va_arg(ap, unsigned int), 1);
	else if (c == '%')
		count = ft_putchar('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		count;
	int		i;

	count = 0;
	i = 0;
	va_start(ap, str);
	while (*(str + i))
	{
		if (*(str + i) == '%')
		{
			count += ft_parse(ap, *(str + i + 1));
			i++;
		}
		else
			count += ft_putchar(*(str + i));
		i++;
	}
	va_end(ap);
	return (count);
}
