/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:45:20 by jolai             #+#    #+#             */
/*   Updated: 2024/07/19 17:23:44 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*convert_type(int type)
{
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == REDIR_APPEND)
		return ("REDIR_APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == QUOTE)
		return ("QUOTE");
	if (type == DBLQUOTE)
		return ("DBLQUOTE");
	if (type == ENV_VAR)
		return ("ENV_VAR");
	if (type == CMD)
		return ("CMD");
	if (type == ARG)
		return ("ARG");
	if (type == SPACES)
		return ("SPACES");
	return ("ERROR");
}

void	print_arg_list(t_node *args)
{
	t_node	*ptr;

	ptr = args;
	while (ptr)
	{
		ft_printf("arg:{%s}Type: %s\n", ptr->data,
			convert_type(ptr->type));
		ptr = ptr->next;
	}
}

void	print_env_list(t_env *env_list)
{
	t_env	*ptr;

	ptr = env_list;
	while (ptr)
	{
		ft_printf("ENVP Key:%s, Value:%s\n", ptr->k, ptr->v);
		ptr = ptr->next;
	}
}

void	print_shell(t_shell *shell)
{
	t_shell	*ptr;
	int		i;

	i = 0;
	ptr = shell;
	while (ptr)
	{
		if (ptr->args)
			print_arg_list(ptr->args);
		if (ptr->env_list)
			print_env_list(ptr->env_list);
		ptr = ptr->next;
	}
}
