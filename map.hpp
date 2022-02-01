/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:39:27 by mberger-          #+#    #+#             */
/*   Updated: 2022/02/01 15:48:21 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

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
		public:
			map() : nil(&nil), root(&nil) {}


			void debug(Node *node, Node *parent, int level = 0, bool right = true)
			{
				if (level)
				{
					for (int i = 0; ++i < level;)
						std::cout << "│  ";
					if (right) std::cout << "├──";
					else std::cout << "└──";
					//show error in parent child stuff
				}
				if (!node->nil) std::cout << (node->red ? "\033[101;30m" : "\033[40;97m") << node->data << "\033[0m" << (node->parent != parent ? " \033[91m(error)" : "") << "\033[0m" << std::endl;
				else std::cout << "\033[90mnil\033[0m" << std::endl;
				if (node->nil) return ;
				debug(node->right, node, level + 1, true);
				debug(node->left, node, level + 1, false);
			}



			// Rotation
			// https://en.wikipedia.org/wiki/Tree_rotation
			// https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
			// https://www.programiz.com/dsa/red-black-tree
			void leftRotate(Node *pivot)
			{
				Node	**ptr = pivot->parent->nil ? &root : (pivot->parent == pivot->parent->left ? &pivot->parent->left : &pivot->parent->right);
				Node	*node = pivot->right;

				pivot->right = node->left;
				node->left = pivot;
				node->parent = pivot->parent;
				pivot->parent = node;
				*ptr = node;
			}
			void rightRotate(Node *pivot)
			{
				Node	**ptr = pivot->parent->nil ? &root : (pivot->parent == pivot->parent->left ? &pivot->parent->left : &pivot->parent->right);
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

				//red black stuff
				Node *z = *ptr;
				while (z->parent->red)
				{
					if (z->parent == z->parent->parent->left)
					{
						Node	*y = z->parent->parent->right;
						if (y->red)
						{
							z->parent->red = false;
							y->red = false;
							z->parent->parent->red = true;
							z = z->parent->parent;
						}
						else
						{
							if (z == z->parent->right)
							{
								z = z->parent;
								leftRotate(z);
							}
							z->parent->red = false;
							z->parent->parent->red = true;
							rightRotate(z->parent->parent);
						}
					}
					else
					{
						Node	*y = z->parent->parent->left;
						if (y->red)
						{
							z->parent->red = false;
							y->red = false;
							z->parent->parent->red = true;
							z = z->parent->parent;
						}
						else
						{
							if (z == z->parent->left)
							{
								z = z->parent;
								rightRotate(z);
							}
							z->parent->red = false;
							z->parent->parent->red = true;
							leftRotate(z->parent->parent);
						}
					}
				}
				root->red = false;

				debug(root, &nil);
				std::cout << "Reorganisation successful" << std::endl;
				std::cout << "------------------------------------" << std::endl;
			}
			mapped_type	*find(const Key &key) {
				Node	*node = root;
				while (!node->nil)
					if (node->key == key)
						return (&node->data);
					else
						node = Compare()(key, node->key) ? node->left : node->right;
				return (NULL); // end()
			}
			//delete
	};
}
