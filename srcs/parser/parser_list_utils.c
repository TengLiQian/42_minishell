/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:15:04 by jolai             #+#    #+#             */
/*   Updated: 2024/07/08 20:48:24 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_arg_node(char *data, int type)
{
	t_node	*new_arg;

	new_arg = (t_node *)ft_calloc(1, sizeof(t_node));
	new_arg->data = ft_strdup(data);
	new_arg->type = type;
	return (new_arg);
}

t_node	*add_arg_node(t_node *arg_list, char *data, int type)
{
	t_node	*new_arg;
	t_node	*ptr;

	new_arg = new_arg_node(data, type);
	ptr = arg_list;
	if (!ptr)
	{
		new_arg->prev = NULL;
		return (new_arg);
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new_arg;
	new_arg->prev = ptr;
	while (arg_list->prev != NULL)
		arg_list = arg_list->prev;
	return (arg_list);
}

t_node	*move_arg_node_back(t_node *arg_list, t_node *prev, t_node *next)
{
	arg_list = prev;
	if (next)
	{
		arg_list->next = next;
		next->prev = arg_list;
	}
	else
		arg_list->next = NULL;
	return (arg_list);
}

t_node	*del_arg_node(t_node *arg_list)
{
	t_node	*ptr;

	if (!arg_list)
		return (NULL);
	ptr = arg_list;
	free (ptr->data);
	if (ptr->prev)
		arg_list = move_arg_node_back(arg_list, ptr->prev, ptr->next);
	else if (ptr->next)
	{
		arg_list = ptr->next;
		arg_list->prev = NULL;
	}
	else
		arg_list = NULL;
	free (ptr);
	ptr = NULL;
	if (arg_list)
	{
		while (arg_list->prev != NULL)
			arg_list = arg_list->prev;
	}
	return (arg_list);
}

void	free_arg_list(t_node *arg_list)
{
	t_node	*ptr;

	if (!arg_list)
		return ;
	while (arg_list->prev != NULL)
		arg_list = arg_list->prev;
	while (arg_list)
	{
		ptr = arg_list;
		free (ptr->data);
		arg_list = ptr->next;
		free (ptr);
	}
	free (arg_list);
	arg_list = NULL;
}
/*
t_node	*combine_node(t_node *ptr1, t_node *ptr2, int type)
{
	t_node	*new;
	char	*newdata;

	if (!ptr1 && !ptr2)
		return (NULL);
	if (!ptr1)
		return (ptr2);
	if (!ptr2)
		return (ptr1);
	newdata = ft_strjoin(ptr1->data, ptr2->data);
	new = new_arg_node(newdata, type);
	new->prev = ptr1->prev;
	new->next = ptr2->next;
	del_arg_node(ptr1);
	del_arg_node(ptr2);
	return (new);
}*/
