/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:51:15 by lteng             #+#    #+#             */
/*   Updated: 2024/07/31 18:34:37 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_options(char **cmd, int *newline)
{
	int	i;
	int	j;

	i = 1;
	*newline = 1;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		j = 2;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] == '\0')
		{
			*newline = 0;
			i++;
		}
		else
			break ;
	}
	return (i);
}

void	print_args(char **cmd, int start_index, int newline)
{
	if (cmd[start_index])
		ft_putstr_fd(cmd[start_index++], STDOUT_FILENO);
	while (cmd[start_index])
	{
		ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(cmd[start_index++], STDOUT_FILENO);
	}
	if (newline == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	newline;

	newline = 1;
	i = parse_options(cmd, &newline);
	print_args(cmd, i, newline);
	return (0);
}
