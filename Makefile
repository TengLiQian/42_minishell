# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lteng <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/23 14:14:28 by lteng             #+#    #+#              #
#    Updated: 2024/07/01 23:55:55 by lteng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c signals.c \
	env/env.c \
	env/get_env.c \
	lexer/lexer.c \
	lexer/lexer_free.c \
	lexer/lexer_token.c \
	lexer/lexer_utils.c \
	builtins/main_builtin.c \
	builtins/ft_env.c \
	builtins/ft_exit.c \
	builtins/ft_pwd.c

OBJS = $(SRCS:.c=.o)
CC = cc -g
CFLAGS = -Wall -Werror -Wextra
LFLAGS = -lreadline
NAME = minishell
RM = rm -rf
all: $(NAME)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

$(LIBFT):
	make -C $(LIBFT_PATH) all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_PATH) -lft $(LFLAGS)

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_PATH)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re
