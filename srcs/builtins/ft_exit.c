/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 00:26:03 by lteng             #+#    #+#             */
/*   Updated: 2024/08/07 19:42:42 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	handle_exit(char **cmd)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd(MANY_ARGS, 2);
		exit_status = 1;
	}
	if (i == 2)
	{
		if (check_numeric(cmd[1]) == 0)
			exit_status = ft_atoi(cmd[1]) % 256;
		else
		{
			ft_putstr_fd(NUM_ARG, 2);
			exit_status = 2;
		}
	}
	return (exit_status);
}

int	ft_exit(char **cmd, t_shell *shell)
{
	int	exit_status;

	exit_status = handle_exit(cmd);
	printf("exit\n");
	free_2d_c(cmd);
	free_shell(shell);
	exit(exit_status);
}
