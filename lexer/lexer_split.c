/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:45:26 by lteng             #+#    #+#             */
/*   Updated: 2024/07/15 12:15:53 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lexer_wordlen(char const *s)
{
	int	len;

	len = 0;
	while (*s && is_space(*s) != 1)
	{
		len++;
		s++;
	}
	return (len);
}

void	*lexer_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

int	lexer_wordcount(char const *s)
{
	int	words;

	words = 0;
	while (*s)
	{
		if (is_space(*s) != 1)
		{
			s += (lexer_wordlen(s));
			words++;
		}
		else
			s++;
	}
	return (words);
}

char	**lexer_split(char const *s)
{
	char		**strings;
	int		i;
	int		words;

	words = lexer_wordcount(s);
	strings = (char **)malloc(sizeof(char *) * (words + 1));
	if (!strings || !s)
		return (NULL);
	strings[words] = NULL;
	i = 0;
	while (*s)
	{
		if (is_space(*s) != 1)
		{
			strings[i] = ft_substr(s, 0, lexer_wordlen(s));
			if (!strings[i])
				return (lexer_free(strings));
			i++;
			s += lexer_wordlen(s);
		}
		else
			s++;
	}
	return (strings);
}
