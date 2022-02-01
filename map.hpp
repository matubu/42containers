/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:39:27 by mberger-          #+#    #+#             */
/*   Updated: 2022/02/01 19:17:27 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

#define GET_PTR_NODE(node) \
	(node->parent->nil ? &root : (node->parent == node->parent->left ? &node->parent->left : &node->parent->right));

// TODO set previous for nil ?

namespace ft {
	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> >
	>
	class map {
		public:
			typedef Key                               key_type;
			typedef T                                 mapped_type;
			typedef ft::pair<const Key, T>            value_type;
			typedef std::size_t                       size_type;
			typedef std::ptrdiff_t                    difference_type;
			typedef Compare                           key_compare;
			typedef Allocator                         allocator_type;
			typedef T &                               reference;
			typedef const T &                         const_reference;
			typedef typename Allocator::pointer       pointer;
			typedef typename Allocator::const_pointer const_pointer;
			//typedef iterator
			//typedef const_iterator
			//typedef reverse_iterator
			//typedef const_reverse_iterator
		private:
			struct Node {
				Key		key;
				T		data;
				Node	*parent;
				Node	*left;
				Node	*right;
				bool	red;
				bool	nil;

				Node(Node *_nil) :
					key(),
					data(),
					parent(_nil),
					left(_nil),
					right(_nil),
					red(false),
					nil(true) {}
				Node(const value_type &value, Node *_parent, Node *_nil) :
					key(value.first),
					data(value.second),
					parent(_parent),
					left(_nil),
					right(_nil),
					red(true),
					nil(false) {}
			};

			Node	nil;
			Node	*root;

			Node	*_find(const Key &key) {
				Node	*node = root;
				while (!node->nil)
					if (node->key == key)
						break ;
					else
						node = Compare()(key, node->key) ? node->left : node->right;
				return (node);
			}
			void debug(Node *node, Node *parent, std::string buf = "", bool right = true)
			{
				if (!parent->nil)
				{
					std::cout << buf;
					if (right) std::cout << "├──";
					else std::cout << "└──";
					buf += right ? "│  " : "   ";
				}
				if (!node->nil)
					std::cout << (node->red ? "\033[101;30m" : "\033[40;97m") << node->data << "\033[0m" << (node->parent != parent ? " \033[91m(error)" : "") << "\033[0m" << std::endl;
				else
				{
					std::cout << "\033[90mnil\033[0m" << std::endl;
					return ;
				}
				debug(node->right, node, buf, true);
				debug(node->left, node, buf, false);
				if (parent->nil) std::cout << std::endl;
			}
		public:
			map() : nil(&nil), root(&nil) {}

			// Rotation
			// https://en.wikipedia.org/wiki/Tree_rotation
			// https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
			// https://www.programiz.com/dsa/red-black-tree
			void leftRotate(Node *pivot)
			{
				Node	**ptr = GET_PTR_NODE(pivot);
				Node	*node = pivot->right;

				pivot->right = node->left;
				node->left = pivot;
				node->parent = pivot->parent;
				pivot->parent = node;
				*ptr = node;
			}
			void rightRotate(Node *pivot)
			{
				Node	**ptr = GET_PTR_NODE(pivot);
				Node	*node = pivot->left;

				pivot->left = node->right;
				node->right = pivot;
				node->parent = pivot->parent;
				pivot->parent = node;
				*ptr = node;
			}

			// Red black tree algo
			// https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
			// https://www.programiz.com/dsa/red-black-tree
			// https://www.codesdope.com/course/data-structures-red-black-trees/
			// https://dichchankinh.com/~galles/visualization/RedBlack.html
			// https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
			// https://www.programiz.com/dsa/insertion-in-a-red-black-tree
			void	insert(const value_type &value) {
				std::cout << std::endl << std::endl << std::endl << "------------------------------------" << std::endl;
				debug(root, &nil);
				std::cout << "Starting insertion " << value.second << std::endl;

				Node	*parent = &nil;
				Node	**ptr = &root;

				while (!(*ptr)->nil)
				{
					if ((*ptr)->key == value.first) return ;
					parent = *ptr;
					ptr = Compare()(value.first, (*ptr)->key) ? &(*ptr)->left : &(*ptr)->right;
				}
				*ptr = new Node(value, parent, &nil);

				debug(root, &nil);
				std::cout << "Insertion successful starting reorganizing" << std::endl;

				#define CASE(side, ar, br) { \
					Node	*y = z->parent->parent->side; \
					if (y->red) \
					{ \
						std::cout << #side "_1"; \
						z->parent->red = false; \
						y->red = false; \
						z->parent->parent->red = true; \
						z = z->parent->parent; \
					} \
					else \
					{ \
						std::cout << #side "_2"; \
						if (z == z->parent->side) \
						{ \
							std::cout << "a"; \
							z = z->parent; \
							ar(z); \
						} \
						z->parent->red = false; \
						z->parent->parent->red = true; \
						br(z->parent->parent); \
					} \
					std::cout << std::endl; \
				}

				//red black stuff
				Node *z = *ptr;
				while (z->parent->red)
					if (z->parent == z->parent->parent->left)
						CASE(right, leftRotate, rightRotate)
					else
						CASE(left, rightRotate, leftRotate)
				root->red = false;

				debug(root, &nil);
				std::cout << "Reorganisation successful" << std::endl;
				std::cout << "------------------------------------" << std::endl;
			}
			mapped_type	*find(const Key &key) {
				Node	*node = _find(key);
				return (node->nil ? NULL : &node->data);
			}
			void erase(const Key &key) {
				//debug(root, &nil);
				Node	*node = _find(key);
				if (node->nil) return ;
				Node	**ptr = GET_PTR_NODE(node);
				if (node->left->nil)
				{
					node->right->parent = node->parent;
					*ptr = node->right;
				}
				else if (node->right->nil)
				{
					node->left->parent = node->parent;
					*ptr = node->left;
				}
				else
					// do some stuff
					;
				//debug(root, &nil);
			}
	};
}
