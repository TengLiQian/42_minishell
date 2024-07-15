/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:21:34 by lteng             #+#    #+#             */
/*   Updated: 2024/07/15 12:29:38 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

t_token_type	get_token(char *token, int len)
{
	if (ft_strncmp(token, "<", len) == 0)
		return (T_REDIR_L);
	else if (ft_strncmp(token, ">", len) == 0)
		return (T_REDIR_R);
	else if (ft_strncmp(token, "<<", len) == 0)
		return (T_HEREDOC);
	else if (ft_strncmp(token, ">>", len) == 0)
		return (T_APPEND);
	else if (ft_strncmp(token, "|", len) == 0)
		return (T_PIPE);
	else
		return (T_STRING);
}

t_token	*token_init(int type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->token_type = type;
	token->value = value;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **list, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	else if (!*list)
	{
		*list = new;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

t_token *tokenize(t_minishell *shell, char *input)
{
	int		i;
	int		j;
	char	**strings;

	i = 0;
	j = 0;
	if (input[i])
	{
		while (is_space(input[i]))
			i++;
		if (!input[i])
			return (NULL);
	}
	while (input[i])
	{
		strings = lexer_split(input);
		if (strings[j])
		{
			shell->tokens = token_init(get_token(strings[j], ft_strlen(strings[j])), strings[j]);
			j++;
		}
		while (strings[j])
		{
			add_token(shell->tokens, token_init(get_token(strings[j], ft_strlen(strings[j])), strings[j]));
			j++;
		}
	}
	// if (lexer_quotes(shell->tokens) == -1 || lexer_syntax(shell->tokens) == -1)
		// return (NULL);
	return (shell->tokens);
}
