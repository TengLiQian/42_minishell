/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:28:49 by jolai             #+#    #+#             */
/*   Updated: 2024/08/07 19:16:20 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig_num = 0;

t_shell	*reset_shell(t_shell *shell)
{
	t_shell	*ptr;

	free_arg_list(shell->args);
	shell->args = NULL;
	if (shell->next)
	{
		ptr = shell;
		while (ptr)
		{
			shell->exit_status = ptr->exit_status;
			ptr = ptr->next;
		}
		free_shell(shell->next);
		shell->next = NULL;
	}
	if (STDIN_FILENO != shell->stdio[0])
		dup2(shell->stdio[0], STDIN_FILENO);
	if (STDOUT_FILENO != shell->stdio[1])
		dup2(shell->stdio[1], STDOUT_FILENO);
	if (shell->heredoc_fd != 0)
	{
		close(shell->heredoc_fd);
		shell->heredoc_fd = 0;
	}
	return (shell);
}

t_shell	*input_processing(char *input, t_shell *shell)
{
	char	**arr;

	add_history(input);
	arr = arg_split(input);
	shell = make_arg_list(arr, shell);
	free_2d_c(arr);
	return (shell);
}

t_shell	*input_prompt(t_shell *shell)
{
	char	*input;
	int		status;

	input = NULL;
	while (!input)
	{
		input = readline("\001\033[0;36m\002MiniJell\001\033[0m\002>");
		if (g_sig_num != 0)
			shell->exit_status = g_sig_num;
		status = shell->exit_status;
		if (!input)
			free_shell(shell);
		if (!input)
			exit(status);
		if (ft_strlen(input) == 0)
		{
			free(input);
			input = NULL;
		}
	}
	g_sig_num = 0;
	shell = input_processing(input, shell);
	free(input);
	input = NULL;
	return (shell);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*envp;
	char	*prompt;
	int		status;

	envp = new_shell_node(STDIN_FILENO, STDOUT_FILENO);
	envp->env_list = initialize_env(env);
	prompt = NULL;
	while (ac && av)
	{
		main_sig_handler();
		status = envp->exit_status;
		envp = input_prompt(envp);
		if (!envp)
			break ;
		if (!(envp->args) || envp->exit_status == 2)
			continue ;
		pipe_separator(envp->args, envp);
		heredoc_runner(envp);
		if (envp->args && envp->next && g_sig_num == 0)
			process_handler(envp);
		else if (g_sig_num == 0)
			exec_handler(envp, 1);
		envp = reset_shell(envp);
	}
	return (status);
}
