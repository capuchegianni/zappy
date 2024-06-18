##
## EPITECH PROJECT, 2024
## MYTEAMS
## File description:
## Makefile to compile myteams
##

## -------------------------------- FLAGS ---------------------------------- ##

WARNING_FLAGS := -Wall -Wextra -W -g -std=gnu2x

LIB_FLAGS := -I include/ -luuid

FILE = coding-style.sh


## -------------------------------- SERVER --------------------------------- ##

NAME = zappy_server

OBJ_DIR = ./obj/

SRC = 	src/server/main.c						\
		src/server/utils.c 						\
		src/server/loop/server.c 				\
		src/server/loop/execute.c				\
		src/server/loop/server_utils.c 			\
		src/server/loop/commands.c				\
		src/server/parser/argument_parser.c 	\
		src/server/parser/flags.c 				\
		src/server/command/msz.c 				\
		src/server/command/sgt.c 				\
		src/server/command/bct.c 				\
		src/server/command/mct.c 				\
		src/server/parser/flags/clients.c 		\
		src/server/game/game_loop.c 			\
		src/server/parser/flags/frequency.c 	\
		src/server/parser/flags/map.c 			\
		src/server/parser/flags/port.c 			\
		src/server/parser/flags/teams.c			\
		src/server/game/levels.c				\
		src/server/game/map.c

OBJ = $(addprefix $(OBJ_DIR), \
	$(subst src/,,$(SRC:.c=.o)))


## --------------------------------- RULES --------------------------------- ##

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	gcc $(SRC) $(WARNING_FLAGS) -o $(NAME) $(LIB_FLAGS)
	@echo -n "[ "
	@echo -n "\e[1;34mOK\e[0m"
	@echo -n " ] "
	@echo "\e[1;32mSuccessfully compiled $(NAME) files\e[0m"

$(OBJ_DIR)%.o: src/%.c
	gcc $(WARNING_FLAGS) -c -o \
	$(OBJ_DIR)$(subst src/,,$(basename $<)).o $< $(LIB_FLAGS)

$(OBJ_DIR):
	mkdir -p $(dir $(OBJ))

clean:
	rm -f $(OBJ)
	@echo -n "[ "
	@echo -n "\e[1;34mOK\e[0m"
	@echo -n " ] "
	@echo "\e[1;32mSuccessfully removed .o & .log files\e[0m"

cstyle: fclean
	FILE=$$(find ~/ -name "$(FILE)" -print -quit); \
	if [ -z "$$FILE" ]; then \
		echo "[ \e[1;93mWARNING\e[0m ]" \
		"\e[1;31mFile $(FILE) not found.\e[0m"; \
		exit 69; \
	else \
		bash $$FILE . .; \
	fi
	if [ -s coding-style-reports.log ]; then \
		echo "[ \e[1;93mWARNING\e[0m ]" \
		"\e[1;31mFound coding style errors in coding-style-reports.log\e[0m"; \
		cat coding-style-reports.log; \
	else \
		echo "[ \e[1;34mOK\e[0m ]" \
		"\e[1;32mNo coding style error found\e[0m"; \
		rm -f coding-style-reports.log; \
	fi

fclean: clean
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)
	rm -f *.log
	@echo -n "[ "
	@echo -n "\e[1;34mOK\e[0m"
	@echo -n " ] "
	@echo "\e[1;32mSuccessfully removed $(NAME)\e[0m"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean cstyle fclean re
