##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

NAME = libmydb.a

CC = gcc

CFLAGS = -Wall -Wextra -g -g3

SRC = 	files.c 		\
		folders.c 		\
		db_struct.c 	\
		list_folder.c 	\

OBJ_DIR = ../../obj/

OBJ = $(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	ar rc ../$(NAME) $(OBJ)
	@echo -n "[ "
	@echo -n "\e[1;34mOK\e[0m"
	@echo -n " ] "
	@echo "\e[1;32mSuccessfully compiled libmydb\e[0m"

$(OBJ_DIR)%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
