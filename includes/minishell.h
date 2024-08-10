/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:40:04 by jolai             #+#    #+#             */
/*   Updated: 2024/08/07 19:40:17 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <assert.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

// Error Messages
# define INV_IDEN " not a valid identifier\n"
# define NO_FD " No such file or directory\n"
# define NUM_ARG " numeric argument required\n"
# define MANY_ARGS " too many arguments\n"
# define BROKEN_PIPE "Broken Pipe\n"

/****************************************************
		type definitions
****************************************************/

extern int			g_sig_num;

typedef enum s_type
{
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	QUOTE,
	DBLQUOTE,
	ENV_VAR,
	CMD,
	ARG,
	SPACES
}					t_type;

typedef struct s_env
{
	struct s_env	*next;
	char			*k;
	char			*v;
}					t_env;

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prev;
	int				type;
	char			*data;
	int				heredoc_expand;
}					t_node;

typedef struct s_shell
{
	struct s_shell	*next;
	t_node			*args;
	t_env			*env_list;
	pid_t			pid;
	int				stdio[2];
	int				heredoc_fd;
	int				exit_status;
}					t_shell;

/****************************************************
		main
****************************************************/

// main.c
t_shell				*reset_shell(t_shell *shell);
t_shell				*input_prompt(t_shell *shell);

/****************************************************
		srcs/parser
****************************************************/

// parser_splitting.c
int					ft_is_operator(char c);
size_t				ft_count_args(const char *input);
size_t				ft_find_arg_end(const char *input, size_t start);
int					ft_assign_args(char **splitted, const char *input);
char				**arg_split(const char *input);

// parser_tokenising.c
t_shell				*process_args(t_shell *shell);
t_node				*assign_redir(t_node *arg_list, char *data, int i);
t_node				*assign_operator(t_node *arg_list, char *data);
t_shell				*make_arg_list(char **split_arg, t_shell *shell);

// parser_processing.c
t_node				*heredoc_eof_parser(t_node *arg_list, t_node *ptr_hd);
t_node				*heredoc_checker(t_node *arg_list);
t_node				*combine_args(t_node *arg_list);
t_node				*remove_spaces(t_node *arg_list);
t_node				*convert_to_args(t_node *arg_list);

// parser_expansion.c
t_node				*process_quotes(t_node *ptr);
t_node				*remove_quotes(t_node *arg_list);
t_node				*split_env_val(t_node *arg_list, t_node *ptr, char *val);
t_node				*insert_env_val(t_shell *shell, t_node *ptr, t_node *next);
t_shell				*expand_env_var(t_shell *shell);

// syntax_checks.c
void				print_syntax_error(char *token);
int					syntax_pipe_check(t_node *pipe_node, t_node *args);
int					syntax_redir_check(t_node *redir_node);
int					syntax_quote_check(t_node *args);
int					syntax_check(t_node *args);

// parser_list_utils.c
t_node				*new_arg_node(char *data, int type);
t_node				*add_arg_node(t_node *arg_list, char *data, int type);
t_node				*move_arg_node_back(t_node *arg_list, t_node *prev,
						t_node *next);
t_node				*del_arg_node(t_node *arg_list);
void				free_arg_list(t_node *arg_list);

/****************************************************
		srcs/env
****************************************************/

// env_utils.c
t_env				*add_env_node(t_env *env_list, char *k, char *v);
t_env				*del_env_node(t_env *env_list, char *k);
void				free_env(t_env *env_list);
// env_initial.c
t_env				*make_env(void);
t_env				*update_shlvl(t_env *env_list);
t_env				*initialize_env(char **env);
// env_val_tools.c
char				*get_env_key(t_env *env, char *key);
char				*get_env_val(t_env *env, char *key);
t_env				*update_env_val(t_env *env, char *key, char *value);
// sort_env.c
t_env				*sort_env_alpha(t_env *env);
// env_cpy.c
t_env				*env_cpy(t_env *env);

/****************************************************
		srcs/pipes
****************************************************/

// pipes.c
void				pipe_separator(t_node *arg_list, t_shell *shell);
void				child_handler(t_shell *start, t_shell *shell, int *fd);
pid_t				fork_handler(t_shell *start, t_shell *shell);
void				process_handler(t_shell *shell);

// shell_list_utils.c
void				free_shell_node(t_shell *ptr);
void				free_shell(t_shell *shell);
t_shell				*new_shell_node(int in_fd, int out_fd);
t_shell				*copy_shell_node(t_node *arg_list, t_shell *shell);

/****************************************************
		srcs/exec
****************************************************/

// cmd_utils.c
int					wait_status(pid_t pid, int sig_msg);
int					run_cmd(t_shell *shell, int sig_msg);
int					cmd_or_builtin_handler(t_shell *shell, int sig_msg);
void				exec_handler(t_shell *shell, int sig_msg);

// cmd_child_utils.c
char				*find_cmd(char **path, char *cmd_exec);
char				*path_finder(char *cmd, char **env);
void				cmd_executer(char **cmd, char **env);

// redir_utils.c
int					redir_handler(t_node *ptr, t_node *next, int fd,
						t_shell *shell);
t_shell				*redir_checker(t_shell *shell, int *fd_in, int *fd_out);

// heredoc.c
void				heredoc_output(char *input, int expand, t_env *env_list,
						int out_fd);
int					eof_checker(char *input, char *eof);
int					heredoc_handler(char *eof, int expand, t_shell *shell,
						t_shell *first);
void				heredoc_runner(t_shell *shell);

// heredoc_child.c
int					heredoc_env_output(char *key, int end, t_env *env_list,
						int out_fd);
void				heredoc_output(char *input, int expand, t_env *env_list,
						int out_fd);
int					eof_checker(char *input, char *eof);
void				heredoc_input(char *eof, int expand, t_env *env_list,
						int out_fd);

// array_conversions.c
int					arg_list_size(t_node *arg_list);
int					env_list_size(t_env *env_list);
char				**arg_list_to_array(t_node *arg_list);
char				**env_to_array(t_env *env_list);

/****************************************************
		srcs/builtins
****************************************************/

// ft_builtins.c
int					is_builtin(char *name);
int					run_builtin(t_shell *shell);

// env
char				*extract_value(char *arg);
char				*extract_key(char *arg);
int					ft_env(t_shell *shell);

// exit
int					check_numeric(char *str);
int					handle_exit(char **cmd);
int					ft_exit(char **cmd, t_shell *shell);

// pwd
int					ft_pwd(t_shell *shell);

// echo
int					parse_options(char **cmd, int *newline);
void				print_args(char **cmd, int start_index, int newline);
int					ft_echo(char **cmd);

// cd
int					ft_cd(char **cmd, t_shell *shell);
char				*get_pwd(t_shell *shell, char *key);

// unset
int					ft_unset(char **cmd, t_shell *shell);
int					find_key(char *arg, t_env *env_list);

// export
int					ft_export(char **cmd, t_shell *shell);
int					check_key(char *arg);
int					check_keys(char **cmd);
void				export_no_arg(t_shell *shell);

/****************************************************
		srcs/error
****************************************************/

// test_utils.c
char				*convert_type(int type);
void				print_arg_list(t_node *args);
void				print_env_list(t_env *env_list);
void				print_shell(t_shell *shell);

/****************************************************
		srcs/signals
****************************************************/

// signals.c
void				main_sig_handler(void);
void				exec_child_sig(void);

#endif
