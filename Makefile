# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 22:16:23 by carlnysten        #+#    #+#              #
#    Updated: 2022/06/17 23:08:58 by carlnysten       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = cnysten.filler

SRC = allocate.c can_place_piece.c cleanup.c command.c \
	  get_map_info.c main.c parse.c player_symbol.c queue.c skip_line.c \
	  solve.c update_heatmap.c \
	  debug.c

OBJ = $(SRC:%.c=%.o)

LIB = -L./libft/ -lft

INC = -I./libft/

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRC)
	-@make -C ./libft
	$(CC) $(CFLAGS) -c $(SRC) $(INC) -g
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) $(INC)

clean:
	-@make -C ./libft clean
	-@/bin/rm $(OBJ)

fclean: clean
	-@make -C ./libft fclean
	-@/bin/rm $(NAME)

re: fclean all
