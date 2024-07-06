/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:58:42 by lteng             #+#    #+#             */
/*   Updated: 2024/06/27 22:00:38 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_minishell *shell)
{
	t_env	*current;

	current = shell->env;
	while (current)
	{
		printf("%s\n", current->env_line);
		current = current->next;
	}
}
