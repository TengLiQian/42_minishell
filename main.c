/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:14:18 by lteng             #+#    #+#             */
/*   Updated: 2024/07/15 12:17:26 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	*shell;

	(void)argc;
	(void)argv;
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	shell = malloc(sizeof(t_minishell));
	if (!shell)
		return (-1);
	env_init(envp, shell);
	while (1)
	{
		shell->input = readline(BC "Minishell: Enter Command >> " RST);
		if (!shell->input)
		{
			printf("exit\n");
			break ;
		}
		add_history(shell->input);
		main_builtin(shell->input, shell);
	}
	free(shell->input);
	clear_history();
	return (0);
}
/*
int	main(void)
{
	int i = 0;
	char **strings;

	strings = lexer_split("Hello World HAHAHAHA ");
	while (strings[i])
	{
		printf("%s\n", strings[i]);
		i++;
	}
	return (0);
}*/
