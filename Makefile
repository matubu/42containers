NAME=containers
SRCS=main.cpp
OBJS=$(SRCS:.cpp=.o)
FLAG=-Wall -Werror -Wextra -std=c++98
ECHO=echo "\033[92m"
ENDL="\033[0m"

all:
	@$(ECHO) "---> compiling sources ⚙️  <---" $(ENDL)
	@$(MAKE) $(NAME)
%.o: %.cpp
	g++ $(FLAG) -c $^ -o $@
$(NAME): $(OBJS)
	g++ $(FLAG) $(OBJS) -o $(NAME)
run: all
	@$(ECHO) "-------> launching 🚀 <-------" $(ENDL)
	./$(NAME)
re: fclean all
clean:
	@$(ECHO) "------> cleaning up 🧼 <------" $(ENDL)
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
test: re run
	@$(MAKE) fclean

.PHONY: all run re clean fclean test
