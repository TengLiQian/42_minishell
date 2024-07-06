/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:21:34 by lteng             #+#    #+#             */
/*   Updated: 2024/07/02 00:06:39 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*lexer_init(char *input)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->content = input;
	lexer->index = 0;
	lexer->c = input[lexer->index];
	return (lexer);
}
/*
t_token	lexer_gettoken(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->index < ft_strlen(lexer->content))
	{
		if (lexer->c == ' ')
			lexer_skipspace(lexer);
	}
}*/
// Need to add token to the back

t_token	*lexer_string(t_lexer *lexer)
{
	char	*value;
	char	*c;
	int		len;

	lexer_next(lexer);
	value = malloc(sizeof(char));
	if (!value)
		return (NULL);
	value[0] = '\0';
	len = 0;
	while (lexer->c != '"')
	{
		c = lexer_chartostr(lexer);
		if (!c)
		{
			free(value);
			return (NULL);
		}
		value = ft_realloc(value, len + 1, len + 2);
		if (!value)
		{
			free(c);
			return (NULL);
		}
		ft_strlcat(value, c, len + 2);
		len += 1;
		lexer_next(lexer);
	}
	lexer_next(lexer);
	return (token_init(T_STRING, value));
}

/*
int main(void)
{
	t_lexer *lexer;
	t_token *token;

	lexer = lexer_init("This is me");
	if (!lexer) {
		printf("Lexer initialization failed\n");
		return 1;
	}

	token = lexer_string(lexer);
	if (token) {
		printf("Token type: %d, value: %s\n", token->token_type, token->value);
		free(token->value);
		free(token);
	} else {
		printf("Token initialization failed\n");
	}

	// Clean up lexer if needed
	// lexer_cleanup(lexer);

	return 0;
}*/

