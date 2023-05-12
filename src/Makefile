# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 12:15:26 by gialexan          #+#    #+#              #
#    Updated: 2023/05/12 11:24:26 by gialexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	:=		main.c		\
			action.c	\
			control.c 	\
			interface.c \
			utils.c 	\
			watcher.c	\
			parse.c

PFLAGS := -pthread

OBJ	:=		$(SRC:.c=.o)

CC	:=		gcc -g

CFLAGS	:=	-Wall -Wextra -Werror

RM := 		rm -f

NAME	:=	philo

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(PFLAGS) $(CFLAGS) $(OBJ) -o $(NAME)

helgrind:	$(NAME)
			valgrind --tool=helgrind ./philo 4 310 200 100

drd:		$(NAME)
			valgrind --tool=drd ./philo 4 310 200 100

clean:
			$(RM) $(OBJ) $(OBJ_BONUS)

fclean:		clean
			$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re


#- Test 1 800 200 200. The philosopher should not eat and should die.
#- Test 5 800 200 200. No philosopher should die.
#- Test 5 800 200 200 7. No philosopher should die and the simulation
#should stop when every philosopher has eaten at least 7 times.
#- Test 4 410 200 200. No philosopher should die.
#- Test 4 310 200 100. One philosopher should die.