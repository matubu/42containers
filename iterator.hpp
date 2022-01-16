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
	template <class Iter>
	struct iterator_traits {
		typedef typename Iter::iterator_category iterator_category;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::difference_type difference_type;
		typedef difference_type distance_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
	};
	template<class T>
	struct iterator_traits<T*> {
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};
	
	template<class T>
	struct iterator_traits<const T*> {
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

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

			template<class U>
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

	template<class Iter1, class Iter2>
	bool operator==(const ft::reverse_iterator<Iter1>& lhs,
					const ft::reverse_iterator<Iter2>& rhs) { return (lhs.base() == rhs.base()); }
	template<class Iter1, class Iter2>
	bool operator!=(const ft::reverse_iterator<Iter1>& lhs,
					const ft::reverse_iterator<Iter2>& rhs) { return (lhs.base() != rhs.base()); }
	template<class Iter1, class Iter2>
	bool operator<(const ft::reverse_iterator<Iter1>& lhs,
					const ft::reverse_iterator<Iter2>& rhs) { return (lhs.base() < rhs.base()); }
	template<class Iter1, class Iter2>
	bool operator<=(const ft::reverse_iterator<Iter1>& lhs,
					const ft::reverse_iterator<Iter2>& rhs) { return (lhs.base() <= rhs.base()); }
	template<class Iter1, class Iter2>
	bool operator>(const ft::reverse_iterator<Iter1>& lhs,
					const ft::reverse_iterator<Iter2>& rhs) { return (lhs.base() > rhs.base()); }
	template<class Iter1, class Iter2>
	bool operator>=(const ft::reverse_iterator<Iter1>& lhs,
					const ft::reverse_iterator<Iter2>& rhs) { return (lhs.base() >= rhs.base()); }

	template<class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
		const reverse_iterator<Iter>& it) { return (it + n); }
	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) { return (lhs.base() - rhs.base()); }
}
