/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:16:17 by lteng             #+#    #+#             */
/*   Updated: 2024/07/27 20:42:37 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_key(char *arg, t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (ft_strcmp(arg, temp->k) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	ft_unset(char **cmd, t_shell *shell)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (find_key(cmd[i], shell->env_list) == 1)
			shell->env_list = del_env_node(shell->env_list, cmd[i]);
		i++;
	}
	return (0);
}
