/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:12:56 by mberger-          #+#    #+#             */
/*   Updated: 2022/01/18 21:12:59 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {
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
		//void operator&() const = delete;
		template <class T>             inline operator T*() const { return 0; }
		template <class C, class T>    inline operator T C::*() const { return 0; }
	}	ft_nullptr_t;
	ft_nullptr_t	ft_nullptr;
}
