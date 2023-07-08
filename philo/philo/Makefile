# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 21:41:32 by cgouiame          #+#    #+#              #
#    Updated: 2023/07/07 18:00:54 by cgouiame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Werror -Wextra
FILES = philo.c parsing.c routine.c utils.c
OBJ= $(FILES:.c=.o)
NAME = philo

all : $(NAME)

$(NAME): $(OBJ) 
		 		$(CC) $(OBJ) $(FLAGS) -o $(NAME)

%.o : %.c philo.h
		$(CC) $(FLAGS) -c $<

clean :
		 rm -f $(OBJ)

fclean : clean
		 rm -f $(NAME)

re : fclean all