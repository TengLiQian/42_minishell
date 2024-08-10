/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:15:04 by jolai             #+#    #+#             */
/*   Updated: 2024/07/18 17:13:37 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//everything change to CMD, except ENV_VARS in DBLQUOTE
t_node	*process_quotes(t_node *start)
{
	t_node	*ptr;
	int		flag;

	ptr = start;
	flag = CMD;
	while (ptr)
	{
		if (flag != CMD)
		{
			if (ptr->type == flag)
				flag = CMD;
			else if (flag == QUOTE
				|| (flag == DBLQUOTE && ptr->type != ENV_VAR))
				ptr->type = CMD;
		}
		else if (ptr->type == QUOTE || ptr->type == DBLQUOTE)
			flag = ptr->type;
		ptr = ptr->next;
	}
	return (start);
}

//if between quotes are empty then insert null ARG
t_node	*remove_quotes(t_node *arg_list)
{
	t_node	*ptr;

	if (!arg_list)
		return (NULL);
	ptr = arg_list;
	while (ptr)
	{
		if (ptr->type == QUOTE || ptr->type == DBLQUOTE)
		{
			if (ptr->next && ptr->next->type == ptr->type)
			{
				free (ptr->next->data);
				ptr->next->data = ft_strdup("");
				ptr->next->type = CMD;
				arg_list = del_arg_node(ptr);
			}
			else
				arg_list = del_arg_node(ptr);
			ptr = arg_list;
			continue ;
		}
		ptr = ptr->next;
	}
	return (arg_list);
}

t_node	*split_env_val(t_node *arg_list, t_node *ptr, char *val)
{
	char	**vals;
	t_node	*new;
	int		i;

	i = 0;
	new = NULL;
	vals = ft_split(val, ' ');
	while (vals[i])
	{
		if (i != 0)
			new = add_arg_node(new, " ", SPACES);
		new = add_arg_node(new, vals[i], CMD);
		i++;
	}
	if (!vals[0])
		new = add_arg_node(new, "", CMD);
	new->prev = ptr->prev;
	ptr->prev->next = new;
	while (new->next != NULL)
		new = new->next;
	new->next = ptr;
	ptr->prev = new;
	free_2d_c(vals);
	arg_list = del_arg_node(ptr);
	return (arg_list);
}

t_node	*insert_env_val(t_shell *shell, t_node *ptr, t_node *next)
{
	char	*val;

	if (ft_strncmp(" ", next->data, 1) == 0)
	{
		ptr->type = CMD;
		return (shell->args);
	}
	else if (ft_strcmp("?", next->data) == 0)
	{
		val = ft_itoa(shell->exit_status);
		shell->args = split_env_val(shell->args, next, val);
		free (val);
	}
	else
	{
		val = get_env_val(shell->env_list, next->data);
		if (val)
			shell->args = split_env_val(shell->args, next, val);
		else
			shell->args = del_arg_node(next);
	}
	shell->args = del_arg_node(ptr);
	return (shell->args);
}

t_shell	*expand_env_var(t_shell *shell)
{
	t_node	*ptr;

	ptr = shell->args;
	while (ptr)
	{
		if (ptr->type == ENV_VAR)
		{
			if (ptr->next && ptr->next->type != DBLQUOTE)
			{
				if (ptr->next->type == CMD || ptr->next->type == ARG)
					shell->args = insert_env_val(shell, ptr, ptr->next);
				else if (ptr->next->type != SPACES)
					shell->args = del_arg_node(ptr);
				else
					ptr->type = CMD;
			}
			else
				ptr->type = CMD;
			ptr = shell->args;
			continue ;
		}
		ptr = ptr->next;
	}
	return (shell);
}
