# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 13:19:38 by aducobu           #+#    #+#              #
#    Updated: 2023/10/19 15:49:03 by aducobu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			philo

SRCS = 			sources/main.c sources/parsing.c sources/routine.c \
				sources/monitor.c sources/forks.c sources/utils.c

OBJS = 			$(SRCS:sources/%.c=objects/%.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3#-fsanitize=thread -g3
HEADER = philo.h
PHILO_FLAG = -pthread
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) Makefile include/philo.h	
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(PHILO_FLAG)
	
objects/%.o: sources/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) objects

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re%
