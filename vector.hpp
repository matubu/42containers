/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:36:15 by mberger-          #+#    #+#             */
/*   Updated: 2022/01/16 18:34:20 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm> // min
#include <memory> // allocator
#include <exception> // error
#include <cstring> // memmove
#include "iterator.hpp" // reverse_iterator
#include "utils.hpp" // is_integral enable_if

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
			typedef typename ft::random_access_iterator<T>         iterator;
			typedef typename ft::random_access_iterator<T>         const_iterator;
			typedef typename ft::reverse_iterator<iterator>        reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>  const_reverse_iterator;
			typedef typename std::ptrdiff_t                        difference_type;
			typedef typename std::size_t                           size_type;
		private:
			// Data
			Alloc	allocator;
			pointer	start;
			pointer	curr;
			pointer	last;
		public:
			// Constructor
			vector(void) : allocator(), start(NULL), curr(NULL), last(NULL) {}
			explicit vector(const Alloc &alloc) : allocator(alloc), start(NULL), curr(NULL), last(NULL) {}
			explicit vector(size_type count, const T &value = T(), const Alloc &alloc = Alloc())
				: allocator(alloc), start(NULL), curr(NULL), last(NULL) {
				reserve(count);
				while (count--)
					*curr++ = value;
			}
			template <class Iter>
			vector(Iter first, Iter last, const Alloc &alloc = Alloc(),
					typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = ft_nullptr)
				: allocator(alloc), start(NULL), curr(NULL), last(NULL) {
				size_type count = last - first;
				reserve(count);
				while (count--)
					*curr++ = *first++;
			}
			vector(const vector &other) : allocator(other.allocator), start(NULL), curr(NULL), last(NULL) {
				size_type n = other.size();
				reserve(n);
				memmove(start, other.start, n * sizeof(T));
				curr = start + n;
			}
	
			// Destructor
			~vector(void) { allocator.deallocate(start, capacity()); }

			// Member functions
			vector	&operator=(const vector &other) {
				size_type n = other.size();
				curr = start;
				reserve(n);
				memmove(start, other.start, n * sizeof(T));
				curr = start + n;
				return (*this);
			}

			void assign(size_type count, const T &value) {
				curr = start;
				reserve(count);
				while (count--)
					*curr++ = value;
			}
			template <class Iter>
			void assign(Iter first, Iter last,
					typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = ft_nullptr) {
				curr = start;
				if (first > last) std::swap(first, last);
				reserve(last - first);
				while (first < last)
					push_back(*first++);
			}
			allocator_type	get_allocator() const { return (allocator); };

			// Access
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

			// Iterators
			iterator				begin() { return (iterator(start)); }
			const_iterator			begin() const { return (iterator(start)); }
			iterator				end() { return (iterator(curr)); }
			const_reverse_iterator	end() const { return (iterator(curr)); }
			reverse_iterator		rbegin() { return (reverse_iterator(curr)); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(curr)); }
			reverse_iterator		rend() { return (reverse_iterator(start)); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(start)); }

			// Capacity
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
				last = (start = allocator.allocate(new_cap)) + new_cap;
				curr = start + n;
				memmove(start, old, n * sizeof(T));
				allocator.deallocate(old, cap);
			}
			size_type	capacity() const { return (last - start); }

			// Modifiers
			void		clear() { curr = start; }
			iterator	insert(iterator pos, const T& value) {
				size_type	idx = &(*pos) - start;
				if (unlikely(size() >= capacity()))
					reserve(capacity() << 1 | !capacity());
				memmove(start + idx + 1, start + idx, (size() - idx) * sizeof(T));
				curr++;
				start[idx] = value;
				return (iterator(start + idx));
			}
			void insert(iterator pos, size_type count, const T& value) {
				size_type	idx = &(*pos) - start;
				if (unlikely(size() + count > capacity()))
					reserve(size() + count <= capacity() << 1 ? capacity() << 1 : size() + count);
				memmove(start + idx + count, start + idx, ((size() - idx) * sizeof(T)));
				while (count--)
					*curr++ = value;
			}
			template <class Iter>
			void insert(iterator pos, Iter first, Iter last,
					typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = ft_nullptr) {
				size_type	idx = &(*pos) - start;
				size_type	count = last - first;
				if (unlikely(size() + count > capacity()))
					reserve(size() + count <= capacity() << 1 ? capacity() << 1 : size() + count);
				memmove(start + idx + count, start + idx, ((size() - idx) * sizeof(T)));
				while (count--)
					*curr++ = *first++;
			}
			iterator erase(iterator pos)
			{ memmove(&(*pos), &(*pos) + 1, (curr-- - &(*pos))); return (pos); }
			iterator erase(iterator first, iterator last) {
				memmove(&(*first), &(*last), (curr - &(*last)) * sizeof(T));
				curr -= &(*last) - &(*first);
				return (first);
			};
			void		push_back(const T &value) {
				if (unlikely(size() >= capacity()))
					reserve(capacity() << 1 | !capacity());
				*curr++ = value;
			}
			void		pop_back() { curr--; }
			void		resize(size_type count, T value = T()) {
				if (likely(size() >= count)) { curr = start + count; return ; }
				reserve(count);
				while (size() < count) *curr++ = value;
			}
			void		swap(ft::vector<T,Alloc> &other) {
				pointer	tmp = start;
				start = other.start;
				other.start = tmp;

				tmp = curr;
				curr = other.curr;
				other.curr = tmp;

				tmp = last;
				last = other.last;
				other.last = tmp;
			};
	};

	// Operators
	template <class T, class Alloc>
	bool operator==(const ft::vector<T,Alloc> &lhs, const ft::vector<T,Alloc> &rhs) {
		if (lhs.size() != rhs.size())
			return (0);
		for (int i = lhs.size(); i--;)
			if (lhs[i] != rhs[i])
				return (0);
		return (1);
	}

	template <class T, class Alloc>
	bool operator!=(const ft::vector<T,Alloc> &lhs, const ft::vector<T,Alloc> &rhs)
	{ return (!(lhs == rhs)); }

	template <class T, class Alloc>
	bool operator<(const ft::vector<T,Alloc> &lhs, const ft::vector<T,Alloc> &rhs) {
		for (int i = 0, size = std::min(lhs.size(), rhs.size()); i < size; i++)
			if (lhs[i] < rhs[i])
				return (1);
		return (lhs.size() < rhs.size());
	}

	template <class T, class Alloc>
	bool operator>=(const ft::vector<T,Alloc> &lhs, const ft::vector<T,Alloc> &rhs)
	{ return (!(lhs < rhs)); }

	template <class T, class Alloc>
	bool operator>(const ft::vector<T,Alloc> &lhs, const ft::vector<T,Alloc> &rhs) {
		for (int i = 0, size = std::min(lhs.size(), rhs.size()); i < size; i++)
			if (lhs[i] > rhs[i])
				return (1);
		return (lhs.size() > rhs.size());
	}

	template <class T, class Alloc>
	bool operator<=(const ft::vector<T,Alloc> &lhs, const ft::vector<T,Alloc> &rhs)
	{ return (!(lhs > rhs)); }

	template <class T, class Alloc>
	void swap(ft::vector<T,Alloc> &lhs, ft::vector<T,Alloc> &rhs) { lhs.swap(rhs); }
}