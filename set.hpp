/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matubu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:46:00 by matubu            #+#    #+#             */
/*   Updated: 2022/03/14 22:46:35 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"

namespace ft {
	template <
		class Key,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<Key>
	>
	class set : public map {
		public:
			explicit set(const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type());
			template <class InputIterator>
			set(InputIterator first, InputIterator last,
				const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type());
			set(const set &x);
			~set() {}
	}
}
