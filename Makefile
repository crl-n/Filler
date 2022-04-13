# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 22:16:23 by carlnysten        #+#    #+#              #
#    Updated: 2022/04/13 22:17:15 by carlnysten       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = cnysten.filler

SRC = main.c allocate.c cleanup.c command.c parse.c skip.c \
	  symbol.c think.c heatmap.c

OBJ = $(SRC:%.c=%.o)

LIB = -L./libft/ -lft

INC = -I./libft/

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRC)
	-@make -C ./libft
	$(CC) $(CFLAGS) -c $(SRC) $(INC)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) $(INC)

clean:
	-@make -C ./libft clean
	-@/bin/rm $(OBJ)

fclean: clean
	-@make -C ./libft fclean
	-@/bin/rm $(NAME)

re: fclean all
