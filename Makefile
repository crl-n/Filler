.PHONY: all, clean, fclean, re

NAME = cnysten.filler

SRC = main.c

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
