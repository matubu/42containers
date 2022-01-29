/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:36:15 by mberger-          #+#    #+#             */
/*   Updated: 2022/01/29 20:51:02 by matubu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory> // allocator
#include <stdexcept> // error
#include "iterator.hpp" // reverse_iterator
#include "utils.hpp" // is_integral enable_if

#define ALLOC \
	size_type	cap = capacity(); \
	pointer		old = NULL;
#define CLEANUP \
	if (old) allocator.deallocate(old, cap);
#define FOR(count) \
	if (size() + count > capacity()) \
		old = _realloc(size() + count <= capacity() << 1 ? capacity() << 1 : size() + count);
#define SET(ptr, val) allocator.construct(ptr, val);
#define CPY(a, b, n) {int pn = n; T *pa = a; T *pb = b; while (pn--) SET(pa++, *pb++);}
#define RCPY(a, b, n) {int pn = n; T *pa = a; T *pb = b; while (pn--) SET(pa + pn, pb[pn]);}
#define NCPY(a, val, n) {int pn = n; T *pa = a; while (pn--) SET(pa++, val);}
#define MIN(a, b) (a < b) ? a : b

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

			pointer		_realloc(size_type new_cap) {
				if (new_cap <= capacity())
					return (NULL);
				if (new_cap > max_size())
					throw std::length_error("'n' exceeds maximum supported size");
				size_type	n = size();
				pointer		old = start;
				last = (start = allocator.allocate(new_cap)) + new_cap;
				curr = start + n;
				CPY(start, old, n);
				return (old);
			}
		public:
			// Constructor
			vector(void) : allocator(), start(NULL), curr(NULL), last(NULL) {}
			explicit vector(const Alloc &alloc) : allocator(alloc), start(NULL), curr(NULL), last(NULL) {}
			explicit vector(size_type count, const T &value = T(), const Alloc &alloc = Alloc())
				: allocator(alloc), start(NULL), curr(NULL), last(NULL) {
				reserve(count);
				NCPY(curr, value, count);
				curr += count;
			}
			template <class Iter>
			vector(Iter first, Iter last, const Alloc &alloc = Alloc(),
					typename ft::enable_if<!ft::is_integral<Iter>::value>::type * = ft_nullptr_t())
				: allocator(alloc), start(NULL), curr(NULL), last(NULL) {
				difference_type count = last - first;
				reserve(count);
				CPY(curr, first, count);
				curr += count;
			}
			vector(const vector &other) : allocator(other.allocator), start(NULL), curr(NULL), last(NULL) {
				size_type n = other.size();
				reserve(n);
				CPY(start, other.start, n);
				curr = start + n;
			}
	
			// Destructor
			~vector(void) { allocator.deallocate(start, capacity()); }

			// Member functions
			vector	&operator=(const vector &other) {
				size_type n = other.size();
				curr = start;
				reserve(n);
				CPY(start, other.start, n);
				curr = start + n;
				return (*this);
			}

			void assign(size_type count, const T &value) {
				curr = start;
				reserve(count);
				NCPY(start, value, count);
				curr = start + count;
			}
			template <class Iter>
			void assign(Iter first, Iter last,
					typename ft::enable_if<!ft::is_integral<Iter>::value>::type * = ft_nullptr_t()) {
				curr = start;
				size_type n = last - first;
				reserve(n);
				CPY(start, &*first, n);
				curr = start + n;
			}
			allocator_type	get_allocator() const { return (allocator); };

			// Access
			reference		operator[](size_type pos)       { return (start[pos]); }
			const_reference	operator[](size_type pos) const { return (start[pos]); }
			reference		at(size_type n)                 { if (n >= size()) throw std::out_of_range("Out of range"); return (start[n]); }
			const_reference	at(size_type n) const           { if (n >= size()) throw std::out_of_range("Out of range"); return (start[n]); }
			reference		front()                         { return (*start); };
			const_reference	front() const                   { return (*start); };
			reference		back()                          { return (curr[-1]); };
			const_reference	back() const                    { return (curr[-1]); };
			T				*data()                         { return (start); }
			const T			*data() const                   { return (start); }

			// Iterators
			iterator				begin() { return (iterator(start)); }
			const_iterator			begin() const { return (iterator(start)); }
			iterator				end() { return (iterator(curr)); }
			const_iterator			end() const { return (iterator(curr)); }
			reverse_iterator		rbegin() { return (reverse_iterator(curr)); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(curr)); }
			reverse_iterator		rend() { return (reverse_iterator(start)); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(start)); }

			// Capacity
			bool		empty() const { return (curr == start); }
			size_type	size() const { return (curr - start); }
			size_type	max_size() const { return (allocator.max_size()); }
			void		reserve(size_type new_cap) {
				ALLOC;
				old = _realloc(new_cap);
				CLEANUP;
			}
			size_type	capacity() const { return (last - start); }

			// Modifiers
			void		clear() { curr = start; }
			iterator	insert(iterator pos, const T& value) {
				size_type	idx = &*pos - start;
				ALLOC FOR(1);
				if (idx < size()) RCPY(start + idx + 1, start + idx, size() - idx);
				curr++;
				start[idx] = value;
				CLEANUP;
				return (iterator(start + idx));
			}
			void insert(iterator pos, size_type count, const T& value) {
				size_type	idx = &*pos - start;
				ALLOC FOR(count);
				if (idx < size()) RCPY(start + idx + count, start + idx, size() - idx);
				curr += count;
				NCPY(start + idx, value, count);
				CLEANUP;
			}
			// https://stackoverflow.com/questions/14791984/appending-stdvector-to-itself-undefined-behavior
			template <class Iter>
			void insert(iterator pos, Iter first, Iter last,
					typename ft::enable_if<!ft::is_integral<Iter>::value>::type * = ft_nullptr_t()) {
				size_type	idx = &*pos - start;
				size_type	count = last - first;
				ALLOC FOR(count);
				if (idx < size()) RCPY(start + idx + count, start + idx, size() - idx);
				curr += count;
				CPY(start + idx, &*first, count);
				CLEANUP;
			}
			iterator erase(iterator pos)
			{ CPY(&*pos, &*pos + 1, --curr - &*pos); return (pos); }
			iterator erase(iterator first, iterator last) {
				CPY(&*first, &*last, curr - &*last);
				curr -= &*last - &*first;
				return (first);
			};
			void		push_back(const T &value) {
				ALLOC FOR(1);
				SET(curr++, value);
				CLEANUP;
			}
			void		pop_back() { curr--; }
			void		resize(size_type count, T value = T()) {
				if (size() >= count) { curr = start + count; return ; }
				reserve(count);
				NCPY(curr, value, count - size());
				curr = start + count;
			}
			void		swap(ft::vector<T,Alloc> &other) {
				std::swap(start, other.start);
				std::swap(curr, other.curr);
				std::swap(last, other.last);
			};
	};

	// Operators
	template <class T, class Alloc>
	bool operator==(const ft::vector<T,Alloc> &lhs, const ft::vector<T,Alloc> &rhs) {
		if (lhs.size() != rhs.size()) return (0);
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
		for (int i = 0, size = MIN(lhs.size(), rhs.size()); i < size; i++)
			if (lhs[i] < rhs[i])
				return (1);
		return (lhs.size() < rhs.size());
	}
	template <class T, class Alloc>
	bool operator>=(const ft::vector<T,Alloc> &lhs, const ft::vector<T,Alloc> &rhs)
	{ return (!(lhs < rhs)); }

	template <class T, class Alloc>
	bool operator>(const ft::vector<T,Alloc> &lhs, const ft::vector<T,Alloc> &rhs) {
		for (int i = 0, size = MIN(lhs.size(), rhs.size()); i < size; i++)
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
