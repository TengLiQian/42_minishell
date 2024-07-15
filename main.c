/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:14:18 by lteng             #+#    #+#             */
/*   Updated: 2024/07/15 22:50:03 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	massive_free(t_minishell *shell)
{
	free(shell->input);
	free_env(shell);
	free_tokens(shell->tokens);
	free(shell);
}

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
		shell->tokens = tokenize(shell->input);
		main_builtin(shell->input, shell);
	}
	massive_free(shell);
	clear_history();
	return (0);
}

/*
int	main(void)
{
	int		i;
	char	**strings;

	i = 0;
	strings = lexer_split("Hello World HAHAHAHA ");
	while (strings[i])
	{
		printf("%s\n", strings[i]);
		i++;
	}
	lexer_free(strings);
	return (0);
}*/
/*
while (shell->tokens)
{
	printf("Value: %s\n", shell->tokens->value);
	printf("Token Type: %u\n", shell->tokens->token_type);
	shell->tokens = shell->tokens->next;
}
*/
/*
valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell
*/