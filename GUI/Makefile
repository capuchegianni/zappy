NAME=zappy_gui

$(NAME):
	mkdir -p build
	cd build && cmake .. && make

all:	$(NAME)

clean:
	rm -rf build
	rm -rf lib/Maths/build

fclean: clean
	rm -f $(NAME)

re: fclean all
