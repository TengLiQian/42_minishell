/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenising.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:50:44 by jolai             #+#    #+#             */
/*   Updated: 2024/07/18 17:11:36 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*process_args(t_shell *shell)
{
	t_node	*ptr;

	if (!(shell->args))
		return (shell);
	ptr = shell->args;
	while (ptr->prev != NULL)
		ptr = ptr->prev;
	shell->args = process_quotes(ptr);
	shell->args = heredoc_checker(shell->args);
	shell = expand_env_var(shell);
	shell->exit_status = 0;
	if (!syntax_check(shell->args))
	{
		shell = reset_shell(shell);
		shell->exit_status = 2;
		return (shell);
	}
	shell->args = remove_quotes(shell->args);
	shell->args = combine_args(shell->args);
	shell->args = remove_spaces(shell->args);
	shell->args = convert_to_args(shell->args);
	return (shell);
}

t_node	*assign_redir(t_node *arg_list, char *data, int i)
{
	if (ft_strncmp(&data[i], "<<", 2) == 0)
		arg_list = add_arg_node(arg_list, data, HEREDOC);
	else if (ft_strncmp(&data[i], ">>", 2) == 0)
		arg_list = add_arg_node(arg_list, data, REDIR_APPEND);
	else if (data[i] == '<')
		arg_list = add_arg_node(arg_list, data, REDIR_IN);
	else if (data[i] == '>')
		arg_list = add_arg_node(arg_list, data, REDIR_OUT);
	return (arg_list);
}

t_node	*assign_operator(t_node *arg_list, char *data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] == '<' || data[i] == '>')
			arg_list = assign_redir(arg_list, data, i);
		else if (data[i] == '\'')
			arg_list = add_arg_node(arg_list, data, QUOTE);
		else if (data[i] == '\"')
			arg_list = add_arg_node(arg_list, data, DBLQUOTE);
		else if (data[i] == '|')
			arg_list = add_arg_node(arg_list, data, PIPE);
		else if (data[i] == '$')
			arg_list = add_arg_node(arg_list, data, ENV_VAR);
		if (ft_is_operator(data[i]) == 1 && data[i] != ' ')
			break ;
		i++;
		if (!data[i])
			arg_list = add_arg_node(arg_list, data, SPACES);
	}
	return (arg_list);
}

t_shell	*make_arg_list(char **split_arg, t_shell *shell)
{
	int		i;
	t_node	*arg_list;

	i = 0;
	arg_list = NULL;
	while (split_arg[i])
	{
		if (split_arg[i][0] && ft_is_operator(split_arg[i][0]) == 1
			&& split_arg[i][0] != '?')
			arg_list = assign_operator(arg_list, split_arg[i]);
		else
			arg_list = add_arg_node(arg_list, split_arg[i], CMD);
		i++;
	}
	shell->args = arg_list;
	shell = process_args(shell);
	return (shell);
}
