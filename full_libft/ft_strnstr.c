/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:11:33 by jolai             #+#    #+#             */
/*   Updated: 2023/09/14 17:12:49 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(small) == 0)
		return ((char *)big);
	if (len <= 0)
		return (NULL);
	while (i < len && big[i])
	{
		j = 0;
		while (big[i + j] == small[j] && (i + j < len))
		{
			j++;
			if (small[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
