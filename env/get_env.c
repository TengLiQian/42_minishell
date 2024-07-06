/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:47:05 by lteng             #+#    #+#             */
/*   Updated: 2024/06/28 13:04:34 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char *name, t_minishell *shell)
{
	int		name_len;
	char	*equal_pos;
	t_env	*curr;

	name_len = ft_strlen(name);
	curr = shell->env;
	while (curr)
	{
		if (ft_strncmp(name, curr->env_line, name_len) == 0)
		{
			equal_pos = ft_strchr(curr->env_line, '=');
			return (equal_pos + 1);
		}
		curr = curr->next;
	}
	return (NULL);
}
