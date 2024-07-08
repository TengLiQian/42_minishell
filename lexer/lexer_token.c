/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 23:48:58 by lteng             #+#    #+#             */
/*   Updated: 2024/07/01 22:02:49 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	