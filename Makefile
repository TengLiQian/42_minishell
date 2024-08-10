# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jolai <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/18 17:26:02 by jolai             #+#    #+#              #
#    Updated: 2024/08/07 17:05:33 by jolai            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
LIBFT   	=	./full_libft/
SRCDIR  	=	./srcs/
PARSE_DIR	=	$(addprefix $(SRCDIR), parser/)
ENV_DIR		=	$(addprefix $(SRCDIR), env/)
PIPE_DIR	=	$(addprefix $(SRCDIR), pipes/)
EXEC_DIR	=	$(addprefix $(SRCDIR), exec/)
BUILTIN_DIR	=	$(addprefix $(SRCDIR), builtins/)
ERROR_DIR	=	$(addprefix $(SRCDIR), error/)
SIGNAL_DIR	=	$(addprefix $(SRCDIR), signals/)
LIBFT_A		=	$(addprefix $(LIBFT), libft.a)
INCLUDE 	=	includes

PARSE_SRCS	= 	parser_splitting.c parser_tokenising.c parser_list_utils.c \
				parser_processing.c parser_expansion.c syntax_checks.c

PARSER_FILES= 	$(addprefix $(PARSE_DIR), $(PARSE_SRCS))

ENV_SRCS	= 	env_utils.c env_initial.c env_val_tools.c env_cpy.c sort_env.c

ENV_FILES	=	$(addprefix $(ENV_DIR), $(ENV_SRCS))

PIPE_SRCS	= 	pipes.c shell_list_utils.c

PIPE_FILES	= 	$(addprefix $(PIPE_DIR), $(PIPE_SRCS))

EXEC_SRCS	= 	cmd_utils.c cmd_child_utils.c redir_utils.c \
				heredoc.c heredoc_child.c array_conversions.c

EXEC_FILES	= 	$(addprefix $(EXEC_DIR), $(EXEC_SRCS))

BUILTIN_SRCS	=	ft_builtins.c ft_env.c ft_exit.c ft_pwd.c ft_echo.c ft_cd.c \
					ft_unset.c ft_export.c

BUILTIN_FILES	=	$(addprefix $(BUILTIN_DIR), $(BUILTIN_SRCS))

ERROR_SRCS	=	test_utils.c

ERROR_FILES	= 	$(addprefix $(ERROR_DIR), $(ERROR_SRCS))

SIGNAL_SRCS =	signals.c

SIGNAL_FILES= 	$(addprefix $(SIGNAL_DIR), $(SIGNAL_SRCS))

SRCS		=	main.c $(PARSER_FILES) $(ENV_FILES) $(PIPE_FILES) \
				$(EXEC_FILES) $(BUILTIN_FILES) $(ERROR_FILES) $(SIGNAL_FILES)

OBJS		=	${SRCS:.c=.o}

CC			= cc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -I$(INCLUDE) -g

all:		 	${NAME}

$(NAME):		${OBJS} ${LIBFT_A}
				@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -lreadline -o $(NAME)
				@echo "Compiled into executable \033[0;32mminishell\033[0m"

%.o:			%.c
				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(LIBFT_A):
				@$(MAKE) -s -C $(LIBFT)
				@echo "Compiled $(LIBFT_A)"

objclean:
				@$(RM) $(OBJS)
				@echo "Removed object files"

clean:			objclean
				@$(MAKE) clean -s -C $(LIBFT)
				@echo "Cleaned libft"

fclean:			clean
				@$(MAKE) fclean -s -C $(LIBFT)
				@echo "Full cleaned libft"
				@$(RM) $(NAME)
				@echo "Removed executable"

re:				fclean all

.PHONY:			all clean fclean re objclean bonus
