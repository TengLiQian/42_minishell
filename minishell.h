/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:13:56 by lteng             #+#    #+#             */
/*   Updated: 2024/07/15 12:17:11 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define BC "\001\033[1;36m\002" // Bold Cyan
# define RST "\001\033[0m\002"   // Reset color

# define EMPTY 0
# define COMMAND 1
# define ARGUMENT 2
#

// Global Variable
static int			g_exit_status = 0;

typedef enum e_token_type
{
	T_STRING,  // "XXX"
	T_REDIR_L, // <
	T_REDIR_R, // >
	T_HEREDOC, // <<
	T_APPEND,  // >>
	T_BRAC_L,  // (
	T_BRAC_R,  // )
	T_PIPE,    // |
}					t_token_type;

// token struct
typedef struct s_token
{
	t_token_type	token_type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

// lexer struct

typedef struct s_lexer
{
	char			*content;
	int				index;
	char			c;
}					t_lexer;

// env struct

typedef struct s_env
{
	char			*env_line;
	struct s_env	*next;
}					t_env;

// minishell struct

typedef struct s_minishell
{
	t_env			*env;
	char			*input;
	t_token			*tokens;

}					t_minishell;

// lexer

int					is_space(char c);
t_token_type		get_token(char *token, int len);
t_token				*token_init(int type, char *value);
void				add_token(t_token **list, t_token *new);
t_token 			*tokenize(t_minishell *shell, char *input);
char				**lexer_split(char const *s);
int					lexer_wordlen(char const *s);
void				*lexer_free(char **strs);
int					lexer_wordcount(char const *s);

// signals
void				new_prompt(int sig);

// env
int					env_init(char *envp[], t_minishell *shell);
void				free_env(t_minishell *shell);
char				*get_env_value(char *name, t_minishell *shell);

// builtins
void				main_builtin(char *str, t_minishell *shell);
void				ft_env(t_minishell *shell);
void				ft_exit(t_minishell *shell);
void				ft_pwd(char *name, t_minishell *shell);

#endif
