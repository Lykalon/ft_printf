/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lykalon <lykalon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:25:46 by lykalon           #+#    #+#             */
/*   Updated: 2021/11/18 21:54:26 by lykalon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	count;

	if (str == 0)
		return (write(1, "(null)", 6));
	count = 0;
	while (*(str + count))
		count += ft_putchar(*(str + count));
	return (count);
}

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n > 9)
	{
		count += ft_putnbr(n / 10);
		count += ft_putnbr(n % 10);
	}
	else
		count += ft_putchar((char)(n + '0'));
	return (count);
}

int	ft_putnbr_unsgn(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
	{
		count += ft_putnbr(n / 10);
		count += ft_putnbr(n % 10);
	}
	else
		count += ft_putchar((char)(n + '0'));
	return (count);
}

int	ft_putnbr_base(unsigned long int n, int upper)
{
	int		count;

	count = 0;
	if (n > 15)
	{
		count += ft_putnbr_base(n / 16, upper);
		count += ft_putnbr_base(n % 16, upper);
	}
	else
	{
		if (n < 10)
			count += ft_putchar(n + '0');
		else
		{
			if (upper)
				count += ft_putchar(n - 10 + 'A');
			else
				count += ft_putchar(n - 10 + 'a');
		}
	}
	return (count);
}
