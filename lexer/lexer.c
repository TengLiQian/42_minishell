/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:21:34 by lteng             #+#    #+#             */
/*   Updated: 2024/07/15 18:40:00 by lteng            ###   ########.fr       */
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
	char **strings = lexer_split(input);
	if (!strings)
		return (NULL);

	t_token *head = NULL;
	t_token *tail = NULL; // Track the tail of the list

	for (int j = 0; strings[j] != NULL; j++)
	{
		t_token *new_token = token_init(get_token(strings[j],
					strlen(strings[j])), strings[j]);
		if (new_token)
		{
			if (!head)
			{
				head = new_token;
				tail = new_token;
			}
			else
			{
				add_token(&tail, new_token); // Append new token to the list
				tail = new_token;            // Update tail to the new token
			}
		}
	}

	// Free the strings array if it was dynamically allocated
	// free_strings_array(strings);

	return (head); // Return the head of the list of tokens
}