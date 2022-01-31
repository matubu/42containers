/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:12:56 by mberger-          #+#    #+#             */
/*   Updated: 2022/01/31 19:53:33 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {
	// https://en.cppreference.com/w/cpp/algorithm/equal
	// https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare


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
	typedef struct {
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

		pair &operator=(const pair &other) { first = other.first; second = other.second; }
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
