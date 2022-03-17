/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:12:56 by mberger-          #+#    #+#             */
/*   Updated: 2022/03/17 16:28:41 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <functional>
#include <memory> // allocator
#include <stdexcept> // error

namespace ft {
	// https://en.cppreference.com/w/cpp/algorithm/equal
	// https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1,
				InputIt2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}
	template<class InputIt1, class InputIt2, class BinaryPredicate>
		bool equal(InputIt1 first1, InputIt1 last1,
				InputIt2 first2, BinaryPredicate p)
	{
		while (first1 != last1)
		{
			if (!p(*first1, *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}
	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2) return (true);
			if (*first2 < *first1) return (false);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2,
								Compare comp)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (comp(*first1, *first2)) return (true);
			if (comp(*first2, *first1)) return (false);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	// Swap
	template <class T>
	void swap(T &a, T &b)
	{
		T tmp(a);
		a = b;
		b = tmp;
	}

	// Is integral
	template <class T> struct is_integral {
		typedef T type;
		static const bool value = false;
	};

	template <typename T>
	struct true_type {
		typedef T type;
		static const bool value = true;
	};

	template <>        struct is_integral<unsigned char>      : public true_type<unsigned char> {};
	template <>        struct is_integral<unsigned short>     : public true_type<unsigned short> {};
	template <>        struct is_integral<unsigned int>       : public true_type<unsigned int> {};
	template <>        struct is_integral<unsigned long>      : public true_type<unsigned long> {};
	template <>        struct is_integral<unsigned long long> : public true_type<unsigned long long> {};

	template <>        struct is_integral<signed char>        : public true_type<signed char> {};
	template <>        struct is_integral<signed short>       : public true_type<signed short> {};
	template <>        struct is_integral<signed int>         : public true_type<signed int> {};
	template <>        struct is_integral<signed long>        : public true_type<signed long> {};
	template <>        struct is_integral<signed long long>   : public true_type<signed long long> {};

	template <>        struct is_integral<char>               : public true_type<char> {};
	template <>        struct is_integral<bool>               : public true_type<bool> {};

	// Enable if
	template <bool Condition, class T = void>  struct enable_if           {};
	template <class T>                         struct enable_if<true, T>  { typedef T type; };

	// Nullptr
	typedef struct ft_nullptr_s {
		template <class T>             inline operator T*() const { return (0); }
		template <class C, class T>    inline operator T C::*() const { return (0); }
	}	ft_nullptr_t;

	// Pair
	template <class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;
		T1 first;
		T2 second;

		pair() : first(), second() {}
		pair(const T1 &x, const T2 &y) : first(x), second(y) {}
		template<class U1, class U2>
		pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}
		pair(const pair &p) : first(p.first), second(p.second) {}

		pair &operator=(const pair &other) {
			first = other.first;
			second = other.second;
			return (*this);
		}
	};

	template <class T1, class T2>
		bool operator==(const ft::pair<T1,T2> &lhs, const ft::pair<T1,T2> &rhs)
		{ return (lhs.first == rhs.first && lhs.second == rhs.second); }
	template <class T1, class T2>
		bool operator!=(const ft::pair<T1,T2> &lhs, const ft::pair<T1,T2> &rhs)
		{ return (!(lhs == rhs)); }
	template <class T1, class T2>
		bool operator<(const ft::pair<T1,T2> &lhs, const ft::pair<T1,T2> &rhs)
		{ return (lhs.first < rhs.first || (rhs.first == lhs.first && lhs.second < rhs.second)); }
	template <class T1, class T2>
		bool operator<=(const ft::pair<T1,T2> &lhs, const ft::pair<T1,T2> &rhs)
		{ return (!(rhs < lhs)); }
	template <class T1, class T2>
		bool operator>(const ft::pair<T1,T2> &lhs, const ft::pair<T1,T2> &rhs)
		{ return (rhs < lhs); }
	template <class T1, class T2>
		bool operator>=(const ft::pair<T1,T2> &lhs, const ft::pair<T1,T2> &rhs)
		{ return (!(lhs < rhs)); }

	// Make pair
	template <class T1, class T2>
	ft::pair<T1, T2> make_pair(T1 x, T2 y) { return (ft::pair<T1, T2>(x, y)); };
}
