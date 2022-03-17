/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matubu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:46:00 by matubu            #+#    #+#             */
/*   Updated: 2022/03/17 16:31:30 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "btree.hpp"

namespace ft {
	template <
		class Key,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<Key>
	>
	class set : public btree<Key, Compare, Allocator>
	{
		typedef	btree<Key, Compare, Allocator> btree;

		public:
			explicit set(const Compare &comp = Compare(),
						const Allocator &alloc = Allocator()) : btree(comp, alloc) {}
			template <class InputIterator>
			set(InputIterator first, InputIterator last,
				const Compare& comp = Compare(),
				const Allocator& alloc = Allocator()) : btree(first, last, comp, alloc) {}
			set(const set &x) : btree(x) {}

			~set() {}

			friend void swap(set &x, set &y) { x.swap(y); }
	};
}
