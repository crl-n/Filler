# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 22:16:23 by carlnysten        #+#    #+#              #
#    Updated: 2022/06/29 11:16:06 by cnysten          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, debug, fsan, clean, fclean, re

NAME := cnysten.filler

CC = gcc
CFLAGS := -Wall -Werror -Wextra
INC := -I. -I./libft/

SRC_DIR := ./src
SRC_FILES := allocate.c boolean_array.c can_place_piece.c cleanup.c command.c \
	  get_map_info.c get_piece_info.c main.c parse.c player_symbol.c queue.c \
	  skip_line.c solve.c update_heatmap.c
SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR := ./obj
OBJ_FILES := $(SRC_FILES:%.c=%.o)
OBJ := $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

LIBFT = ./libft/libft.a
LINK := -L./libft/ -lft

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LINK) -o $(@)

$(OBJ_DIR):
	@mkdir -p $(@)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -c $(CFLAGS) $(INC) -o $@ $<

$(LIBFT):
	-@make -C ./libft

fsan: CFLAGS += -g -fsanitize=address
fsan: all

debug: CFLAGS += -g
debug: all

clean:
	-@make -C ./libft clean
	-@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	-@make -C ./libft fclean
	-@/bin/rm $(NAME)

re: fclean all
