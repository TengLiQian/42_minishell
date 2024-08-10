/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:12:09 by jolai             #+#    #+#             */
/*   Updated: 2024/05/29 22:18:31 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = (char *) malloc ((ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (s1 && s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}
