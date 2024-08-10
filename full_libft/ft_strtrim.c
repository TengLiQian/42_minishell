/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:56:02 by jolai             #+#    #+#             */
/*   Updated: 2024/04/12 15:54:38 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimmed;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen((char *)s1) - 1;
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	while (end > start && ft_strchr(set, s1[end]) && s1[end])
		end--;
	trimmed = ft_substr(s1, start, end - start + 1);
	return (trimmed);
}
