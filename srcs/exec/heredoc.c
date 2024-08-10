/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:51:17 by jolai             #+#    #+#             */
/*   Updated: 2024/08/07 17:17:01 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_handler(char *eof, int expand, t_shell *shell, t_shell *first)
{
	int		fd[2];
	pid_t	pid;
	char	*input;

	input = NULL;
	if (pipe(fd) == -1)
		perror("Heredoc pipe");
	pid = fork();
	if (pid == -1)
		perror("Heredoc fork");
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(fd[0]);
		heredoc_input(eof, expand, shell->env_list, fd[1]);
		close(fd[1]);
		free_shell(first);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	shell->exit_status = wait_status(pid, 1);
	close(fd[1]);
	return (fd[0]);
}

void	heredoc_runner(t_shell *shell)
{
	t_shell	*shell_ptr;
	t_node	*arg_ptr;

	shell_ptr = shell;
	while (shell_ptr && g_sig_num == 0)
	{
		arg_ptr = shell_ptr->args;
		while (arg_ptr && g_sig_num == 0)
		{
			if (arg_ptr->type == HEREDOC)
			{
				if (shell_ptr->heredoc_fd != 0)
					close(shell_ptr->heredoc_fd);
				if (arg_ptr->next && (arg_ptr->next->type == ARG
						|| arg_ptr->next->type == CMD))
				{
					shell_ptr->heredoc_fd = heredoc_handler(arg_ptr->next->data,
							arg_ptr->heredoc_expand, shell_ptr, shell);
					arg_ptr = arg_ptr->next;
				}
			}
			arg_ptr = arg_ptr->next;
		}
		shell_ptr = shell_ptr->next;
	}
}
