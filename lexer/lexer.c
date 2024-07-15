/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:21:34 by lteng             #+#    #+#             */
/*   Updated: 2024/07/15 23:45:55 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	token->value = ft_strdup(value);
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

t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*tail;
	char	**strings;
	int		i;
	t_token	*new_token;

	head = NULL;
	tail = NULL;
	strings = lexer_split(input);
	if (!strings)
		return (NULL);
	i = 0;
	while (strings[i])
	{
		new_token = token_init(get_token(strings[i], strlen(strings[i])),
				strings[i]);
		if (!head)
			head = new_token;
		else
			add_token(&tail, new_token);
		tail = new_token;
		i++;
	}
	lexer_free(strings);
	return (head);
}

/*
void	join_token(t_token *head, t_token *tail, char **strings)
{
	int		i;
	t_token	*new_token;

	i = 0;
	while (strings[i])
	{
		new_token = token_init(get_token(strings[i], strlen(strings[i])),
				strings[i]);
		if (new_token)
		{
			if (!head)
			{
				head = new_token;
				tail = new_token;
			}
			else
			{
				add_token(&tail, new_token);
				tail = new_token;
			}
		}
		i++;
	}
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*tail;
	char	**strings;

	head = NULL;
	tail = NULL;
	strings = lexer_split(input);
	if (!strings)
		return (NULL);
	join_token(head, tail, strings);
	return (head);
}
*/
