/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:36:15 by mberger-          #+#    #+#             */
/*   Updated: 2022/01/07 18:52:35 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory> // std::allocator
#include <exception> //std::error

namespace ft {
	template <
		class T,
		class Alloc = std::allocator<T>
	>
	class vector {
		public:
			//Types
			typedef T                                              value_type;
			typedef Alloc                                          allocator_type;
			typedef typename Alloc::reference                      reference;
			typedef typename Alloc::const_reference                const_reference;
			typedef typename Alloc::pointer                        pointer;
			typedef typename Alloc::const_pointer                  const_pointer;
			//typedef typename             iterator;
			//typedef typename             const_iterator;
			//typedef typename std::reverse_iterator<iterator>       reverse_iterator
			//typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator
			typedef typename std::ptrdiff_t                        difference_type;
			typedef typename std::size_t                           size_type;
		private:
			//Data
			Alloc	allocator;
			pointer	start;
			pointer	curr;
			pointer	end;
		public:
			//Constructor
			vector(void) : allocator() { start = curr = end = NULL; }
			explicit vector(const Alloc &alloc) : allocator(alloc) { start = curr = end = allocator.allocate(0); }
			//explicit vector(size_type count,
			//	const T& value = T(),
			//	const Allocator& alloc = Allocator()) {}
			//template<class InputIt>
			//vector(InputIt first, InputIt last,
			//		const Allocator& alloc = Allocator()) {}
			//vector(const vector& other) {}
	
			//Destructor
			//TODO destroy all elements ?
			~vector(void) { allocator.deallocate(start, capacity()); }

			//Access
			T	*data() { return (start); }
			const T	*data() const { return (start); }
			reference	operator[](size_type pos) { return (start[pos]); }
			const_reference	operator[](size_type pos) const { return (start[pos]); }

			//Capacity
			bool		empty() const { return (curr == start); }
			size_type	size() const { return (curr - start); }
			//TODO why not the same value
			size_type	max_size() const { return (std::numeric_limits<difference_type>::max()); }
			//TODO maybe need to destroy all elements
			void		reserve(size_type new_cap) {
				if (new_cap > max_size())
					throw std::length_error("'n' exceeds maximum supported size");
				if (new_cap <= capacity())
					return ;
				pointer		old = start;
				size_type	n = size(), cap = capacity();
				end = (start = allocator.allocate(new_cap)) + new_cap;
				curr = start + n;
				while (n--)
					start[n] = old[n];
				allocator.deallocate(old, cap);
			}
			size_type	capacity() const { return (end - start); }

			//Modifiers
			void	push_back(const T	&value) {
				if (size() >= capacity())
					reserve(capacity() ? capacity() * 2 : 1);
				*curr++ = value;
			}
			//TODO call elm destructor
			void	pop_back() {
				curr--;
			}
	};
}
