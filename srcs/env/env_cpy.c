/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:38:27 by jolai             #+#    #+#             */
/*   Updated: 2024/07/22 22:38:30 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_cpy(t_env *env)
{
	t_env	*cpy;
	t_env	*ptr;

	cpy = NULL;
	ptr = env;
	while (ptr)
	{
		cpy = add_env_node(cpy, ptr->k, ptr->v);
		ptr = ptr->next;
	}
	return (cpy);
}
