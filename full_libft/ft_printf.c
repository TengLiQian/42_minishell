/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:03:47 by jolai             #+#    #+#             */
/*   Updated: 2024/03/07 16:02:18 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ptrconvert(unsigned long long value, int *count)
{
	if (value == 0)
	{
		write (1, "(nil)", 5);
		*count += 5;
	}
	else
	{
		write (1, "0x", 2);
		*count += 2;
		if (value > 16)
		{
			ft_printnbr((value / 16), count, "0123456789abcdef");
			ft_printnbr((value % 16), count, "0123456789abcdef");
		}
		else
			ft_printnbr(value, count, "0123456789abcdef");
	}
}

void	check_specifier(int *count, const char s, va_list ap)
{
	if (s == 'c' || s == 's')
		ft_printchars(ap, s, count);
	else if (s == 'p')
		ft_ptrconvert(va_arg(ap, unsigned long long), count);
	else if (s == 'x')
		ft_printnbr(va_arg(ap, unsigned int), count, "0123456789abcdef");
	else if (s == 'X')
		ft_printnbr(va_arg(ap, unsigned int), count, "0123456789ABCDEF");
	else if (s == 'd' || s == 'i')
		ft_printnbr(va_arg(ap, int), count, "0123456789");
	else if (s == 'u')
		ft_printnbr(va_arg(ap, unsigned int), count, "0123456789");
	else if (s == '%')
	{
		write(1, "%", 1);
		(*count)++;
	}
	else
	{
		write(1, "%", 1);
		write(1, &s, 1);
		(*count) += 2;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		*count;
	int		c;
	int		i;

	va_start(ap, str);
	i = 0;
	c = 0;
	count = &c;
	while (str[i])
	{
		if (str[i] == '%')
		{
			check_specifier(count, str[++i], ap);
			i++;
		}
		else
		{
			write(1, &str[i], 1);
			(*count)++;
			i++;
		}
	}
	va_end(ap);
	return (*count);
}
