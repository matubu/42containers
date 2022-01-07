all:
	g++ -Wall -Werror -Wextra -fsanitize=address main.cpp
run: all
	./a.out
re: fclean all
clean:
fclean: clean
	rm -rf a.out
