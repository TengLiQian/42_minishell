/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:19:22 by jolai             #+#    #+#             */
/*   Updated: 2024/07/08 16:37:48 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell_node(t_shell *ptr)
{
	if (ptr->args)
		free_arg_list(ptr->args);
	if (ptr->env_list)
		free_env(ptr->env_list);
	ptr->next = NULL;
	close (ptr->stdio[0]);
	close (ptr->stdio[1]);
	if (ptr->heredoc_fd != 0)
		close(ptr->heredoc_fd);
	free (ptr);
}

void	free_shell(t_shell *shell)
{
	t_shell	*ptr;

	ptr = shell;
	while (ptr)
	{
		shell = ptr->next;
		free_shell_node(ptr);
		ptr = shell;
	}
}

t_shell	*new_shell_node(int in_fd, int out_fd)
{
	t_shell	*new;

	new = (t_shell *)ft_calloc(sizeof(t_shell), 1);
	new->stdio[0] = dup(in_fd);
	new->stdio[1] = dup(out_fd);
	return (new);
}

t_shell	*copy_shell_node(t_node *arg_list, t_shell *shell)
{
	t_shell	*new;

	new = new_shell_node(shell->stdio[0], shell->stdio[1]);
	new->args = arg_list;
	new->env_list = env_cpy(shell->env_list);
	return (new);
}
