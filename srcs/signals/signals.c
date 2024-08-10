/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:16:40 by jolai             #+#    #+#             */
/*   Updated: 2024/07/17 20:40:09 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//SIGINT	= CTRL + 'C'
//SIGQUIT	= CTRL + '\'

static void	redisplay_sig(int sig)
{
	rl_replace_line("", 0);
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_redisplay();
	g_sig_num = 128 + sig;
}

void	main_sig_handler(void)
{
	g_sig_num = 0;
	signal(SIGINT, redisplay_sig);
	signal(SIGQUIT, SIG_IGN);
}

void	exec_child_sig(void)
{
	g_sig_num = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
