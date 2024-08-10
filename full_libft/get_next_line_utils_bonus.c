/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:20:55 by jolai             #+#    #+#             */
/*   Updated: 2024/03/30 20:51:34 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	*ft_calloc(size_t num, size_t size)
{
	size_t	i;
	size_t	totalsize;
	char	*space;

	i = 0;
	totalsize = num * size;
	if (totalsize == 0)
		return (NULL);
	space = (char *) malloc(totalsize * sizeof(char));
	if (!space)
		return (NULL);
	while (i < totalsize)
	{
		space[i] = '\0';
		i++;
	}
	return (space);
}

int	ft_strlen(char const *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}*/

size_t	ft_find_newline(char const *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*ft_strndup(char *s, size_t len)
{
	size_t	i;
	char	*result;

	i = 0;
	if (!s || ft_strlen(s) == 0 || len == 0)
		return (NULL);
	result = (char *)ft_calloc((len + 1), sizeof(char));
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*result;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	result = (char *)ft_calloc((i + j + 1), sizeof(char));
	if (!result)
		return (NULL);
	while (j > 0)
	{
		j--;
		result[i + j] = s2[j];
	}
	while (i > 0)
	{
		i--;
		result[i] = s1[i];
	}
	free (s1);
	return (result);
}
