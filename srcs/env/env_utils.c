/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:38:48 by jolai             #+#    #+#             */
/*   Updated: 2024/07/22 22:38:50 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Check if k already exists, if k already exists, update v instead
Else
Add a new node
*/
t_env	*add_env_node(t_env *env, char *k, char *v)
{
	t_env	*new;
	t_env	*ptr;

	if (get_env_key(env, k))
	{
		env = update_env_val(env, k, v);
		return (env);
	}
	new = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	if (k)
		new->k = ft_strdup(k);
	if (v)
		new->v = ft_strdup(v);
	new->next = NULL;
	if (!env)
		return (new);
	ptr = env;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	return (env);
}

t_env	*del_env_node(t_env *env, char *k)
{
	t_env	*ptr;
	t_env	*prev;

	ptr = env;
	prev = NULL;
	while (ptr)
	{
		if (ft_strcmp(ptr->k, k) == 0)
		{
			if (prev)
				prev->next = ptr->next;
			else
				env = ptr->next;
			free(ptr->k);
			free(ptr->v);
			free(ptr);
			return (env);
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return (env);
}

void	free_env(t_env *env_list)
{
	t_env	*ptr;

	while (env_list)
	{
		ptr = env_list;
		free(ptr->k);
		free(ptr->v);
		env_list = ptr->next;
		free(ptr);
	}
	free(env_list);
	env_list = NULL;
}
