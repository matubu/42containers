/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matubu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:34:45 by matubu            #+#    #+#             */
/*   Updated: 2022/01/15 18:58:39 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace ft {
	template <class T, class Container = ft::vector<T> >
	class stack {
	public:
		using value_type      = typename Container::value_type;
		using reference       = typename Container::reference;
		using const_reference = typename Container::const_reference;
		using size_type       = typename Container::size_type;
		using container_type  = Container;
	
	protected:
		Container c;
	
	public:
		stack() : stack(Container()) {}
		explicit stack(const Container&);
		explicit stack(Container&&);
		//template <class InputIt> stack(InputIt first, InputIt last);
		template <class Alloc> explicit stack(const Alloc&);
		template <class Alloc> stack(const Container&, const Alloc&);
		template <class Alloc> stack(Container&&, const Alloc&);
		template <class Alloc> stack(const stack&, const Alloc&);
		template <class Alloc> stack(stack&&, const Alloc&);
		template <class InputIt, class Alloc>
		//stack(InputIt first, InputIt last, const Alloc&);
	
		bool empty() const    { return c.empty(); }
		size_type size()  const             { return c.size(); }
		reference         top()             { return c.back(); }
		const_reference   top() const       { return c.back(); }
		void push(const value_type& x)      { c.push_back(x); }
		void push(value_type&& x)           { c.push_back(std::move(x)); }
		void pop()                          { c.pop_back(); }
	};
	
	template <class Container>
		stack(Container) -> stack<typename Container::value_type, Container>;
	
	//template <class InputIt>
	//	stack(InputIt, InputIt) -> stack</*iter-value-type*/<InputIt>>;
	
	template <class Container, class Allocator>
		stack(Container, Allocator) -> stack<typename Container::value_type, Container>;
	
	//template <class InputIt, class Allocator>
	//	stack(InputIt, InputIt, Allocator)
	//	-> stack</*iter-value-type*/<InputIt>, deque</*iter-value-type*/<InputIt>,
	//			Allocator>>;
	
	template <class T, class Container, class Alloc>
		struct uses_allocator<stack<T, Container>, Alloc>
			: uses_allocator<Container, Alloc>::type { };
}
