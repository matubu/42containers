/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matubu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:34:45 by matubu            #+#    #+#             */
/*   Updated: 2022/01/31 16:50:33 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace ft {
	template <class T, class Container = ft::vector<T> >
	class stack {
		public:
			typedef typename Container::value_type  value_type;
			typedef typename Container::reference reference;
			typedef typename Container::const_reference const_reference;
			typedef typename Container::size_type size_type;
			typedef Container container_type;
		
		protected:
			Container c;
		
		public:
			explicit stack(const Container &_c = Container()) : c(_c) {}
			stack(const stack &other) : c(other.c) {}

			~stack() {}

			stack &operator=(const stack& other) { c = other.c; };
		
			reference         top()             { return (c.back()); }
			const_reference   top() const       { return (c.back()); }
			bool empty() const                  { return (c.empty()); }
			size_type size()  const             { return (c.size()); }
			void push(const value_type &x)      { c.push_back(x); }
			void pop()                          { c.pop_back(); }

			template <class _T, class _Container>
			friend bool operator==(const ft::stack<_T,_Container> &lhs, const ft::stack<_T,_Container> &rhs)
			{ return lhs.c == rhs.c; }

			template <class _T, class _Container>
			friend bool operator!=(const ft::stack<_T,_Container> &lhs, const ft::stack<_T,_Container> &rhs)
			{ return lhs.c != rhs.c; }

			template <class _T, class _Container>
			friend bool operator<(const ft::stack<_T,_Container> &lhs, const ft::stack<_T,_Container> &rhs)
			{ return lhs.c < rhs.c; }

			template <class _T, class _Container>
			friend bool operator<=(const ft::stack<_T,_Container> &lhs, const ft::stack<_T,_Container> &rhs)
			{ return lhs.c <= rhs.c; }

			template <class _T, class _Container>
			friend bool operator>(const ft::stack<_T,_Container> &lhs, const ft::stack<_T,_Container> &rhs)
			{ return lhs.c > rhs.c; }

			template <class _T, class _Container>
			friend bool operator>=(const ft::stack<_T,_Container> &lhs, const ft::stack<_T,_Container> &rhs)
			{ return lhs.c >= rhs.c; }
	};
}
