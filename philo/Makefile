# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 13:19:38 by aducobu           #+#    #+#              #
#    Updated: 2023/10/09 14:07:27 by aducobu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			philo

SRCS = 			main.c parsing.c

OBJS = 			${SRCS:%.c=objects/%.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror
PHILO_FLAG = -pthread
RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS} Makefile
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${CFLAGS} ${PHILO_FLAG}
	
objects/%.o: %.c
	mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c -o $@ $^

clean:
	${RM} objects

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re%
