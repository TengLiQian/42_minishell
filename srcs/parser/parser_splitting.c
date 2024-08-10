/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_splitting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:44:47 by jolai             #+#    #+#             */
/*   Updated: 2024/07/22 22:44:51 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_operator(char c)
{
	if (c == '|'
		|| c == '<' || c == '>'
		|| c == '\'' || c == '\"'
		|| c == '$' || c == '?'
		|| c == ' ')
		return (1);
	else
		return (0);
}

size_t	ft_count_args(const char *input)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		count++;
		if (ft_is_operator(input[i]) == 1)
		{
			i++;
			if ((input[i] == '>' || input[i] == '<')
				&& input[i] == input[i - 1])
				i++;
			while (input[i] == ' ' && input[i] == input[i - 1])
				i++;
		}
		else
		{
			i++;
			while (input[i] && ft_is_operator(input[i]) == 0)
				i++;
		}
	}
	return (count);
}

size_t	ft_find_arg_end(const char *input, size_t start)
{
	size_t	end;

	end = start;
	if (ft_is_operator(input[start]) == 1)
	{
		if (input[end] && ft_is_operator(input[end]) == 1)
			end++;
		if (input[end] && (input[end] == '<' || input[end] == '>')
			&& (input[end] == input[end - 1]))
			end++;
		else
			while (input[end] && (input[end] == ' ')
				&& (input[end] == input[end - 1]))
				end++;
	}
	else
	{
		while (input[end] && ft_is_operator(input[end]) == 0)
			end++;
	}
	return (end);
}

int	ft_assign_args(char **splitted, const char *input)
{
	size_t	start;
	size_t	end;
	size_t	i;

	end = 0;
	i = 0;
	while (input[end])
	{
		start = end;
		end = ft_find_arg_end(input, start);
		if (end > start)
		{
			splitted[i] = ft_substr(input, start, (end - start));
			if (!splitted[i])
			{
				while (i > 0)
					free(splitted[--i]);
				free(splitted);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

char	**arg_split(const char *input)
{
	char	**splitted;
	size_t	len;
	int		status;

	status = 0;
	if (!input)
		return (NULL);
	len = ft_count_args(input);
	splitted = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!splitted)
		return (NULL);
	status = ft_assign_args(splitted, input);
	if (status == 0)
		return (NULL);
	splitted[len] = 0;
	return (splitted);
}
