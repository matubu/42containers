/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matubu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:46:00 by matubu            #+#    #+#             */
/*   Updated: 2022/03/15 19:30:38 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "map.hpp"

namespace ft {
	template <
		class Key,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<Key>
	>
	class set : public map<Key, Key, Compare, Allocator>
	{
		typedef Key value_type;
		typedef Key mapped_type;
	};
}
