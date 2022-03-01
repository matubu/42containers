/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_reverseIterator.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:51:28 by bvalette          #+#    #+#             */
/*   Updated: 2021/09/06 14:53:00 by etakouer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_map.hpp"

void
test_iterator_values_pointed(
				ft::map<int, int>::reverse_iterator ft_it_test ,
				ft::map<int, int>& ft_c0 ,
				std::map<int, int>::reverse_iterator std_it_test ,
				std::map<int, int>& std_c0 , int line)	{

	if (std_it_test == std_c0.rend())
		testBool(ft_it_test == ft_c0.rend(), __FILE__, line);
	else
		testBool(ft_it_test->first == std_it_test->first && ft_it_test->second == std_it_test->second, __FILE__, line);
	if (std_it_test != std_c0.rbegin())
		testBool(ft_it_test != ft_c0.rbegin(), __FILE__, line);
}

void
test_const_iterator_values_pointed(
				ft::map<int, int>::const_reverse_iterator ft_it_test ,
				const ft::map<int, int>& ft_c0 ,
				std::map<int, int>::const_reverse_iterator std_it_test ,
				const std::map<int, int>& std_c0 , int line)	{

	if (std_it_test == std_c0.rend())
		testBool(ft_it_test == ft_c0.rend(), __FILE__, line);
	else
		testBool(ft_it_test->first == std_it_test->first && ft_it_test->second == std_it_test->second, __FILE__, line);
	if (std_it_test != std_c0.rbegin())
		testBool(ft_it_test != ft_c0.rbegin(), __FILE__, line);
}

void
test_constReverseIterator( ft::map<int, int> const & ft_c0, std::map<int, int> const & std_c0 )	{

	std::cout << HEADER_TITLE << "Test const version of reverse iterator" << RESET_COLOR << std::endl;
	std::cout << SUBTITLE << "If compile fails, const version of function are missing" << RESET_COLOR << std::endl;
	std::map<int, int>::const_reverse_iterator	std_it = std_c0.rbegin();
	std::map<int, int>::const_reverse_iterator	std_itend = std_c0.rend()--;

	ft::map<int, int>::const_reverse_iterator		ft_it = ft_c0.rbegin(); //  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
	ft::map<int, int>::const_reverse_iterator		ft_itend = ft_c0.rend()--; //  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !

	test_const_iterator_values_pointed(ft_it, ft_c0, std_it, std_c0, __LINE__);
	test_const_iterator_values_pointed(ft_itend, ft_c0, std_itend, std_c0, __LINE__);

	ft_it++;
	std_it++;
	test_const_iterator_values_pointed(ft_it, ft_c0, std_it, std_c0, __LINE__);
	++ft_it;
	++std_it;
	test_const_iterator_values_pointed(ft_it, ft_c0, std_it, std_c0, __LINE__);
	ft_it--;
	std_it--;
	test_const_iterator_values_pointed(ft_it, ft_c0, std_it, std_c0, __LINE__);
	--ft_it;
	--std_it;
	test_const_iterator_values_pointed(ft_it, ft_c0, std_it, std_c0, __LINE__);

}

int
test_map_reverseIterator( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;

	{
		size_t			valgrind_factor = (VALGRIND_MODE == true) ? 100 : 1;
		size_t			testSize = 5000 / valgrind_factor;
		int findKey = 42;
		std::cout << HEADER_TITLE << "[ Create a map of " << testSize << " int key and int mapped value ]" << RESET_COLOR << std::endl;

		std::vector<ft::pair<int, int> >	ft_val_0(testSize);
		std::vector<std::pair<int, int> >	std_val_0(testSize);
		srand(time(NULL));
		for (size_t i = 0; i < testSize; i++)	{
			if (i == testSize / 2)
				findKey = i;
			ft_val_0[i] = ft::make_pair(i*2, i);
			std_val_0[i] = std::make_pair(i*2, i);
		}

		std::map<int, int>	std_c0(std_val_0.begin(), std_val_0.end());
		ft::map<int, int>	ft_c0(ft_val_0.begin(), ft_val_0.end());
		testMap(ft_c0, std_c0, NOPRINT);

		ft::map<int, int>::reverse_iterator			ft_it = ft_c0.rbegin();
		ft::map<int, int>::reverse_iterator			ft_it2 = --ft_c0.rend();
		ft::map<int, int>::reverse_iterator			ft_it3 = ++ft_c0.rbegin();
		ft::map<int, int>::reverse_iterator			ft_itend = ft_c0.rend();

		std::map<int, int>::reverse_iterator		std_it = std_c0.rbegin();
		std::map<int, int>::reverse_iterator		std_it2 = --std_c0.rend();
		std::map<int, int>::reverse_iterator		std_it3 = ++std_c0.rbegin();
		std::map<int, int>::reverse_iterator		std_itend = std_c0.rend();

		test_iterator_values_pointed(ft_it, ft_c0, std_it, std_c0, __LINE__);
		test_iterator_values_pointed(ft_itend, ft_c0, std_itend, std_c0, __LINE__);
		test_iterator_values_pointed(ft_it2, ft_c0, std_it2, std_c0, __LINE__);
		test_iterator_values_pointed(ft_it3, ft_c0, std_it3, std_c0, __LINE__);

		std::cout << HEADER_TITLE << "[ TEST REVERSE ITERATOR ARITHMETIC ]" << RESET_COLOR << std::endl;

		ft_it++;
		std_it++;
		test_iterator_values_pointed(ft_it, ft_c0, std_it, std_c0, __LINE__);
		++ft_it;
		++std_it;
		test_iterator_values_pointed(ft_it, ft_c0, std_it, std_c0, __LINE__);
		ft_it--;
		std_it--;
		test_iterator_values_pointed(ft_it, ft_c0, std_it, std_c0, __LINE__);
		--ft_it;
		--std_it;
		test_iterator_values_pointed(ft_it, ft_c0, std_it, std_c0, __LINE__);

		test_iterator_values_pointed(ft_itend, ft_c0, std_itend, std_c0, __LINE__);
		ft_itend--;
		std_itend--;
		test_iterator_values_pointed(ft_itend, ft_c0, std_itend, std_c0, __LINE__);
		--ft_itend;
		--std_itend;
		test_iterator_values_pointed(ft_itend, ft_c0, std_itend, std_c0, __LINE__);
		ft_itend++;
		std_itend++;
		test_iterator_values_pointed(ft_itend, ft_c0, std_itend, std_c0, __LINE__);
		++ft_itend;
		++std_itend;
		test_iterator_values_pointed(ft_itend, ft_c0, std_itend, std_c0, __LINE__);

		test_constReverseIterator(ft_c0, std_c0);

		std::cout << HEADER_TITLE << "[ TEST BASE MEMBER FUNCTION ]" << RESET_COLOR << std::endl;
		{
			std_it = ++std_c0.rbegin();
			ft_it = ++ft_c0.rbegin();
			std::map<int, int>::iterator		std_base = std_it.base();
			ft::map<int, int>::iterator			ft_base = ft_it.base();
			testBool( ft_base->first == std_base->first
				&&	ft_base->second == std_base->second, __FILE__, __LINE__);
		}
		{
			std_it = --std_c0.rend();
			ft_it = --ft_c0.rend();
			std::map<int, int>::iterator		std_base = std_it.base();
			ft::map<int, int>::iterator			ft_base = ft_it.base();
			testBool( ft_base->first == std_base->first
				&&	ft_base->second == std_base->second, __FILE__, __LINE__);
		}
	}
	return (0);
}
