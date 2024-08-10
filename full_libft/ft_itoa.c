/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:30:31 by jolai             #+#    #+#             */
/*   Updated: 2024/03/20 21:16:11 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_length(long n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	if (n == 0)
		len = 1;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	size_t	i;

	num = n;
	i = check_length(num) - 1;
	str = (char *)ft_calloc(check_length(n) + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (num >= 0)
	{
		str[i] = (num % 10) + '0';
		num /= 10;
		i--;
		if (num == 0)
			num = -1;
	}
	str[check_length(n)] = '\0';
	return (str);
}
