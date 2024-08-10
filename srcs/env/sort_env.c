/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:39:21 by jolai             #+#    #+#             */
/*   Updated: 2024/07/22 22:39:22 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*sort_env_alpha(t_env *env)
{
	t_env	*ptr;
	t_env	*temp;
	char	*temp_k;
	char	*temp_v;

	ptr = env;
	while (ptr)
	{
		temp = ptr->next;
		while (temp)
		{
			if (ft_strncmp(ptr->k, temp->k, ft_strlen(ptr->k)) > 0)
			{
				temp_k = ptr->k;
				temp_v = ptr->v;
				ptr->k = temp->k;
				ptr->v = temp->v;
				temp->k = temp_k;
				temp->v = temp_v;
			}
			temp = temp->next;
		}
		ptr = ptr->next;
	}
	return (env);
}
