/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:19:22 by jolai             #+#    #+#             */
/*   Updated: 2024/08/07 17:17:28 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_separator(t_node *arg_list, t_shell *shell)
{
	t_node	*ptr;
	t_shell	*s_ptr;

	ptr = arg_list;
	s_ptr = shell;
	while (ptr)
	{
		if (ptr->type == PIPE)
		{
			ptr->prev->next = NULL;
			ptr->prev = NULL;
			s_ptr->next = copy_shell_node(ptr->next, shell);
			s_ptr = s_ptr->next;
			arg_list = ptr->next;
			arg_list->prev = NULL;
			ptr->next = NULL;
			free_arg_list(ptr);
			ptr = arg_list;
			continue ;
		}
		ptr = ptr->next;
	}
}

void	child_handler(t_shell *start, t_shell *shell, int *fd)
{
	t_shell	*ptr;

	ptr = start;
	while (ptr != shell)
	{
		start = ptr->next;
		free_shell_node(ptr);
		ptr = start;
	}
	if (shell->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close (fd[0]);
		free_shell(shell->next);
		shell->next = NULL;
	}
	exec_handler(shell, 0);
}

pid_t	fork_handler(t_shell *start, t_shell *shell)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (shell->next && pipe(fd) == -1)
		perror("|");
	pid = fork();
	if (pid == -1)
		perror("Fork");
	if (pid == 0)
	{
		rl_clear_history();
		child_handler(start, shell, fd);
		status = shell->exit_status;
		free_shell(shell);
		exit(status);
	}
	if (shell->next)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	return (pid);
}

void	process_handler(t_shell *shell)
{
	t_shell	*ptr;

	ptr = shell;
	while (ptr)
	{
		ptr->pid = fork_handler(shell, ptr);
		ptr = ptr->next;
	}
	dup2(shell->stdio[0], STDIN_FILENO);
	signal(SIGINT, SIG_IGN);
	ptr = shell;
	while (ptr)
	{
		ptr->exit_status = wait_status(ptr->pid, 0);
		if (ptr->exit_status > 128 && g_sig_num != ptr->exit_status)
		{
			g_sig_num = ptr->exit_status;
			if (ptr->exit_status == 130)
				ft_putstr_fd("\n", STDERR_FILENO);
			else if (ptr->exit_status == 131)
				ft_putstr_fd("Quit\n", STDERR_FILENO);
		}
		ptr = ptr->next;
	}
}
