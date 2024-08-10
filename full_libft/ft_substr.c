/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:22:17 by jolai             #+#    #+#             */
/*   Updated: 2023/09/19 19:27:52 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (!s || (start >= (size_t)ft_strlen(s)) || (len <= 0))
		return ((char *)ft_calloc(1, 1));
	if (start + len > (size_t)ft_strlen(s))
		len = (size_t)ft_strlen(s) - (size_t)start;
	sub = (char *) ft_calloc ((len + 1), sizeof(char));
	if (!sub)
		return (NULL);
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[len] = '\0';
	return (sub);
}
