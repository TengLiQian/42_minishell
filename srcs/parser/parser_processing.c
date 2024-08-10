/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:15:04 by jolai             #+#    #+#             */
/*   Updated: 2024/07/18 17:15:09 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*heredoc_eof_parser(t_node *ptr, t_node *ptr_hd)
{
	while (ptr && ptr->type >= QUOTE && ptr->type <= ARG)
	{
		if (ptr->type == QUOTE || ptr->type == DBLQUOTE)
			ptr_hd->heredoc_expand = 1;
		else
			ptr->type = CMD;
		ptr = ptr->next;
	}
	return (ptr);
}

t_node	*heredoc_checker(t_node *arg_list)
{
	t_node	*ptr_hd;
	t_node	*ptr;

	ptr = arg_list;
	while (ptr)
	{
		if (ptr->prev && ptr->prev->type == HEREDOC)
		{
			ptr_hd = ptr->prev;
			while (ptr && ptr->type == SPACES)
				ptr = ptr->next;
			if (ptr && ptr->type >= QUOTE && ptr->type <= ARG)
			{
				ptr = heredoc_eof_parser(ptr, ptr_hd);
				continue ;
			}
		}
		if (ptr)
			ptr = ptr->next;
	}
	return (arg_list);
}

t_node	*combine_args(t_node *arg_list)
{
	t_node	*ptr;
	char	*new;

	ptr = arg_list;
	while (ptr)
	{
		if (ptr->type == CMD && ptr->next && ptr->next->type == CMD)
		{
			new = ft_strjoin(ptr->data, ptr->next->data);
			free(ptr->data);
			ptr->data = new;
			arg_list = del_arg_node(ptr->next);
			continue ;
		}
		ptr = ptr->next;
	}
	return (arg_list);
}

t_node	*remove_spaces(t_node *arg_list)
{
	t_node	*ptr;

	ptr = arg_list;
	while (ptr)
	{
		if (ptr->type == SPACES)
		{
			arg_list = del_arg_node(ptr);
			ptr = arg_list;
			continue ;
		}
		if (ptr)
			ptr = ptr->next;
	}
	return (arg_list);
}

t_node	*convert_to_args(t_node *arg_list)
{
	t_node	*ptr;

	ptr = arg_list;
	while (ptr)
	{
		if (ptr->type == CMD && ptr->prev && ptr->prev->type == CMD)
		{
			while (ptr && (ptr->type == CMD || ptr->type == ARG))
			{
				ptr->type = ARG;
				ptr = ptr->next;
			}
			continue ;
		}
		if (ptr)
			ptr = ptr->next;
	}
	return (arg_list);
}
