/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matubu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:46:00 by matubu            #+#    #+#             */
/*   Updated: 2022/02/09 15:50:38 by matubu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"

namespace ft {
	template <
		class Key,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<Key>
	>
	class set {
		ft::map<Key, void, Compare, Allocator>	c;
		public:
	}
}
