##
## EPITECH PROJECT, 2024
## B-YEP-400-LIL-4-1-zappy-nicolas.pechart
## File description:
## ./Makefile
##

all:
	$(MAKE) -C ./AI
	$(MAKE) -C ./GUI
	$(MAKE) -C ./server
	cp ./server/zappy_server .
	cp ./GUI/zappy_gui .
	cp ./AI/zappy_ai .

clean:
	$(MAKE) clean -C ./AI
	$(MAKE) clean -C ./GUI
	$(MAKE) clean -C ./server

fclean:
	$(MAKE) fclean -C ./AI
	$(MAKE) fclean -C ./GUI
	$(MAKE) fclean -C ./server
	rm -f zappy_server
	rm -f zappy_gui
	rm -f zappy_ai

re: fclean all

zappy_server:
	$(MAKE) -C ./server

zappy_gui:
	$(MAKE) -C ./GUI

zappy_ai:
	$(MAKE) -C ./AI