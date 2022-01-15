/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:36:15 by mberger-          #+#    #+#             */
/*   Updated: 2022/01/15 13:45:02 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory> // std::allocator
#include <exception> // std::error
#include <cstring> // memcpy

#define likely(x)      __builtin_expect(x, 1)
#define unlikely(x)    __builtin_expect(x, 0)

namespace ft {
	template <class T, class Alloc = std::allocator<T> >
	class vector {
		public:
			//Types
			typedef T                                              value_type;
			typedef Alloc                                          allocator_type;
			typedef typename Alloc::reference                      reference;
			typedef typename Alloc::const_reference                const_reference;
			typedef typename Alloc::pointer                        pointer;
			typedef typename Alloc::const_pointer                  const_pointer;
			//typedef typename             iterator;
			//typedef typename             const_iterator;
			//typedef typename std::reverse_iterator<iterator>       reverse_iterator
			//typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator
			typedef typename std::ptrdiff_t                        difference_type;
			typedef typename std::size_t                           size_type;
		protected:
			//Data
			Alloc	allocator;
			pointer	start;
			pointer	curr;
			pointer	end;
		public:
			//Constructor
			vector(void) : allocator(), start(NULL), curr(NULL), end(NULL) {}
			explicit vector(const Alloc &alloc) : allocator(alloc), start(NULL), curr(NULL), end(NULL) {}
			explicit vector(size_type count, const T &value = T(), const Alloc &alloc = Alloc())
				: allocator(alloc), start(NULL), curr(NULL), end(NULL) {
				reserve(count);
				curr = start + count;
				while (count--)
					start[count]  = value;
			}
			//template<class InputIt>
			//vector(InputIt first, InputIt last,
			//		const Alloc &alloc = Alloc()) {}
			vector(const vector &other) : allocator(other.allocator), start(NULL), curr(NULL), end(NULL) {
				size_type n = other.size();
				reserve(n);
				memcpy(start, other.start, n * sizeof(T));
				curr = start + n;
			}
	
			//Destructor
			~vector(void) { allocator.deallocate(start, capacity()); }

			vector	&operator=(const vector &other)
			{
				size_type n = other.size();
				curr = start;
				reserve(n);
				memcpy(start, other.start, n * sizeof(T));
				curr = start + n;
				return (*this);
			}

			//void assign( size_type count, const T& value );
			//template< class InputIt >
			//void assign( InputIt first, InputIt last );

			allocator_type	get_allocator() const { return (allocator); };

			//Access
			reference		operator[](size_type pos)       { return (start[pos]); }
			const_reference	operator[](size_type pos) const { return (start[pos]); }
			reference		at(size_type n)                 { if (n >= size()) throw std::out_of_range("Out of range"); return (start[n]); }
			const_reference	at(size_type n) const           { if (n >= size()) throw std::out_of_range("Out of range"); return (start[n]); }
			reference		front()                         { return (start[0]); };
			const_reference	front() const                   { return (start[0]); };
			reference		back()                          { return (curr[-1]); };
			const_reference	back() const                    { return (curr[-1]); };
			T				*data()                         { return (start); }
			const T	*data() const                           { return (start); }

			//Capacity
			bool		empty() const { return (curr == start); }
			size_type	size() const { return (curr - start); }
			size_type	max_size() const { return (allocator.max_size()); }
			void		reserve(size_type new_cap) {
				if (unlikely(new_cap <= capacity()))
					return ;
				if (unlikely(new_cap > max_size()))
					throw std::length_error("'n' exceeds maximum supported size");
				size_type	n = size(), cap = capacity();
				pointer		old = start;
				end = (start = allocator.allocate(new_cap)) + new_cap;
				curr = start + n;
				memcpy(start, old, n * sizeof(T));
				allocator.deallocate(old, cap);
			}
			size_type	capacity() const { return (end - start); }

			//Modifiers
			void		clear() { curr = start; }
			//iterator	insert(iterator pos, const T& value) {}
			void		push_back(const T &value) {
				if (unlikely(size() >= capacity()))
					reserve(capacity() << 1 | !capacity());
				*curr++ = value;
			}
			void		pop_back() { curr--; }
			void		resize(size_type count, T value = T())
			{
				if (likely(size() >= count)) { curr = start + count; return ; }
				reserve(count);
				while (size() < count) push_back(value);
			}
			void		swap(vector &other) {
				std::swap(start, other.start);
				std::swap(curr, other.curr);
				std::swap(end, other.end);
			};
	};
}

template<class T, class Alloc>
bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return (0);
	for (int i = lhs.size(); i--;)
		if (lhs[i] != rhs[i])
			return (0);
	return (1);
}
template<class T, class Alloc>
bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{ return (!(lhs == rhs)); }

template<class T, class Alloc>
bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	for (int i = 0, size = std::min(lhs.size(), rhs.size()); i < size; i++)
		if (lhs[i] < rhs[i])
			return (1);
	return (lhs.size() < rhs.size());
}

template<class T, class Alloc>
bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{ return (!(lhs < rhs)); }

template<class T, class Alloc>
bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	for (int i = 0, size = std::min(lhs.size(), rhs.size()); i < size; i++)
		if (lhs[i] > rhs[i])
			return (1);
	return (lhs.size() > rhs.size());
}

template<class T, class Alloc>
bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{ return (!(lhs > rhs)); }
