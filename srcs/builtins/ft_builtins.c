/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:12:25 by jolai             #+#    #+#             */
/*   Updated: 2024/07/27 21:14:11 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *name)
{
	if (ft_strcmp(name, "export") == 0 || ft_strcmp(name, "unset") == 0
		|| ft_strcmp(name, "echo") == 0 || ft_strcmp(name, "exit") == 0
		|| ft_strcmp(name, "pwd") == 0 || ft_strcmp(name, "env") == 0
		|| ft_strcmp(name, "cd") == 0)
		return (1);
	else
		return (0);
}

int	run_builtin(t_shell *shell)
{
	char	**cmd;
	int		status;

	cmd = arg_list_to_array(shell->args);
	if (ft_strcmp(cmd[0], "exit") == 0)
		status = ft_exit(cmd, shell);
	else if (ft_strcmp(cmd[0], "env") == 0)
		status = ft_env(shell);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		status = ft_pwd(shell);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		status = ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		status = ft_cd(cmd, shell);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		status = ft_unset(cmd, shell);
	else if (ft_strcmp(cmd[0], "export") == 0)
		status = ft_export(cmd, shell);
	else
		status = 127;
	free_2d_c(cmd);
	return (status);
}
