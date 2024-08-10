/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:00:05 by jolai             #+#    #+#             */
/*   Updated: 2024/07/28 16:54:10 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_handler(t_node *ptr, t_node *next, int fd, t_shell *shell)
{
	if (fd != 0)
		close(fd);
	if (ptr->type == REDIR_IN)
		fd = open(next->data, O_RDONLY);
	else if (ptr->type == HEREDOC)
		fd = shell->heredoc_fd;
	else if (ptr->type == REDIR_OUT)
		fd = open(next->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (ptr->type == REDIR_APPEND)
		fd = open(next->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd != -1 && (ptr->type == REDIR_IN || ptr->type == HEREDOC))
		dup2(fd, STDIN_FILENO);
	else if (fd != -1 && (ptr->type == REDIR_OUT || ptr->type == REDIR_APPEND))
		dup2(fd, STDOUT_FILENO);
	if (fd == -1)
	{
		perror(next->data);
		shell->exit_status = 1;
	}
	else
		close(fd);
	return (fd);
}

t_shell	*redir_checker(t_shell *shell, int *fd_in, int *fd_out)
{
	t_node	*ptr;

	ptr = shell->args;
	while (ptr)
	{
		if (ptr->type == REDIR_IN || ptr->type == HEREDOC
			|| ptr->type == REDIR_OUT || ptr->type == REDIR_APPEND)
		{
			if (ptr->next && (ptr->next->type == ARG || ptr->next->type == CMD))
			{
				if (ptr->type == REDIR_IN || ptr->type == HEREDOC)
					*fd_in = redir_handler(ptr, ptr->next, *fd_in, shell);
				else if (ptr->type == REDIR_OUT || ptr->type == REDIR_APPEND)
					*fd_out = redir_handler(ptr, ptr->next, *fd_out, shell);
				shell->args = del_arg_node(ptr->next);
			}
			shell->args = del_arg_node(ptr);
			ptr = shell->args;
		}
		else
			ptr = ptr->next;
		if (shell->exit_status == 1)
			break ;
	}
	return (shell);
}
