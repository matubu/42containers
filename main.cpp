#include <iomanip>
#include <iostream>
#include <vector>
#include "vector.hpp"

#define ENDL "\033[0m" << "\n"

#define DEBUG(_vec, _namespace) \
	std::cout << " - \033[92m" << #_namespace << ENDL; \
	std::cout << "    [\033[33m" << _vec.size() << "\033[0m/\033[33m" << _vec.capacity() << "\033[0m] \033[0m \033[90m(" << _vec.data() << ")" << ENDL; \
	for (size_t i = 0; i < _vec.size(); i++) \
		std::cout << "    - [\033[33m" << i << "\033[0m] -> \033[33m" << _vec[i] << ENDL; \

#define RUN(_namespace, _vec, _cmd) { \
	_namespace::vector<type> &vec = _vec; \
	int i = 0; (void)i; _cmd; \
	DEBUG(_vec, _namespace); \
}

#define BENCH(_return, _namespace, _vec, _cmd) { \
	_namespace::vector<type> &vec = _vec; \
	clock_t start = clock(); \
	for (int j = 0; j < 32; j++) \
	{ \
		for (int y = 0; y < iter; y++) \
		{ \
			int i = y + j * iter; \
			(void)i; \
			_cmd; \
		} \
		std::cout << "█" << std::flush; \
	} \
	_return = (double)(clock() - start) / CLOCKS_PER_SEC * 1000; \
}

#define SHOW(_this_ms, _other_ms, _namespace) \
	std::cout << (_this_ms <= _other_ms ? "\033[92m" : "\033[91m") \
		<< std::setw(3) << #_namespace << " -> " << _this_ms << "ms   \033[90m(" << iter * 32 << " times)" << ENDL;

#define INIT() \
	std::vector<type> real, real_bench; \
	ft::vector<type> mine, mine_bench; \
	int iter = 100000;

#define TEST(cmd) { \
	std::cout << ENDL << "\033[94m" << #cmd << ENDL; \
	RUN(std, real, cmd); \
	RUN(ft, mine, cmd); \
	double	std_ms, ft_ms; \
	std::cout << "\033[94m"; \
	BENCH(std_ms, std, real_bench, cmd); \
	std::cout << "\033[91m"; \
	BENCH(ft_ms, ft, mine_bench, cmd); \
	std::cout << "\33[2K\r"; \
	SHOW(std_ms, ft_ms, std); \
	SHOW(ft_ms, std_ms, ft); \
	std::cout << ENDL; \
}

void	scope_int(void)
{
	typedef int type;
	INIT();

	TEST(vec.front());
	TEST(vec.push_back(1));
	TEST(vec.push_back(*vec.begin()));
	TEST(vec.pop_back());
	TEST(vec.push_back(3));
	TEST(vec.push_back(2));
	TEST(vec.reserve(5));
	TEST(vec.clear());
	TEST(vec.resize(1));
	TEST(vec.push_back(i));
	TEST(vec[i + 1] += 2);
	TEST(vec[i]++);
	TEST(vec.erase(vec.end() - 2));
	TEST(vec.push_back(i+3));
	TEST(vec.push_back(i+2));
	TEST(vec.push_back(i+1));
	TEST(vec.erase(vec.end() - 3, vec.end() - 1));
	iter = 10;
	TEST(vec.insert(vec.begin() + 1, 7, i + 7));
	TEST(vec.insert(vec.begin(), vec.begin() + 1, vec.begin() + 3));
}

void scope_string(void)
{
	typedef std::string type;
	INIT();

	std::string s = "Hello World";
	TEST(vec.push_back(s))
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	scope_int();
	scope_string();
	#ifdef __APPLE__
	if (argc <= 0)
		return (1);
	std::string cmd = "leaks " + std::string(argv[0]).substr(2);
	std::cout << cmd << ENDL;
	system(cmd.c_str());
	#endif
	return (0);
}
