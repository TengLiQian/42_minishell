/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:50:29 by lteng             #+#    #+#             */
/*   Updated: 2024/07/22 20:55:47 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*extract_content(char *string)
{
	int		len;
	char	*content;
	char	*start;
	char	*end;

	start = ft_strchr(string, '"');
	end = ft_strrchr(string, '"');
	if (!start || !end || start == end)
		return (NULL);
	start++;
	len = end - start;
	content = malloc(len + 1);
	if (!content)
		return (NULL);
	ft_strlcpy(content, start, len + 1);
	content[len] = '\0';
	return (content);
}

int	unclosed_quotes_s(char *string)
{
	int	i;
	int	count;

	i = 0;
	while (string[i])
	{
		count = 0;
		if (string[i] == '"')
			count++;
		if (count % 2 != 0)
			return (1);
		i++;
	}
	return (0);
}

int	unclosed_quotes_ss(char **strings)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (strings[i])
	{
		count = 0;
		j = 0;
		while (strings[i][j])
		{
			if (strings[i][j] == '"')
				count++;
			j++;
		}
		if (count % 2 != 0)
			return (1);
		i++;
	}
	return (0);
}
