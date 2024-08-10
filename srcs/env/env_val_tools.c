/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_val_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:39:00 by jolai             #+#    #+#             */
/*   Updated: 2024/07/22 22:39:08 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_key(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->k, key) == 0)
			return (env->k);
		env = env->next;
	}
	return (NULL);
}

char	*get_env_val(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->k, key) == 0)
			return (env->v);
		env = env->next;
	}
	return (NULL);
}

t_env	*update_env_val(t_env *env, char *key, char *value)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (ft_strcmp(ptr->k, key) == 0)
		{
			free(ptr->v);
			if (value == NULL)
				ptr->v = NULL;
			else
				ptr->v = ft_strdup(value);
			return (env);
		}
		ptr = ptr->next;
	}
	return (env);
}
