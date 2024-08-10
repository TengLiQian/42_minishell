/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_initial.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:38:39 by jolai             #+#    #+#             */
/*   Updated: 2024/07/27 21:22:57 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*make_env(void)
{
	t_env	*env_list;

	env_list = NULL;
	env_list = add_env_node(env_list, "PWD", getcwd(NULL, 0));
	env_list = add_env_node(env_list, "SHLVL", "1");
	env_list = add_env_node(env_list, "_", "lastcommand");
	return (env_list);
}

t_env	*update_shlvl(t_env *env_list)
{
	int		lvl;
	char	*temp;

	if (get_env_val(env_list, "SHLVL"))
	{
		lvl = ft_atoi(get_env_val(env_list, "SHLVL"));
		lvl++;
		temp = ft_itoa(lvl);
		env_list = update_env_val(env_list, "SHLVL", temp);
		free(temp);
	}
	else
		env_list = add_env_node(env_list, "SHLVL", "1");
	return (env_list);
}

t_env	*initialize_env(char **env)
{
	t_env	*env_list;
	char	**temp;
	int		i;

	i = 0;
	if (!env || !env[0])
		return (make_env());
	env_list = NULL;
	while (env[i])
	{
		temp = ft_split(env[i], '=');
		env_list = add_env_node(env_list, temp[0], temp[1]);
		free_2d_c(temp);
		i++;
	}
	env_list = update_shlvl(env_list);
	if (!get_env_key(env_list, "_"))
		env_list = add_env_node(env_list, "_", "lastcommand");
	return (env_list);
}
