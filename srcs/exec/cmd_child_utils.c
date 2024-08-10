/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_child_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:23:46 by jolai             #+#    #+#             */
/*   Updated: 2024/08/07 18:18:41 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_cmd(char **path, char *cmd_exec)
{
	int		i;
	char	*cmd_path;

	i = 0;
	cmd_path = NULL;
	if (!path)
		return (NULL);
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], cmd_exec);
		if (access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	return (cmd_path);
}

char	*path_finder(char *cmd, char **env)
{
	char	**path;
	char	*cmd_path;
	char	*cmd_exec;
	int		i;

	i = 0;
	if (!env || !(*env))
		return (NULL);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (env[i])
		path = ft_split(env[i] + 5, ':');
	else
		path = NULL;
	cmd_exec = ft_strjoin("/", cmd);
	i = 0;
	cmd_path = find_cmd(path, cmd_exec);
	if (!cmd_path && access(cmd, X_OK) == 0)
		cmd_path = ft_strdup(cmd);
	free(cmd_exec);
	free_2d_c(path);
	path = NULL;
	return (cmd_path);
}

void	cmd_executer(char **cmd, char **env)
{
	char	*cmd_path;

	cmd_path = path_finder(cmd[0], env);
	if (cmd_path)
		execve(cmd_path, cmd, env);
	if (cmd[0])
		ft_putstr_fd(cmd[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	if (cmd)
		free_2d_c(cmd);
	if (env)
		free_2d_c(env);
	if (cmd_path)
		free (cmd_path);
	exit (127);
}
