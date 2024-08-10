/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:53:07 by lteng             #+#    #+#             */
/*   Updated: 2024/08/07 22:30:19 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_no_arg(t_shell *shell)
{
	t_env	*sorted_env;
	t_env	*current;

	sorted_env = sort_env_alpha(shell->env_list);
	current = sorted_env;
	while (current)
	{
		if (current->k[0] != '_')
			printf("%s%s=%s\n", "declare -x ", current->k, current->v);
		current = current->next;
	}
}

int	check_key(char *arg)
{
	int	i;

	i = 0;
	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (1);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	check_keys(char **cmd)
{
	int		i;
	char	*key;
	char	*value;
	int		result;

	result = 0;
	i = 1;
	while (cmd[i])
	{
		key = extract_key(cmd[i]);
		value = extract_value(cmd[i]);
		if (!key || !value || check_key(key) != 0)
		{
			free(key);
			free(value);
			result = 1;
			ft_putstr_fd(INV_IDEN, 2);
			break ;
		}
		free(key);
		free(value);
		i++;
	}
	return (result);
}

int	ft_export(char **cmd, t_shell *shell)
{
	int		i;
	char	*key;
	char	*value;
	int		result;

	result = 0;
	i = 1;
	if (!cmd[1])
		return (export_no_arg(shell), result);
	if (check_keys(cmd) == 1)
		result = 1;
	while (cmd[i++])
	{
		key = extract_key(cmd[i]);
		value = extract_value(cmd[i]);
		if (!key || !value)
			return (free(key), free(value), 1);
		if (check_key(key) == 0)
			shell->env_list = add_env_node(shell->env_list, key, value);
		else
			result = 0;
		free(key);
		free(value);
	}
	return (result);
}
