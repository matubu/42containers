#include <iostream>
#include <iomanip>
#include <time.h>
#include <vector>
#include "vector.hpp"

#define ITER 10000000
#define endl "\033[0m\n"

template<class T>
void	at(T &vector, size_t n)
{
	try { vector.at(n); std::cout << "  \033[94mat\033[0m(" << n << ") -> \033[33m" << vector.at(n) << endl; }
	catch (const std::exception &e) { std::cout << "  \033[94mat\033[0m(" << n << ") -> \033[91mOut of range" << endl; }
}

template<class T>
void	debug(T &vector)
{
	std::cout << "<\033[92m" << (typeid(T) == typeid(ft::vector<int>) ? "ft " : "std") << "\033[0m>" << endl;
	std::cout << "  \033[94mdata\033[0m() -> \033[33m" << vector.data() << endl;
	typename T::size_type n = vector.size();
	at(vector, 0);
	at(vector, 1);
	at(vector, n - 1);
	at(vector, n);
	if (n)
	{
		std::cout << "  \033[94mfront\033[0m() -> \033[33m" << vector.front() << endl;
		std::cout << "  \033[94mlast\033[0m() -> \033[33m" << vector.back() << endl;
	}
	while (n--)
		std::cout << "    - [\033[33m" << n << "\033[0m] -> \033[33m" << vector[n] << endl;
	std::cout << "  \033[94mempty\033[0m() -> \033[36m" << (vector.empty() ? "true" : "false") << endl;
	std::cout << "  \033[94msize\033[0m() -> \033[33m" << vector.size() << endl;
	std::cout << "  \033[94mmax_size\033[0m() -> \033[33m" << vector.max_size() << endl;
	std::cout << "  \033[94mcapacity\033[0m() -> \033[33m" << vector.capacity() << endl;
}

#define TEST(cmd) \
	std::cout << "\n\n-----> " << #cmd << endl; \
	real.cmd; \
	debug(real); \
	mine.cmd; \
	debug(mine)

#define SPED(cmd) \
	start = clock(); \
	for(int i = 0; i < ITER; i++) cmd; \
	std::cout << std::setw(25) << #cmd << " * " << ITER << " -> " \
		<< ((double)(clock() - start) / CLOCKS_PER_SEC * 1000) << "ms" << endl

#define PERF(cmd) \
	SPED(real.cmd); \
	SPED(mine.cmd)

int	main(void)
{
	clock_t	start;
	std::vector<int>	real;
	ft::vector<int>		mine;

	debug(real);
	debug(mine);

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

	debug(real);
	debug(mine);
}
