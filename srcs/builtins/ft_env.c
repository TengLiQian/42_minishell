/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 00:13:01 by lteng             #+#    #+#             */
/*   Updated: 2024/08/06 19:09:32 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key(char *arg)
{
	char	*key;
	int		i;

	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_substr(arg, 0, i);
	return (key);
}

char	*extract_value(char *arg)
{
	char	*value;
	int		i;
	int		length;

	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
		i++;
	length = ft_strlen(arg) - i;
	value = ft_substr(arg, i, length);
	return (value);
}

int	ft_env(t_shell *shell)
{
	t_env	*current;

	current = shell->env_list;
	if (!current)
		return (1);
	while (current)
	{
		printf("%s=%s\n", current->k, current->v);
		current = current->next;
	}
	return (0);
}
