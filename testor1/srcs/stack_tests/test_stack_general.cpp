/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack_general.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:56:55 by bvalette          #+#    #+#             */
/*   Updated: 2021/08/24 12:30:27 by etakouer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_stack.hpp"

static size_t	valgrind_factor = (VALGRIND_MODE == true) ? 10000 : 1;
static size_t	testSize = 2000000 / valgrind_factor;

template<typename T1, typename T2>
void
testStack( const T1& ft_c0, const T2& std_c0, int _line) {

		testBool(ft_c0.empty() == std_c0.empty()
			&& ft_c0.size() == std_c0.size(), __FILE__, _line);

		if (std_c0.empty() == false)
			testBool(ft_c0.top() == std_c0.top(), __FILE__, _line);
}

template<typename T1, typename T2>
void
test_top( T1& ft_c0, T2& std_c0)	{

		if (std_c0.empty() == false)
			testBool(ft_c0.top() == std_c0.top(), __FILE__, __LINE__);
}

template<typename T1, typename T2>
void
test_push_pop( T1& ft_c0, T2& std_c0)	{

	testStack<T1, T2>(ft_c0, std_c0, __LINE__);
	std::cout << SUBTITLE << "Push() " << testSize << " values on empty container" << RESET_COLOR << std::endl;
	for (size_t i = 0; i < testSize; i++)	{
		int val = rand();
		std_c0.push(val);
		ft_c0.push(val);
		if (ft_c0.top() != std_c0.top())
			testBool(false, __FILE__, __LINE__, i);
	}
	testStack(ft_c0, std_c0, __LINE__);
	std::cout << SUBTITLE << "pop() until the stack is empty" << RESET_COLOR << std::endl;
	for (size_t i = 0; std_c0.empty() == false; i++)	{
		if (ft_c0.top() != std_c0.top())
			testBool(false, __FILE__, __LINE__, i);
		std_c0.pop();
		ft_c0.pop();
	}
	testStack(ft_c0, std_c0, __LINE__);
	std::cout << SUBTITLE << "push and pop() values" << RESET_COLOR << std::endl;
	for (size_t i = 0; i < testSize; i++)	{
		if (std_c0.empty() == false && ft_c0.top() != std_c0.top())
			testBool(false, __FILE__, __LINE__, i);
		int val = rand();
		if ( val % 3 == 0 && std_c0.empty() == false )	{
			std_c0.pop();
			ft_c0.pop();
		}
		else	{
			std_c0.push(val);
			ft_c0.push(val);
		}
	}
	testStack(ft_c0, std_c0, __LINE__);
}

int
test_stack_general( void )	{


	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << HEADER_TITLE << "Instanciation with no arguments" << RESET_COLOR << std::endl;
		ft::stack<int>		ft_c0;
		std::stack<int>		std_c0;

		std::cout << HEADER_TITLE << "Empty() on empty container" << RESET_COLOR << std::endl;
		testBool(ft_c0.empty() == std_c0.empty(), __FILE__, __LINE__);
		std::cout << HEADER_TITLE << "Size() on empty container" << RESET_COLOR << std::endl;
		testBool(ft_c0.size() == std_c0.size(), __FILE__, __LINE__);
	}
	{
		std::cout << HEADER_TITLE << "Instanciation arguments for deque container" << RESET_COLOR << std::endl;
		ft::stack<int, std::deque<int>>		ft_c0(std::deque<int>(10, 42));
		std::stack<int>		std_c0(std::deque<int>(10, 42));

		std::cout << HEADER_TITLE << "Empty() on non empty container" << RESET_COLOR << std::endl;
		testBool(ft_c0.empty() == std_c0.empty(), __FILE__, __LINE__);
		std::cout << HEADER_TITLE << "Size() on non empty container" << RESET_COLOR << std::endl;
		testBool(ft_c0.size() == std_c0.size(), __FILE__, __LINE__);
	}
	{
		std::cout << HEADER_TITLE << "Instanciation arguments for a list container" << RESET_COLOR << std::endl;
		ft::stack<int, std::list<int> >		ft_c0(std::list<int>(10, 42));
		std::stack<int, std::list<int> >		std_c0(std::list<int>(10, 42));

		std::cout << HEADER_TITLE << "Empty() on non empty container" << RESET_COLOR << std::endl;
		testBool(ft_c0.empty() == std_c0.empty(), __FILE__, __LINE__);
		std::cout << HEADER_TITLE << "Size() on non empty container" << RESET_COLOR << std::endl;
		testBool(ft_c0.size() == std_c0.size(), __FILE__, __LINE__);
	}

	{
		std::cout << HEADER_TITLE << "Instanciation arguments for list container" << RESET_COLOR << std::endl;
		ft::stack<int, std::list<int> >		ft_c0(std::list<int>(10, 42));
		std::stack<int, std::list<int> >		std_c0(std::list<int>(10, 42));
		ft::stack<int, std::list<int> >		ft_c1(std::list<int>(10, 21));
		std::stack<int, std::list<int> >		std_c1(std::list<int>(10, 21));
		ft::stack<int, std::list<int> >		ft_c2(std::list<int>(11, 21));
		std::stack<int, std::list<int> >		std_c2(std::list<int>(11, 21));

		std::cout << HEADER_TITLE << "Relational Operators" << RESET_COLOR << std::endl;
		std::cout << SUBTITLE<< "operator==" << RESET_COLOR << std::endl;
		testBool(ft_c0 == ft_c0 && std_c0 == std_c0, __FILE__, __LINE__);
		std::cout << SUBTITLE<< "operator!=" << RESET_COLOR << std::endl;
		testBool(ft_c0 != ft_c1 && std_c0 != std_c1, __FILE__, __LINE__);

		std::cout << SUBTITLE<< "operator<" << RESET_COLOR << std::endl;
		testBool(ft_c1 < ft_c0 && std_c1 < std_c0, __FILE__, __LINE__);
		std::cout << SUBTITLE<< "operator<=" << RESET_COLOR << std::endl;
		testBool(ft_c1 <= ft_c2 && std_c1 <= std_c2, __FILE__, __LINE__);
		std::cout << SUBTITLE<< "operator>" << RESET_COLOR << std::endl;
		testBool(ft_c0 > ft_c2 && std_c0 > std_c2, __FILE__, __LINE__);
		std::cout << SUBTITLE<< "operator>=" << RESET_COLOR << std::endl;
		testBool(ft_c1 >= ft_c1 && std_c1 >= std_c1, __FILE__, __LINE__);
	}
	{
		std::cout << HEADER_TITLE << "Push/Pop on a stack made of DEFAULT container" << RESET_COLOR << std::endl;
		ft::stack<int> 		ft_c0;
		std::stack<int> 	std_c0;
		test_push_pop(ft_c0, std_c0);
	}
	{
		std::cout << HEADER_TITLE << "Push/Pop on a stack made of LIST container" << RESET_COLOR << std::endl;
		ft::stack<int, std::list<int> > 		ft_c0(std::list<int>(10, 42));
		std::stack<int, std::list<int> > 	std_c0(std::list<int>(10, 42));
		test_push_pop(ft_c0, std_c0);
	}
	{
		testSize = testSize / 1000;
		std::cout << HEADER_TITLE << "Push/Pop on a stack made of VECTOR container" << RESET_COLOR << std::endl;
		ft::stack<int, std::vector<int> > 		ft_c0(std::vector<int>(10, 42));
		std::stack<int, std::vector<int> > 	std_c0(std::vector<int>(10, 42));
		test_push_pop(ft_c0, std_c0);

		std::cout << HEADER_TITLE << "Top() with non const value" << RESET_COLOR << std::endl;
		test_top(ft_c0, std_c0);
	}

	return (0);

}
