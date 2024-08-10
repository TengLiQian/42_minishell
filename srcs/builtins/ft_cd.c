/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:03:16 by lteng             #+#    #+#             */
/*   Updated: 2024/08/07 19:33:03 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(t_shell *shell, char *key)
{
	t_env	*curr;
	char	*k;
	char	*v;

	if (!shell || !shell->env_list)
		return (NULL);
	curr = shell->env_list;
	while (curr)
	{
		k = curr->k;
		v = curr->v;
		if (ft_strcmp(key, k) == 0)
			return (ft_strdup(v));
		curr = curr->next;
	}
	return (NULL);
}

int	change_directory(char **cmd, char *home_dir, char *old_pwd)
{
	if (ft_strcmp(cmd[1], "-") == 0)
	{
		if (!old_pwd || chdir(old_pwd) == -1)
			return (-1);
	}
	else if (ft_strcmp(cmd[1], "~") == 0)
	{
		if (!home_dir || chdir(home_dir) == -1)
			return (-1);
	}
	else if (chdir(cmd[1]) == -1)
		return (-1);
	return (0);
}

int	update_env_vars(t_shell *shell, char *curr_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (-1);
	shell->env_list = add_env_node(shell->env_list, "OLDPWD", curr_pwd);
	shell->env_list = add_env_node(shell->env_list, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

int	ft_cd(char **cmd, t_shell *shell)
{
	int		i;
	char	*curr_pwd;
	char	*old_pwd;
	char	*home_dir;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
		return (ft_putstr_fd(MANY_ARGS, 2), 1);
	curr_pwd = get_pwd(shell, "PWD");
	home_dir = get_pwd(shell, "HOME");
	old_pwd = get_pwd(shell, "OLDPWD");
	if (i == 1)
	{
		if (!home_dir || chdir(home_dir) == -1)
			return (free(curr_pwd), free(home_dir), free(old_pwd), 1);
	}
	else if (change_directory(cmd, home_dir, old_pwd) == -1)
		return (ft_putstr_fd(NO_FD, 2), free(curr_pwd), free(home_dir),
			free(old_pwd), 1);
	if (update_env_vars(shell, curr_pwd) == -1)
		return (free(curr_pwd), free(home_dir), free(old_pwd), 1);
	return (free(curr_pwd), free(home_dir), free(old_pwd), 0);
}
