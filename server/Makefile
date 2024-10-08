##
## EPITECH PROJECT, 2024
## MYTEAMS
## File description:
## Makefile to compile myteams
##

## -------------------------------- FLAGS ---------------------------------- ##

WARNING_FLAGS := -Wall -Wextra -W -g -std=gnu2x

LIB_FLAGS := -I include/ -luuid -lm

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
		src/server/command/sst.c 				\
		src/server/command/bct.c 				\
		src/server/command/mct.c 				\
		src/server/command/tna.c 				\
		src/server/command/pnw.c 				\
		src/server/command/ppo.c 				\
		src/server/command/plv.c 				\
		src/server/command/pin.c 				\
		src/server/command/not_implemented.c	\
		src/server/parser/flags/clients.c 		\
		src/server/game/game_loop.c 			\
		src/server/parser/flags/frequency.c 	\
		src/server/parser/flags/map.c 			\
		src/server/parser/flags/port.c 			\
		src/server/parser/flags/teams.c			\
		src/server/game/levels.c				\
		src/server/game/map.c					\
		src/server/game/teams.c					\
		src/server/game/life_units.c 			\
		src/server/game/incantation.c 			\
		src/server/game/win_condition.c 		\
		src/server/command/ai/forward.c			\
		src/server/command/ai/right.c 			\
		src/server/command/ai/left.c 			\
		src/server/command/ai/look.c 			\
		src/server/command/ai/inventory.c		\
		src/server/command/ai/connect_nbr.c		\
		src/server/command/ai/fork.c			\
		src/server/command/ai/eject.c			\
		src/server/command/ai/take.c			\
		src/server/command/ai/set.c				\
		src/server/command/ai/incantation.c 	\
		src/server/command/ai/broadcast.c

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
