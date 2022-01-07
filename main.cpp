#include <iostream>
#include <vector>
#include <time.h>
#include "vector.hpp"

const std::string endl = "\033[0m\n";

template<class T>
void	at(T &vector, size_t n)
{
	try { vector.at(n); std::cout << "  \033[94mat\033[0m(" << n << ") -> \033[33m" << vector.at(n) << endl; }
	catch (const std::exception &e) { std::cout << "  \033[94mat\033[0m(" << n << ") -> \033[91mOut of range" << endl; }
}

template<class T>
void	debug(T &vector)
{
	std::cout << "<\033[92m" << (typeid(T) == typeid(ft::vector<int>) ? "ft" : "std") << "\033[0m>" << endl;
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

#define ITER 10000000
#define TEST(test, lib, name) now(); for(int i = 0; i < ITER; i++) test; now(lib, name)

void	now(const char *lib = NULL, const char *oper = NULL)
{
	static clock_t	start;
	if (lib)
		std::cout << "\033[92m" << lib << "\033[0m " << oper << " -> "
			<< ((double)(clock() - start) / CLOCKS_PER_SEC * 1000) << "ms" << std::endl;
	start = clock();
}

int	main(void)
{
	ft::vector<int>		mine;
	std::vector<int>	real;

	debug(real);
	real.push_back(1);
	debug(real);
	real.push_back(2);
	debug(real);
	real.push_back(3);
	debug(real);
	real.pop_back();
	debug(real);
	real.pop_back();
	debug(real);
	real.pop_back();
	debug(real);
	real.reserve(100);
	debug(real);

	debug(mine);
	mine.push_back(1);
	debug(mine);
	mine.push_back(2);
	debug(mine);
	mine.push_back(3);
	debug(mine);
	mine.pop_back();
	debug(mine);
	mine.pop_back();
	debug(mine);
	mine.pop_back();
	debug(mine);
	mine.reserve(100);
	debug(mine);

	TEST(real.push_back(i), "std", "push");
	TEST(mine.push_back(i), "ft", "push");

	TEST(real[i]++, "std", "access");
	TEST(mine[i]++, "ft", "access");

	TEST(real.pop_back(), "std", "pop");
	TEST(mine.pop_back(), "ft", "pop");

	debug(real);
	debug(mine);
}
