/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:39:27 by mberger-          #+#    #+#             */
/*   Updated: 2022/01/31 21:32:35 by mberger-         ###   ########.fr       */
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

				Node(const value_type &value, Node *_parent) : key(value.first),
					data(value.second),
					parent(_parent),
					left(NULL),
					right(NULL),
					red(true) {}
			};

			Node	*root;
		public:
			map() : root(NULL) {}

			// Rotation
			// https://en.wikipedia.org/wiki/Tree_rotation
			// https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
			void leftRotate(Node *pivot)
			{
				Node *root = pivot->parent;

				root->right = pivot->left;
				pivot->left = root;
				//update root pointer to pivot
			}
			void rightRotate(Node *pivot)
			{
				Node *root = pivot->parent;

				root->left = pivot->right;
				pivot->right = root;
				//update root pointer to pivot
			}

			// Red black tree algo
			// https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
			// https://www.programiz.com/dsa/red-black-tree
			// https://www.codesdope.com/course/data-structures-red-black-trees/
			// https://dichchankinh.com/~galles/visualization/RedBlack.html
			// https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
			void	insert(const value_type &value) {
				Node	*parent = NULL;
				Node	**ptr = &root;

				while (*ptr)
				{
					if ((*ptr)->key == value.first) return ;
					parent = *ptr;
					ptr = Compare()(value.first, (*ptr)->key) ? &(*ptr)->left : &(*ptr)->right;
				}
				*ptr = new Node(value, parent);

				//red black stuff
				/*Node *newNode = *ptr;
				while (newNode->parent && newNode->parent->red)
				{
					Node *p = newNode->parent;
					Node *gp = p->parent;

					if (p == gp->left)
					{
						if (gp->right->red)
						{
							gp->red = true;
							gp->left->red = false;
							gp->right->red = false;
							newNode = gp;
						}
						else if (newNode == p->right)
						{
							newNode = p;
							leftRotate(newNode);
						}
						else
						{
							p->red = false;
							gp->red = true;
							rightRotate(gp);
						}
					}
					else
					{
						if (gp->left->red)
						{
							gp->red = true;
							gp->left->red = false;
							gp->right->red = false;
							newNode = gp;
						}
						else if (newNode == p->left)
						{
							newNode = p;
							rightRotate(newNode);
							p->red = false;
							gp->red = true;
							leftRotate(gp);
						}
					}
				}
				root->red = false;*/
			}
			mapped_type	*find(const Key &key) {
				Node	*node = root;
				while (node)
					if (node->key == key)
						return (&node->data);
					else
						node = Compare()(key, node->key) ? node->left : node->right;
				return (NULL); // end()
			}
			//delete
	};
}
