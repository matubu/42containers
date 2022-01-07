#include <iostream>
#include <vector>
#include "vector.hpp"

template<class T>
void	debug(T &vector)
{
	std::string endl("\033[0m\n");
	std::cout << "<\033[92m" << (typeid(T) == typeid(ft::vector<int>) ? "ft" : "std") << "\033[0m> {" << endl;
	std::cout << "\033[94mdata\033[0m() -> \033[92m" << vector.data() << endl;
	typename T::size_type n = vector.size();
	while (n--)
		std::cout << "  - [\033[91m" << n << "\033[0m] -> \033[91m" << vector[n] << endl;
	std::cout << "\033[94mempty\033[0m() -> \033[33m" << (vector.empty() ? "true" : "false") << endl;
	std::cout << "\033[94msize\033[0m() -> \033[91m" << vector.size() << endl;
	std::cout << "\033[94mmax_size\033[0m() -> \033[91m" << vector.max_size() << endl;
	std::cout << "\033[94mcapacity\033[0m() -> \033[91m" << vector.capacity() << endl;
	std::cout << "\033[0m}" << std::endl;
}

int	main()
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
}
