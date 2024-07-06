/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:12:59 by lteng             #+#    #+#             */
/*   Updated: 2024/06/28 13:04:05 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_init(char *envp[], t_minishell *shell)
{
	int		i;
	t_env	*curr;
	t_env	*new;

	i = 0;
	if (envp == NULL || shell == NULL)
		return (-1);
	curr = (t_env *)malloc(sizeof(t_env));
	if (!curr)
		return (-1);
	curr->env_line = ft_strdup(envp[i]);
	curr->next = NULL;
	shell->env = curr;
	i++;
	while (envp[i])
	{
		new = (t_env *)malloc(sizeof(t_env));
		if (!new)
			return (-1);
		new->env_line = ft_strdup(envp[i++]);
		new->next = NULL;
		curr->next = new;
		curr = new;
	}
	return (0);
}

void	free_env(t_minishell *shell)
{
	t_env	*current;
	t_env	*next;

	current = shell->env;
	while (current != NULL)
	{
		next = current->next;
		free(current->env_line);
		free(current);
		current = next;
	}
	shell->env = NULL;
}
