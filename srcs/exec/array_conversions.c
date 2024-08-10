/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_conversions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:46:49 by jolai             #+#    #+#             */
/*   Updated: 2024/07/08 19:48:15 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_list_size(t_node *arg_list)
{
	t_node	*ptr;
	int		count;

	count = 0;
	if (arg_list)
	{
		ptr = arg_list;
		while (ptr)
		{
			count++;
			ptr = ptr->next;
		}
		return (count);
	}
	else
		return (0);
}

int	env_list_size(t_env *env_list)
{
	t_env	*ptr;
	int		count;

	count = 0;
	if (env_list)
	{
		ptr = env_list;
		while (ptr)
		{
			count++;
			ptr = ptr->next;
		}
		return (count);
	}
	else
		return (0);
}

char	**arg_list_to_array(t_node *arg_list)
{
	char	**array;
	t_node	*ptr;
	int		i;

	ptr = arg_list;
	if (!ptr)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (arg_list_size(ptr) + 1));
	i = 0;
	while (ptr)
	{
		array[i] = ft_strdup(ptr->data);
		ptr = ptr->next;
		i++;
	}
	array[i] = 0;
	return (array);
}

char	**env_to_array(t_env *env_list)
{
	char	**array;
	char	*temp;
	t_env	*ptr;
	int		i;

	ptr = env_list;
	if (!ptr)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (env_list_size(ptr) + 1));
	i = 0;
	while (ptr)
	{
		temp = ft_strjoin(ptr->k, "=");
		array[i] = ft_strjoin(temp, ptr->v);
		free (temp);
		ptr = ptr->next;
		i++;
	}
	array[i] = 0;
	return (array);
}
