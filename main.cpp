/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matubu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 21:38:11 by matubu            #+#    #+#             */
/*   Updated: 2022/01/16 12:18:31 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <time.h>
#include <vector>
//#include <stack>
#include "vector.hpp"
//#include "stack.hpp"

#define ITER 1000000 // 1 millions
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
	std::cout << "  \033[94mmax_size\033[0m() -> \033[33m" << vector.max_size() << ENDL; \
	std::cout << "  \033[94mcapacity\033[0m() -> \033[33m" << vector.capacity() << ENDL; \
	std::cout << "  \033[94mempty\033[0m() -> \033[36m" << (vector.empty() ? "true" : "false") << ENDL; \
	std::cout << "  \033[94msize\033[0m() -> \033[33m" << vector.size() << ENDL; \
}

#define TEST(cmd) \
	std::cout << "\n\n-----> " << #cmd << ENDL; \
	real.cmd; \
	DEBUG(real); \
	mine.cmd; \
	DEBUG(mine)

#define SPED(cmd) { \
	std::cout << (strncmp(#cmd, "real", 4) ? "\033[36m" : "\033[91m"); \
	clock_t start = clock(); \
	for(int i = 0; i < ITER; i++) cmd; \
	std::cout << std::setw(25) << #cmd << " * " << ITER << " -> " \
		<< ((double)(clock() - start) / CLOCKS_PER_SEC * 1000) << "ms" << ENDL; \
	}

#define PERF(cmd) \
	SPED(real.cmd); \
	SPED(mine.cmd); \
	std::cout << ENDL


//TODO try with string
int	main(void)
{
	std::vector<int>	real;
	ft::vector<int>		mine;

	DEBUG(real);
	DEBUG(mine);

	TEST(clear());
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
	PERF(resize(i + 1));
	SPED(real[i]++); SPED(mine[i]++); std::cout << ENDL;
	PERF(resize(ITER - i));

	DEBUG(real);
	DEBUG(mine);

	std::vector<int>	real_copy(real);
	ft::vector<int>		mine_copy(mine);

	DEBUG(real_copy);
	DEBUG(mine_copy);

	TEST(push_back(1));

	std::cout << "\n\n-----> swap()" << ENDL;
	real.swap(real_copy);
	mine.swap(mine_copy);

	DEBUG(real);
	DEBUG(mine);
	DEBUG(real_copy);
	DEBUG(mine_copy);

	TEST(pop_back());

	std::cout << "\n\n-----> _copy = notcopy" << ENDL;
	std::vector<int>	*real_asgn = &(real_copy = real);
	ft::vector<int>		*mine_asgn = &(mine_copy = mine);
	DEBUG((*real_asgn));
	DEBUG((*mine_asgn));

	DEBUG(real);
	DEBUG(mine);
	DEBUG(real_copy);
	DEBUG(mine_copy);

	std::vector<int>	real_len_7_fill_5(7, 5);
	ft::vector<int>		mine_len_7_fill_5(7, 5);

	DEBUG(real_len_7_fill_5);
	DEBUG(mine_len_7_fill_5);

	std::cout << (real > real_len_7_fill_5) << " (>) " << (mine > mine_len_7_fill_5) << ENDL;
	std::cout << (real == real_len_7_fill_5) << " (==)  " << (mine == mine_len_7_fill_5) << ENDL;
	std::cout << (real < real_len_7_fill_5) << " (<) " << (mine < mine_len_7_fill_5) << ENDL;
	std::cout << (real != real_len_7_fill_5) << " (!=) " << (mine != mine_len_7_fill_5) << ENDL;
	std::cout << (real >= real_len_7_fill_5) << " (>=) " << (mine >= mine_len_7_fill_5) << ENDL;
	std::cout << (real <= real_len_7_fill_5) << " (<=) " << (mine <= mine_len_7_fill_5) << ENDL;

	std::swap(real, real_len_7_fill_5);
	ft::swap(mine, mine_len_7_fill_5);

	DEBUG(real);
	DEBUG(mine);

	TEST(assign(3, 4))
	TEST(assign(7, 8))

	real[6] = 7;
	mine[6] = 7;
	
	std::cout << "real:" << ENDL;
	for (std::vector<int>::iterator it = real.begin(); it != real.end(); it++)
		std::cout << "\t- " << *it << ENDL;
	std::cout << "mine:" << ENDL;
	for (ft::vector<int>::iterator it = mine.begin(); it != mine.end(); it++)
		std::cout << "\t- " << *it << ENDL;
	std::cout << "reverse real:" << ENDL;
	for (std::vector<int>::reverse_iterator it = real.rbegin(); it != real.rend(); it++)
		std::cout << "\t- " << *it << ENDL;
	std::cout << "reverse mine:" << ENDL;
	for (ft::vector<int>::reverse_iterator it = mine.rbegin(); it != mine.rend(); it++)
		std::cout << "\t- " << *it << ENDL;


	DEBUG(real);
	std::cout << *real.insert(real.begin(), 5) << ENDL;
	DEBUG(real);
	std::cout << *real.insert(real.begin() + 8, 5) << ENDL;
	DEBUG(real);

	DEBUG(mine);
	std::cout << *mine.insert(mine.begin(), 5) << ENDL;
	DEBUG(mine);
	std::cout << *mine.insert(mine.begin() + 8, 5) << ENDL;
	DEBUG(mine);
}
