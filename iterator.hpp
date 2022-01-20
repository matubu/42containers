/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:38:23 by mberger-          #+#    #+#             */
/*   Updated: 2022/01/16 12:32:28 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {
	// Iterator traits
	template <class Iter>
	struct iterator_traits {
		typedef typename Iter::iterator_category iterator_category;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::difference_type difference_type;
		typedef difference_type distance_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
	};
	template <class T>
	struct iterator_traits<T*> {
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};
	
	template <class T>
	struct iterator_traits<const T*> {
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	// Iterator
	template <
		class Category,
		class T,
		class Distance = std::ptrdiff_t,
		class Pointer = T*,
		class Reference = T&
	>
	struct iterator {
		typedef Category  iterator_category;
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
	};

	// Random access iterator
	struct random_access_iterator_tag {};
	template <class T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category  iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type         value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type    difference_type;
			typedef T*                                                                           pointer;
			typedef T&                                                                           reference;
		private:
			pointer ptr;
		public:
			random_access_iterator() : ptr(NULL) {}
			random_access_iterator(const pointer ptr) : ptr(ptr) {}
			random_access_iterator(const random_access_iterator<T> &other) : ptr(other.ptr) {}
			random_access_iterator &operator=(const random_access_iterator<T> &other) { ptr = other.ptr; return (*this); }
			~random_access_iterator() {}

			bool	operator==(const random_access_iterator<T> &other) const { return (ptr == other.ptr); }
			bool	operator!=(const random_access_iterator<T> &other) const { return (ptr != other.ptr); }
			bool	operator<(const random_access_iterator<T> &other) const { return (ptr < other.ptr); }
			bool	operator>(const random_access_iterator<T> &other) const { return (ptr > other.ptr); }
			bool	operator<=(const random_access_iterator<T> &other) const { return (ptr <= other.ptr); }
			bool	operator>=(const random_access_iterator<T> &other) const { return (ptr >= other.ptr); }

			reference operator*() const { return (*ptr); }
			pointer   operator->() const { return (ptr); }
			reference operator[](difference_type n) const { return (ptr[n]); }

			random_access_iterator &operator++() { ptr++; return (*this); }
			random_access_iterator &operator--() { ptr--; return (*this); }
			random_access_iterator operator++(int) { random_access_iterator tmp(ptr); ++ptr; return (tmp); }
			random_access_iterator operator--(int) { random_access_iterator tmp(ptr); --ptr; return (tmp); }
			random_access_iterator operator+(difference_type n) const { return (random_access_iterator(ptr + n)); }
			random_access_iterator operator-(difference_type n) const { return (random_access_iterator(ptr - n)); }
			difference_type        operator-(random_access_iterator<T> &other) const { return (ptr - other.ptr); }
			random_access_iterator &operator+=(difference_type n) { ptr += n; return (*this); };
			random_access_iterator &operator-=(difference_type n) { ptr -= n; return (*this);};
	};

	// Reverse iterator
	template <typename Iter>
	class	reverse_iterator {
		protected:
			Iter	current;
		public:
			typedef Iter                                                  iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type        value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type   difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer           pointer;
			typedef typename ft::iterator_traits<Iter>::reference         reference;

			reverse_iterator() : current() {}
			explicit reverse_iterator(iterator_type x) : current(x) {}
			template <class U>
			reverse_iterator(const reverse_iterator<U> &other) : current(other.current) {}

			template <class U>
			reverse_iterator	&operator=(const reverse_iterator<U> &other) { current = other.current; }

			iterator_type	base() const { return (current - 1); };
			reference		operator*() const { return (*(current - 1)); }
			pointer			operator->() const { return (current - 1); }
			reference		operator[](difference_type n) const { return (current[-n - 1]); }

			reverse_iterator &operator++() { current--; return (*this); }
			reverse_iterator &operator--() { current++; return (*this); }
			reverse_iterator operator++(int) { return (reverse_iterator(current--)); }
			reverse_iterator operator--(int) { return (reverse_iterator(current++)); }
			reverse_iterator operator+(difference_type n) const { return (reverse_iterator(current - n)); }
			reverse_iterator operator-(difference_type n) const { return (reverse_iterator(current + n)); }
			reverse_iterator &operator+=(difference_type n) { current -= n; return (*this); };
			reverse_iterator &operator-=(difference_type n) { current += n; return (*this);};
	};

	template <class Iter1, class Iter2>
	bool operator==(const ft::reverse_iterator<Iter1>& lhs,
					const ft::reverse_iterator<Iter2>& rhs) { return (lhs.base() == rhs.base()); }
	template <class Iter1, class Iter2>
	bool operator!=(const ft::reverse_iterator<Iter1>& lhs,
					const ft::reverse_iterator<Iter2>& rhs) { return (lhs.base() != rhs.base()); }
	template <class Iter1, class Iter2>
	bool operator<(const ft::reverse_iterator<Iter1>& lhs,
					const ft::reverse_iterator<Iter2>& rhs) { return (lhs.base() < rhs.base()); }
	template <class Iter1, class Iter2>
	bool operator<=(const ft::reverse_iterator<Iter1>& lhs,
					const ft::reverse_iterator<Iter2>& rhs) { return (lhs.base() <= rhs.base()); }
	template <class Iter1, class Iter2>
	bool operator>(const ft::reverse_iterator<Iter1>& lhs,
					const ft::reverse_iterator<Iter2>& rhs) { return (lhs.base() > rhs.base()); }
	template <class Iter1, class Iter2>
	bool operator>=(const ft::reverse_iterator<Iter1>& lhs,
					const ft::reverse_iterator<Iter2>& rhs) { return (lhs.base() >= rhs.base()); }

	template <class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
		const reverse_iterator<Iter>& it) { return (it + n); }
	template <class Iter>
	typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter>& lhs,
		const reverse_iterator<Iter>& rhs) { return (lhs.base() - rhs.base()); }
}
