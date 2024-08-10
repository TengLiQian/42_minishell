/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:43:47 by jolai             #+#    #+#             */
/*   Updated: 2024/03/07 16:04:25 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printchars(va_list ap, char type, int *count)
{
	int		i;
	char	c;
	char	*str;

	i = 0;
	if (type == 'c')
	{
		c = va_arg(ap, int);
		write (1, &c, 1);
		(*count)++;
		return ;
	}
	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	while (str[i])
	{
		write (1, &str[i], 1);
		i++;
		(*count)++;
	}
}

void	ft_printnbr(long long num, int *count, char *base)
{
	char				c;
	unsigned long long	n;
	unsigned long long	len;

	len = ft_strlen(base);
	if (num < 0)
	{
		write (1, "-", 1);
		n = -num;
		(*count)++;
	}
	else
		n = num;
	if (n >= len)
	{
		ft_printnbr((n / len), count, base);
		ft_printnbr((n % len), count, base);
	}
	else
	{
		c = base[n];
		write (1, &c, 1);
		(*count)++;
	}
}
