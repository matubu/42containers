NAME=containers
SRCS=main.cpp
OBJS=$(SRCS:.cpp=.o)
FLAG=-Wall -Werror -Wextra -std=c++98 -O3 -fsanitize=address
ECHO=echo "\033[92m"
ENDL="\033[0m"

all:
	@$(ECHO) "██████ compiling sources ⚙️  ███████" $(ENDL)
	@$(MAKE) $(NAME)
%.o: %.cpp
	g++ $(FLAG) -c $^ -o $@
$(NAME): $(OBJS)
	g++ $(FLAG) $(OBJS) -o $(NAME)
run: all
	@$(ECHO) "██████████ launching 🚀 ███████████" $(ENDL)
	./$(NAME)
re: fclean all
clean:
	@$(ECHO) "█████████ cleaning up 🧼 ██████████" $(ENDL)
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
test: re run
	@$(MAKE) fclean

define test
	cd containers_test && ./do.sh $(1) || echo "Error for containers test"
	$(MAKE) -C testor1 $(1) || echo "Error for testor 1"
	cd testor2 && ./test.sh $(1) || echo "Error for testor 2"
endef

vector:
	$(call test,vector)
stack:
	$(call test,stack)
map:
	$(call test,map)
set:
	$(call test,set)

fulltest: test vector stack map set

.PHONY: all run re clean fclean test vector stack map set fulltest
