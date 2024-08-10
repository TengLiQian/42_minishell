/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:45:07 by jolai             #+#    #+#             */
/*   Updated: 2024/07/22 22:45:10 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_status(pid_t pid, int sig_msg)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		status = 128 + WTERMSIG(status);
		if (g_sig_num != status)
		{
			g_sig_num = status;
			if (status == 130 && sig_msg == 1)
				ft_putstr_fd("\n", STDERR_FILENO);
			else if (status == 131 && sig_msg == 1)
				ft_putstr_fd("Quit\n", STDERR_FILENO);
		}
	}
	else
		status = WEXITSTATUS(status);
	return (status);
}

int	run_cmd(t_shell *shell, int sig_msg)
{
	char	**cmd;
	char	**env;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		exec_child_sig();
		cmd = arg_list_to_array(shell->args);
		env = env_to_array(shell->env_list);
		free_shell(shell);
		cmd_executer(cmd, env);
	}
	if (shell->heredoc_fd != 0)
	{
		close(shell->heredoc_fd);
		shell->heredoc_fd = 0;
	}
	signal(SIGINT, SIG_IGN);
	return (wait_status(pid, sig_msg));
}

int	cmd_or_builtin_handler(t_shell *shell, int sig_msg)
{
	char	*cmd_path;
	char	**env;

	env = env_to_array(shell->env_list);
	cmd_path = path_finder(shell->args->data, env);
	if (!cmd_path)
		cmd_path = ft_strdup(shell->args->data);
	update_env_val(shell->env_list, "_", cmd_path);
	free_2d_c(env);
	free(cmd_path);
	if (is_builtin(shell->args->data) == 1)
		return (run_builtin(shell));
	else
		return (run_cmd(shell, sig_msg));
}

void	exec_handler(t_shell *shell, int sig_msg)
{
	int		file[2];

	file[0] = 0;
	file[1] = 0;
	shell = redir_checker(shell, &file[0], &file[1]);
	if (shell->args && shell->exit_status != 1)
		shell->exit_status = cmd_or_builtin_handler(shell, sig_msg);
	if (file[0] > 2)
		close(file[0]);
	if (file[1] > 2)
		close(file[1]);
	if (shell->heredoc_fd != 0)
	{
		close(shell->heredoc_fd);
		shell->heredoc_fd = 0;
	}
}
