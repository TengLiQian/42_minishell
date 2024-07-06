/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 21:27:36 by lteng             #+#    #+#             */
/*   Updated: 2024/06/27 21:59:32 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	char	a;

	a = (char)c;
	ptr = (char *)s;
	while (*ptr != '\0')
	{
		if (*ptr == a)
			return ((char *)ptr);
		ptr++;
	}
	if (a == '\0')
		return ((char *)ptr);
	return (NULL);
}
