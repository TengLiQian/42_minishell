/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:41:25 by lteng             #+#    #+#             */
/*   Updated: 2024/07/27 13:45:47 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell)
{
	t_env	*curr;
	char	*k;
	char	*v;

	if (!shell || !shell->env_list)
		return (1);
	curr = shell->env_list;
	while (curr)
	{
		k = curr->k;
		v = curr->v;
		if (ft_strcmp("PWD", k) == 0)
		{
			printf("%s\n", v);
			return (0);
		}
		curr = curr->next;
	}
	return (1);
}
