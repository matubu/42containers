FLAGS=-Wall -Werror -Wextra# -fsanitize=address

all:
	g++ $(FLAGS) main.cpp
run: all
	./a.out
re: fclean all
clean:
fclean: clean
	rm -rf a.out
