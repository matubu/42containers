/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:38:23 by mberger-          #+#    #+#             */
/*   Updated: 2022/03/17 16:46:44 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"

namespace ft {
	struct random_access_iterator_tag {};
	struct bidirectional_iterator_tag {};

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
		typedef ft::random_access_iterator_tag iterator_category;
	};
	
	template <class T>
	struct iterator_traits<const T*> {
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef ft::random_access_iterator_tag iterator_category;
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
	template <class T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category  iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type         value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type    difference_type;
			typedef T*                                                                           pointer;
			typedef T&                                                                           reference;
		private:
			pointer	ptr;
		public:
			random_access_iterator() : ptr(NULL) {}
			random_access_iterator(const pointer ptr) : ptr(ptr) {}
			random_access_iterator(const random_access_iterator<T> &other) : ptr(other.ptr) {}
			random_access_iterator &operator=(const random_access_iterator<T> &other) { ptr = other.ptr; return (*this); }
			~random_access_iterator() {}

			friend bool	operator==(const random_access_iterator &a, const random_access_iterator &b) { return (a.ptr == b.ptr); }
			friend bool	operator!=(const random_access_iterator &a, const random_access_iterator &b) { return (a.ptr != b.ptr); }
			friend bool	operator<(const random_access_iterator &a, const random_access_iterator &b) { return (a.ptr < b.ptr); }
			friend bool	operator>(const random_access_iterator &a, const random_access_iterator &b) { return (a.ptr > b.ptr); }
			friend bool	operator<=(const random_access_iterator &a, const random_access_iterator &b) { return (a.ptr <= b.ptr); }
			friend bool	operator>=(const random_access_iterator &a, const random_access_iterator &b) { return (a.ptr >= b.ptr); }

			reference operator*() const { return (*ptr); }
			pointer   operator->() const { return (ptr); }
			reference operator[](difference_type n) const { return (ptr[n]); }

			random_access_iterator &operator++() { ptr++; return (*this); }
			random_access_iterator &operator--() { ptr--; return (*this); }
			random_access_iterator operator++(int) { random_access_iterator tmp(ptr); ++ptr; return (tmp); }
			random_access_iterator operator--(int) { random_access_iterator tmp(ptr); --ptr; return (tmp); }
			random_access_iterator operator+(difference_type n) const { return (random_access_iterator(ptr + n)); }
			random_access_iterator operator-(difference_type n) const { return (random_access_iterator(ptr - n)); }
			random_access_iterator &operator+=(difference_type n) { ptr += n; return (*this); };
			random_access_iterator &operator-=(difference_type n) { ptr -= n; return (*this);};
			
			operator random_access_iterator<const T> () const { return (random_access_iterator<const T>(ptr)); }

			friend random_access_iterator operator+(difference_type n, const random_access_iterator &it)
			{ return (it + n); }
			difference_type operator-(const random_access_iterator &rhs) const
			{ return (ptr - rhs.ptr); }
	};

	// Bidirectional iterator
	template <class T, class RET, bool _const = false>
	class bidirectional_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {
		public:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category  iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type         value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type    difference_type;
			typedef RET                                                                          *pointer;
			typedef RET                                                                          &reference;

			T	*ptr;

			bidirectional_iterator() : ptr(NULL) {}
			bidirectional_iterator(T *ptr) : ptr(ptr) {}
			bidirectional_iterator(const bidirectional_iterator &other) : ptr(other.ptr) {}
			bidirectional_iterator &operator=(const bidirectional_iterator &other) { ptr = other.ptr; return (*this); }
			~bidirectional_iterator() {}

			operator bidirectional_iterator<T, const typename T::type, true>() const
			{ return (bidirectional_iterator<T, const typename T::type, true>(ptr)); }

			template <class T_, class RET_, bool const_>
			friend bool	operator==(const bidirectional_iterator &a, const bidirectional_iterator<T_, RET_, const_> &b) { return (a.ptr == b.ptr); }
			template <class T_, class RET_, bool const_>
			friend bool	operator!=(const bidirectional_iterator &a, const bidirectional_iterator<T_, RET_, const_> &b) { return (a.ptr != b.ptr); }

			reference operator*() const { return (ptr->data); }
			pointer   operator->() const { return (&ptr->data); }

			bidirectional_iterator &operator++() {
				if (ptr->nil)
					ptr = ptr->left;
				else if (ptr->right->nil)
				{
					T	*tmp;
					do {
						tmp = ptr;
						ptr = ptr->parent;
					}
					while (tmp != ptr->left && !ptr->nil);
				}
				else
				{
					ptr = ptr->right;
					while (!ptr->left->nil)
						ptr = ptr->left;
				}
				return (*this);
			}
			bidirectional_iterator &operator--() {
				if (ptr->nil)
					ptr = ptr->right;
				else if (ptr->left->nil)
				{
					T	*tmp;
					do {
						tmp = ptr;
						ptr = ptr->parent;
					}
					while (tmp != ptr->right && !ptr->nil);
				}
				else
				{
					ptr = ptr->left;
					while (!ptr->right->nil)
						ptr = ptr->right;
				}
				return (*this);
			}
			bidirectional_iterator operator++(int) { bidirectional_iterator tmp(ptr); ++*this; return (tmp); }
			bidirectional_iterator operator--(int) { bidirectional_iterator tmp(ptr); --*this; return (tmp); }
	};

	// Reverse iterator
	template <typename Iter>
	class	reverse_iterator {
		private:
			Iter	curr;
		public:
			typedef Iter                                                  iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type        value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type   difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer           pointer;
			typedef typename ft::iterator_traits<Iter>::reference         reference;

			reverse_iterator() : curr() {}
			explicit reverse_iterator(Iter x) : curr(x) {}
			template <class U>
			reverse_iterator(const reverse_iterator<U> &other) : curr(other.base()) {}

			template <class U>
			reverse_iterator	&operator=(const reverse_iterator<U> &other) { curr = other.base(); return (*this); }

			template <class B>
			friend bool operator==(const reverse_iterator &a,
					const reverse_iterator<B> &b) { return (a.base() == b.base()); }
			template <class B>
			friend bool operator!=(const reverse_iterator &a,
					const reverse_iterator<B> &b) { return (a.base() != b.base()); }
			template <class B>
			friend bool operator<(const reverse_iterator &a,
					const reverse_iterator<B> &b) { return (a.base() > b.base()); }
			template <class B>
			friend bool operator<=(const reverse_iterator &a,
					const reverse_iterator<B> &b) { return (a.base() >= b.base()); }
			template <class B>
			friend bool operator>(const reverse_iterator &a,
					const reverse_iterator<B> &b) { return (a.base() < b.base()); }
			template <class B>
			friend bool operator>=(const reverse_iterator &a,
					const reverse_iterator<B> &b) { return (a.base() <= b.base()); }

			iterator_type	base() const { return (curr); };
			reference		operator*() const { Iter tmp(curr); --tmp; return (*tmp); }
			pointer			operator->() const { Iter tmp(curr); --tmp; return (tmp.operator->()); }
			reference		operator[](difference_type n) const { return (curr[-n - 1]); }

			reverse_iterator &operator++() { curr--; return (*this); }
			reverse_iterator &operator--() { curr++; return (*this); }
			reverse_iterator operator++(int) { return (reverse_iterator(curr--)); }
			reverse_iterator operator--(int) { return (reverse_iterator(curr++)); }
			reverse_iterator operator+(difference_type n) const { return (reverse_iterator(curr - n)); }
			reverse_iterator operator-(difference_type n) const { return (reverse_iterator(curr + n)); }
			reverse_iterator &operator+=(difference_type n) { curr -= n; return (*this); };
			reverse_iterator &operator-=(difference_type n) { curr += n; return (*this);};

			friend reverse_iterator operator+(difference_type n, const reverse_iterator &it)
			{ return (it + n); }
			difference_type operator-(const reverse_iterator &rhs) const
			{ return (rhs.curr - curr); }
	};
}
