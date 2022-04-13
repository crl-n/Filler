.PHONY: all, clean, fclean, re

NAME = cnysten.filler

SRC = main.c allocate.c cleanup.c command.c parse.c skip.c symbol.c think.c heatmap.c

OBJ = $(SRC:%.c=%.o)

LIB = -L./libft/ -lft

INC = -I./libft/

CFLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(SRC)
	-@make -C ./libft
	$(CC) $(CFLAGS) -c $(SRC) $(INC)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) $(INC)
	cp $(NAME) ../resources_filler/players

test:
	../resources_filler/filler_vm -p2 ../resources_filler/players/hcao.filler -p1 ./cnysten.filler -f ../resources_filler/maps/map00

clean:
	-@make -C ./libft clean
	-@/bin/rm $(OBJ)

fclean: clean
	-@make -C ./libft fclean
	-@/bin/rm $(NAME)

re: fclean all
