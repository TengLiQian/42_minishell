/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:34:22 by jolai             #+#    #+#             */
/*   Updated: 2024/07/08 17:41:28 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(char *token)
{
	ft_putstr_fd(" syntax error near unexpected token \'", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("\'", 2);
}

int	syntax_pipe_check(t_node *pipe_node, t_node *args)
{
	t_node	*ptr;

	ptr = args;
	while (ptr != pipe_node && ptr->type != SPACES)
		ptr = ptr->next;
	if (ptr == pipe_node)
	{
		print_syntax_error(pipe_node->data);
		return (0);
	}
	ptr = pipe_node->next;
	while (ptr && ptr->type == SPACES)
		ptr = ptr->next;
	if (!ptr || ptr->type == PIPE)
	{
		print_syntax_error(pipe_node->data);
		return (0);
	}
	return (1);
}

int	syntax_redir_check(t_node *redir_node)
{
	t_node	*ptr;

	ptr = redir_node->next;
	while (ptr && ptr->type == SPACES)
		ptr = ptr->next;
	if (!ptr || (ptr->type != CMD && ptr->type != ARG
			&& ptr->type != QUOTE && ptr->type != DBLQUOTE))
	{
		print_syntax_error(redir_node->data);
		return (0);
	}
	return (1);
}

int	syntax_quote_check(t_node *args)
{
	t_node	*ptr1;
	t_node	*ptr2;

	ptr1 = args;
	while (ptr1)
	{
		if (ptr1->type == QUOTE || ptr1->type == DBLQUOTE)
		{
			ptr2 = ptr1->next;
			while (ptr2 && ptr2->type != ptr1->type)
				ptr2 = ptr2->next;
			if (!ptr2)
			{
				print_syntax_error(ptr1->data);
				return (0);
			}
			ptr1 = ptr2;
		}
		ptr1 = ptr1->next;
	}
	return (1);
}

int	syntax_check(t_node *args)
{
	t_node	*ptr;

	ptr = args;
	if (!syntax_quote_check(args))
		return (0);
	while (ptr)
	{
		if (ptr->type == PIPE && !syntax_pipe_check(ptr, args))
			return (0);
		else if (ptr->type >= REDIR_IN && ptr->type <= HEREDOC
			&& !syntax_redir_check(ptr))
			return (0);
		ptr = ptr->next;
	}
	return (1);
}
