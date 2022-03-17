/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:36:15 by mberger-          #+#    #+#             */
/*   Updated: 2022/03/17 13:35:04 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp" // reverse_iterator
#include "utils.hpp" // is_integral enable_if

namespace ft {
	#define ALLOC \
		size_type	cap = capacity(); \
		pointer		old = NULL;
	#define CLEANUP if (old) allocator.deallocate(old, cap);
	#define FOR(count) \
		if (size() + count > capacity()) \
			old = _realloc(size() + count <= capacity() << 1 ? capacity() << 1 : size() + count);
	#define SET(ptr, val) allocator.construct(ptr, val);
	#define MIN(a, b) (a < b) ? a : b
	#define INIT(alloc) allocator(alloc), start(NULL), curr(NULL), last(NULL)

	template <class T, class Alloc = std::allocator<T> >
	class vector {
		public:
			//Types
			typedef T                                             value_type;
			typedef Alloc                                         allocator_type;
			typedef typename Alloc::reference                     reference;
			typedef typename Alloc::const_reference               const_reference;
			typedef typename Alloc::pointer                       pointer;
			typedef typename Alloc::const_pointer                 const_pointer;
			typedef typename ft::random_access_iterator<T>        iterator;
			typedef typename ft::random_access_iterator<const T>  const_iterator;
			typedef typename ft::reverse_iterator<iterator>       reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef typename std::ptrdiff_t                       difference_type;
			typedef typename std::size_t                          size_type;
		private:
			// Data
			Alloc	allocator;
			pointer	start;
			pointer	curr;
			pointer	last;

			pointer		_realloc(size_type new_cap) {
				if (new_cap > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				size_type	n = size();
				pointer		old = start;
				last = (start = allocator.allocate(new_cap)) + new_cap;
				curr = start + n;
				_cpy(start, old, n);
				return (old);
			}
			template <typename a_t, typename b_t> void _cpy(a_t a, b_t b, int n) { while (n--) SET(a++, *b++); }
			template <typename a_t, typename b_t> void _rcpy(a_t a, b_t b, int n) { while (n--) SET(a + n, b[n]); }
			template <typename a_t> void _ncpy(a_t a, const T &val, int n) { while (n--) SET(a++, val); }
		public:
			// Constructor
			vector(void) : INIT() {}
			explicit vector(const Alloc &alloc) : INIT(alloc) {}
			explicit vector(size_type count, const T &value = T(), const Alloc &alloc = Alloc())
					: INIT(alloc) {
				reserve(count);
				_ncpy(start, value, count);
				curr += count;
			}
			template <class Iter>
			vector(Iter first, Iter last, const Alloc &alloc = Alloc(),
					typename ft::enable_if<!ft::is_integral<Iter>::value>::type * = ft_nullptr_t())
					: INIT(alloc) {
				while (first != last)
				{
					push_back(*first);
					++first;
				}
			}
			vector(const vector &other) : INIT(other.allocator) {
				size_type n = other.size();
				reserve(n);
				_cpy(start, other.start, n);
				curr = start + n;
			}
	
			// Destructor
			~vector(void) { allocator.deallocate(start, capacity()); }

			// Member functions
			vector	&operator=(const vector &other) {
				size_type n = other.size();
				curr = start;
				reserve(n);
				_cpy(start, other.start, n);
				curr = start + n;
				return (*this);
			}
			void assign(size_type count, const T &value) {
				curr = start;
				reserve(count);
				_ncpy(start, value, count);
				curr = start + count;
			}
			template <class Iter>
			void assign(Iter first, Iter last,
					typename ft::enable_if<!ft::is_integral<Iter>::value>::type * = ft_nullptr_t()) {
				clear();
				while (first != last)
				{
					push_back(*first);
					++first;
				}
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
			const_iterator			begin() const { return (const_iterator(start)); }
			iterator				end() { return (iterator(curr)); }
			const_iterator			end() const { return (const_iterator(curr)); }
			reverse_iterator		rbegin() { return (reverse_iterator(curr)); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(curr)); }
			reverse_iterator		rend() { return (reverse_iterator(start)); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(start)); }

			// Capacity
			bool		empty() const { return (curr == start); }
			size_type	size() const { return (curr - start); }
			size_type	max_size() const { return (allocator.max_size()); }
			void		reserve(size_type new_cap) {
				if (new_cap <= capacity()) return ;
				ALLOC;
				old = _realloc(new_cap);
				CLEANUP;
			}
			size_type	capacity() const { return (last - start); }

			// Modifiers
			void		clear() { curr = start; }
			iterator	insert(iterator pos, const T &value) {
				size_type	idx = &*pos - start;
				ALLOC FOR(1);
				if (idx < size())
				{
					_rcpy(start + idx + 1, start + idx, size() - idx);
					SET(start + idx, value);
				}
				else
					SET(start + size(), value);
				curr++;
				CLEANUP;
				return (iterator(start + idx));
			}
			void insert(iterator pos, size_type count, const T &value) {
				size_type	idx = &*pos - start;
				ALLOC FOR(count);
				if (idx < size()) _rcpy(start + idx + count, start + idx, size() - idx);
				curr += count;
				_ncpy(start + idx, value, count);
				CLEANUP;
			}
			template <class Iter>
			void insert(iterator pos, Iter first, Iter last,
					typename ft::enable_if<!ft::is_integral<Iter>::value>::type * = ft_nullptr_t()) {
				size_type	idx = &*pos - start;
				size_type	count = 0;
				while (last-- != first)
					count++;
				ALLOC FOR(count);
				if (idx < size()) _rcpy(start + idx + count, start + idx, size() - idx);
				curr += count;
				_cpy(start + idx, first, count);
				CLEANUP;
			}
			iterator erase(iterator pos)
			{ _cpy(&*pos, &*pos + 1, --curr - &*pos); return (pos); }
			iterator erase(iterator first, iterator last) {
				_cpy(&*first, &*last, curr - &*last);
				curr -= &*last - &*first;
				return (first);
			};
			void		push_back(const T &value) {
				ALLOC FOR(1);
				SET(curr++, value);
				CLEANUP;
			}
			void		pop_back() { allocator.destroy(--curr); }
			void		resize(size_type count, T value = T()) {
				if (size() >= count) { curr = start + count; return ; }
				ALLOC
				if (count > capacity())
					old = _realloc(count <= capacity() << 1 ? capacity() << 1 : count);
				_ncpy(curr, value, count - size());
				curr = start + count;
				CLEANUP
			}
			void		swap(vector<T,Alloc> &other) {
				std::swap(start, other.start);
				std::swap(curr, other.curr);
				std::swap(last, other.last);
			}

			// Operators
			friend bool operator==(const vector &lhs, const vector &rhs) {
				if (lhs.size() != rhs.size()) return (0);
				for (int i = lhs.size(); i--;)
					if (lhs[i] != rhs[i])
						return (0);
				return (1);
			}
			friend bool operator!=(const vector &lhs, const vector &rhs)
			{ return (!(lhs == rhs)); }

			friend bool operator<(const vector &lhs, const vector &rhs) {
				for (int i = 0, size = MIN(lhs.size(), rhs.size()); i < size; i++)
					if (lhs[i] != rhs[i])
						return (lhs[i] < rhs[i]);
				return (lhs.size() < rhs.size());
			}
			friend bool operator>=(const vector &lhs, const vector &rhs)
			{ return (!(lhs < rhs)); }
			friend bool operator>(const vector &lhs, const vector &rhs)
			{ return (rhs < lhs); }
			friend bool operator<=(const vector &lhs, const vector &rhs)
			{ return (!(lhs > rhs)); }

			friend void swap(vector &lhs, vector &rhs) { lhs.swap(rhs); }
	};

}
