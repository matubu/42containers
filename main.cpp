#include <iomanip>
#include <iostream>
#include <vector>
#include "vector.hpp"

#define ITER 1000000
#define ENDL "\033[0m" << "\n"
#define TYPE int

#define DEBUG(_vec, _namespace) \
	std::cout << " - \033[92m" << #_namespace << ENDL; \
	std::cout << "    [\033[33m" << _vec.size() << "\033[0m/\033[33m" << _vec.capacity() << "\033[0m] \033[0m \033[90m(" << _vec.data() << ")" << ENDL; \
	for (size_t i = 0; i < _vec.size(); i++) \
		std::cout << "    - [\033[33m" << i << "\033[0m] -> \033[33m" << _vec[i] << ENDL; \

#define RUN(_namespace, _vec, _cmd) { \
	_namespace::vector<TYPE> &vec = _vec; \
	int i = 0; (void)i; _cmd; \
	DEBUG(_vec, _namespace); \
}

#define BENCH(_return, _namespace, _vec, _cmd) { \
	_namespace::vector<TYPE> &vec = _vec; \
	clock_t start = clock(); \
	for(int i = 0; i < ITER; i++) _cmd; \
	_return = (double)(clock() - start) / CLOCKS_PER_SEC * 1000; \
}

#define SHOW(_this_ms, _other_ms, _namespace) \
	std::cout << (_this_ms <= _other_ms ? "\033[92m" : "\033[91m") \
		<< std::setw(3) << #_namespace << " -> " << _this_ms << "ms   \033[90m(" << ITER << " times)" << ENDL;

#define TEST(cmd) { \
	std::cout << ENDL << "\033[94m" << #cmd << ENDL; \
	RUN(std, real, cmd); \
	RUN(ft, mine, cmd); \
	double	std_ms, ft_ms; \
	BENCH(std_ms, std, real_bench, cmd); \
	BENCH(ft_ms, ft, mine_bench, cmd); \
	SHOW(std_ms, ft_ms, std); \
	SHOW(ft_ms, std_ms, ft); \
	std::cout << ENDL; \
}

void	scope()
{
	std::vector<TYPE> real, real_bench;
	ft::vector<TYPE> mine, mine_bench;

	TEST(vec.push_back(1));
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
}

int	main(int argc, char **argv)
{
	scope();
	#ifdef __APPLE__
	if (argc)
	{
		const char	*cmd = ("leaks " + std::string(argv[0]).substr(2)).c_str();
		std::cout << cmd << ENDL;
		system(cmd);
	}
	#endif
	return (0);
}
