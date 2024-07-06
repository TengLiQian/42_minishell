/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:00:20 by lteng             #+#    #+#             */
/*   Updated: 2024/06/28 16:46:06 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	main_builtin(char *str, t_minishell *shell)
{
	if (ft_strncmp(str, "env", 3) == 0)
		ft_env(shell);
	if (ft_strncmp(str, "exit", 3) == 0)
		ft_exit(shell);
	if (ft_strncmp(str, "pwd", 3) == 0)
		ft_pwd("_", shell);
}
