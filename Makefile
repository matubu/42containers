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
	$(MAKE) -C ft_containers_testers/testor1 $(1) || echo "Error for testor 1"
	cd ft_containers_testers/testor2 && ./test.sh $(1) || echo "Error for testor 2"
	cd ft_containers_testers/testor3 && ./do.sh $(1) || echo "Error for testor 3"
	cd ft_containers-unit-test && ./start.sh $(1) || echo "Error for unit testor"
endef

vector:
	$(call test,vector)
stack:
	$(call test,stack)
map:
	$(call test,map)

fulltest: test vector stack map

.PHONY: all run re clean fclean test fulltest vector stack map
