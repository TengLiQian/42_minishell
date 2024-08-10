/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:32:35 by jolai             #+#    #+#             */
/*   Updated: 2023/09/20 13:56:30 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	ft_free_all(char **array, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}

static int	ft_assign(char **base, char const *s, char c)
{
	size_t	start;
	size_t	end;
	size_t	i;

	end = 0;
	i = 0;
	while (s[end])
	{
		start = end;
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		if (end > start)
		{
			base[i] = ft_substr(s, start, (end - start));
			if (!base[i])
				return (ft_free_all(base, i));
			i++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**base;
	size_t	len;
	int		status;

	status = 0;
	len = ft_count_words(s, c);
	base = (char **)ft_calloc((len + 1), sizeof(char *));
	if (!base || !s)
		return (NULL);
	status = ft_assign(base, s, c);
	if (status == 0)
		return (NULL);
	base[len] = 0;
	return (base);
}
