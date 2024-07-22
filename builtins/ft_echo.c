/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:22:07 by lteng             #+#    #+#             */
/*   Updated: 2024/07/22 23:12:31 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_minishell *shell)
{
	t_token	*current_token;
	int		i;

	i = 0;
	current_token = shell->tokens->next;
	if (!current_token)
	{
		printf("\n");
		return ;
	}
	while (ft_strncmp(current_token->value, "-n", 2) == 0)
	{
		current_token = current_token->next;
		i = 1;
	}
	while (current_token)
	{
		printf("%s ", current_token->value);
		current_token = current_token->next;
	}
	if (i == 0)
		printf("\n");
}
