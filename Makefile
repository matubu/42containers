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

TESTED_CONTAINER=vector

fulltest: test
	@$(MAKE) -C ft_containers_testers/testor1 $(TESTED_CONTAINER)
	@./ft_containers_testers/testor2/test.sh $(TESTED_CONTAINER)
	@./ft_containers_testers/testor3/do.sh $(TESTED_CONTAINER)
	@./ft_containers-unit-test/start.sh $(TESTED_CONTAINER)

.PHONY: all run re clean fclean test fulltest
