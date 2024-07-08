/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 00:42:13 by lteng             #+#    #+#             */
/*   Updated: 2024/07/02 00:05:09 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer_nextchar(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->index < (int)(ft_strlen(lexer->content)))
	{
		lexer->index += 1;
		lexer->c = lexer->content[lexer->index];
	}
}

void	lexer_skipspace(t_lexer *lexer)
{
	while (lexer->c == ' ')
		lexer_nextchar(lexer);
}

char	*lexer_chartostr(t_lexer *lexer)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

t_token_type	get_token(char *token, int len)
{
	if (ft_strncmp(token, "<", len) == 0)
		return (T_REDIR_L);
	if (ft_strncmp(token, ">", len) == 0)
		return (T_REDIR_R);
	if (ft_strncmp(token, "<<", len) == 0)
		return (T_HEREDOC);
	if (ft_strncmp(token, ">>", len) == 0)
		return (T_APPEND);
	if (ft_strncmp(token, "(", len) == 0)
		return (T_BRAC_L);
	if (ft_strncmp(token, ")", len) == 0)
		return (T_BRAC_R);
	if (ft_strncmp(token, "|", len) == 0)
		return (T_PIPE);
}

void	*ft_realloc(void *ptr, int old, int new)
{
	void	*new_ptr;

	new_ptr = NULL;
	if (!new_ptr)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (ft_calloc(new, sizeof(char)));
	new_ptr = ft_calloc(new, sizeof(char));
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (new < old)
		old = new;
	ft_memcpy(new_ptr, ptr, old);
	free(ptr);
	return (new_ptr);
}
