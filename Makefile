# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 17:54:19 by pkhvorov          #+#    #+#              #
#    Updated: 2024/12/13 17:40:57 by pkhvorov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= srcs/pipex.c srcs/pipex_utils.c
OBJS	= $(SRCS:.c=.o)
NAME	= pipex
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I includes
RM		= rm -f
LIBDIR  = ./libft
LIBFT	= ${LIBDIR}/libft.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT}
	@${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

${LIBFT}:
	@${MAKE} -C ${LIBDIR}

clean: 
	@${MAKE} -C ${LIBDIR} clean
	@${RM} ${OBJS}

fclean: clean
	@${MAKE} -C ${LIBDIR} fclean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re