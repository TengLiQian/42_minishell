/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:51:17 by jolai             #+#    #+#             */
/*   Updated: 2024/07/17 20:24:28 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_env_output(char *key, int end, t_env *env_list, int out_fd)
{
	if (get_env_key(env_list, key))
		ft_putstr_fd(get_env_val(env_list, key), out_fd);
	free (key);
	return (end);
}

void	heredoc_output(char *input, int expand, t_env *env_list, int out_fd)
{
	int		i;
	int		j;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			j = i + 1;
			while (input[j] && ft_isalnum(input[j]))
				j++;
			j--;
			if (j > i + 1 && expand == 0)
				i = heredoc_env_output(ft_substr(input, i + 1, j - i), j,
						env_list, out_fd);
			else
				ft_putchar_fd(input[i], out_fd);
		}
		else
			ft_putchar_fd(input[i], out_fd);
		i++;
	}
	ft_putchar_fd('\n', out_fd);
}

int	eof_checker(char *input, char *eof)
{
	char	*end;
	int		len;
	int		result;

	len = ft_strlen(eof);
	if ((eof[0] == '\'' || eof[0] == '\"') && eof[len - 1] == eof[0])
		end = ft_substr(eof, 1, len - 2);
	else
		end = ft_strdup(eof);
	if (ft_strcmp(input, end) == 0)
		result = 1;
	else
		result = 0;
	free(end);
	return (result);
}

void	heredoc_input(char *eof, int expand, t_env *env_list, int out_fd)
{
	char	*input;

	while (1)
	{
		input = readline(">");
		if (!input || eof_checker(input, eof))
			break ;
		heredoc_output(input, expand, env_list, out_fd);
		free(input);
		input = NULL;
	}
}
