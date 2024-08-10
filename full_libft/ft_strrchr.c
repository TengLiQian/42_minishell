/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:55:33 by jolai             #+#    #+#             */
/*   Updated: 2023/09/19 16:10:45 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		j;
	char	*ptr;

	i = ft_strlen(s);
	j = -1;
	ptr = (char *)s;
	if ((char)c == '\0' && ptr[i] == '\0')
		return (&ptr[i]);
	i--;
	while (ptr[i] && i >= 0)
	{
		if (ptr[i] == (char)c)
		{
			j = i;
			i = 0;
		}
		i--;
	}
	if (j >= 0)
		return (&ptr[j]);
	return (0);
}
