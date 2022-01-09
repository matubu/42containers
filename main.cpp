#include <iostream>
#include <iomanip>
#include <time.h>
#include <vector>
#include "vector.hpp"

#define ITER 10000000
#define ENDL "\033[0m\n"

template<class T>
void	at(T &vector, size_t n)
{
	try { vector.at(n); std::cout << "  \033[94mat\033[0m(" << n << ") -> \033[33m" << vector.at(n) << ENDL; }
	catch (const std::exception &e) { std::cout << "  \033[94mat\033[0m(" << n << ") -> \033[91mOut of range" << ENDL; }
}

#define DEBUG(vector) { \
	std::cout << "<\033[92m" << #vector << "\033[0m>" << ENDL; \
	std::cout << "  \033[94mdata\033[0m() -> \033[33m" << vector.data() << ENDL; \
	size_t n = vector.size(); \
	at(vector, 0); \
	at(vector, 1); \
	at(vector, n - 1); \
	at(vector, n); \
	if (n) \
	{ \
		std::cout << "  \033[94mfront\033[0m() -> \033[33m" << vector.front() << ENDL; \
		std::cout << "  \033[94mlast\033[0m() -> \033[33m" << vector.back() << ENDL; \
	} \
	while (n--) \
		std::cout << "    - [\033[33m" << n << "\033[0m] -> \033[33m" << vector[n] << ENDL; \
	std::cout << "  \033[94mempty\033[0m() -> \033[36m" << (vector.empty() ? "true" : "false") << ENDL; \
	std::cout << "  \033[94msize\033[0m() -> \033[33m" << vector.size() << ENDL; \
	std::cout << "  \033[94mmax_size\033[0m() -> \033[33m" << vector.max_size() << ENDL; \
	std::cout << "  \033[94mcapacity\033[0m() -> \033[33m" << vector.capacity() << ENDL; }

#define TEST(cmd) \
	std::cout << "\n\n-----> " << #cmd << ENDL; \
	real.cmd; \
	DEBUG(real); \
	mine.cmd; \
	DEBUG(mine)

#define SPED(cmd) \
	std::cout << (strncmp(#cmd, "real", 4) ? "\033[36m" : "\033[91m"); \
	start = clock(); \
	for(int i = 0; i < ITER; i++) cmd; \
	std::cout << std::setw(25) << #cmd << " * " << ITER << " -> " \
		<< ((double)(clock() - start) / CLOCKS_PER_SEC * 1000) << "ms" << ENDL

#define PERF(cmd) \
	SPED(real.cmd); \
	SPED(mine.cmd); \
	std::cout << ENDL

int	main(void)
{
	clock_t	start;
	std::vector<int>	real;
	ft::vector<int>		mine;

	DEBUG(real);
	DEBUG(mine);

	//TODO test copy
	TEST(reserve(1));
	TEST(push_back(1));
	TEST(push_back(2));
	TEST(push_back(3));
	TEST(pop_back());
	TEST(resize(5));
	TEST(resize(2));
	TEST(resize(1));
	TEST(pop_back());
	TEST(reserve(100));

	PERF(push_back(i));
	PERF(pop_back());
	PERF(clear());
	PERF(resize(i));
	PERF(resize(ITER - i));
	SPED(real[i]++); SPED(mine[i]++);

	DEBUG(real);
	DEBUG(mine);

	std::vector<int>	real_copy(real);
	ft::vector<int>		mine_copy(mine);

	DEBUG(real_copy);
	DEBUG(mine_copy);
}
