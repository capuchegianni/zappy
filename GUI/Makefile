NAME=zappy_gui

$(NAME):
	mkdir -p build
	cd build && cmake .. && make && mv $(NAME) ..

all:	$(NAME)

clean:
	rm -rf build

fclean: clean
	rm -f $(NAME)

re: fclean all
