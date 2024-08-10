# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jolai <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 15:25:28 by jolai             #+#    #+#              #
#    Updated: 2024/05/20 20:18:22 by jolai            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_toupper.c ft_tolower.c \
	ft_strlen.c ft_strlcpy.c ft_strlcat.c \
	ft_strchr.c ft_strrchr.c ft_strcmp.c ft_strncmp.c ft_strnstr.c ft_atoi.c \
	ft_memset.c ft_bzero.c ft_memchr.c ft_memcpy.c ft_memmove.c ft_memcmp.c \
	ft_calloc.c ft_strdup.c \
	ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

B_SRCS	= \
	ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c ft_lstsize.c ft_lstlast.c \
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

ADD_SRCS	=	ft_printf.c ft_printstuff.c \
				get_next_line_bonus.c get_next_line_utils_bonus.c \
				ft_free_2d_array.c

OBJS	= ${SRCS:.c=.o}

B_OBJS	= ${B_SRCS:.c=.o}

ADD_OBJS	= ${ADD_SRCS:.c=.o}

CC		= cc
RM		= rm -f
AR		= ar rcs

CFLAGS	= -Wall -Wextra -Werror -c -g

NAME	= libft.a

all		: 	${NAME}

$(NAME)	:	${OBJS} ${ADD_OBJS}
	${AR} ${NAME} ${OBJS} ${ADD_OBJS}

.c.o	:
	${CC} ${CFLAGS} $< -o ${<:.c=.o} 

clean	:
	${RM} ${OBJS} ${B_OBJS} ${ADD_OBJS}

fclean	:	clean
	${RM} ${NAME}

re		:	fclean all

bonus	:	${OBJS} ${B_OBJS} ${ADD_OBJS}
	${AR} ${NAME} ${OBJS} ${B_OBJS} ${ADD_OBJS}

.PHONY	:	all clean fclean re bonus
