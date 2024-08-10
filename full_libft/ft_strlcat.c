/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:04:23 by jolai             #+#    #+#             */
/*   Updated: 2023/09/07 18:53:16 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	j;
	size_t	dlength;
	size_t	slength;

	j = 0;
	dlength = ft_strlen(dst);
	slength = ft_strlen(src);
	if (size == 0 || size <= dlength)
		return (slength + size);
	while (src[j] && j < (size - dlength - 1))
	{
		dst[dlength + j] = src[j];
		j++;
	}
	dst[dlength + j] = '\0';
	return (dlength + slength);
}
