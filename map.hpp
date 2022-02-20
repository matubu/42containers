/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:39:27 by mberger-          #+#    #+#             */
/*   Updated: 2022/02/04 15:21:37 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

// https://en.wikipedia.org/wiki/Tree_rotation
// https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
// https://www.programiz.com/dsa/red-black-tree
// https://www.codesdope.com/course/data-structures-red-black-trees/
// https://dichchankinh.com/~galles/visualization/RedBlack.html
// https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
// https://www.programiz.com/dsa/insertion-in-a-red-black-tree

#define GET_PTR_NODE(node) \
	(node->parent->nil ? &root : (node == node->parent->left ? &node->parent->left : &node->parent->right))

// TODO set previous as max for nil ?
// TODO add red black stuff for erase

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

				Node() :
					key(), data(),
					parent(this), left(this), right(this),
					red(false), nil(true) {}
				Node(const value_type &value, Node *_parent, Node *_nil) :
					key(value.first), data(value.second),
					parent(_parent), left(_nil), right(_nil),
					red(true), nil(false) {}
				Node(const Node &other, Node *_nil) :
					key(other.key), data(other.data),
					parent(_nil), left(_nil), right(_nil),
					red(other.red), nil(false) {}
			};

			Node	*nil;
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
			void _leftRotate(Node *pivot)
			{
				Node	**ptr = GET_PTR_NODE(pivot);
				Node	*node = pivot->right;

				pivot->right = node->left;
				pivot->right->parent = pivot;
				node->left = pivot;
				node->parent = pivot->parent;
				pivot->parent = node;
				*ptr = node;
			}
			void _rightRotate(Node *pivot)
			{
				Node	**ptr = GET_PTR_NODE(pivot);
				Node	*node = pivot->left;

				pivot->left = node->right;
				pivot->left->parent = pivot;
				node->right = pivot;
				node->parent = pivot->parent;
				pivot->parent = node;
				*ptr = node;
			}
			void _del(Node *node)
			{
				if (node->nil) return ;
				_del(node->left);
				_del(node->right);
				delete node;
			}
			size_type _size(Node *node)
			{
				if (node->nil) return (0);
				return (_size(node->left) + _size(node->right) + 1);
			}
			Node	*_insert(const value_type &value) {
				Node	*parent = nil;
				Node	**ptr = &root;

				while (!(*ptr)->nil)
				{
					if ((*ptr)->key == value.first) return (*ptr);
					parent = *ptr;
					ptr = Compare()(value.first, (*ptr)->key) ? &(*ptr)->left : &(*ptr)->right;
				}
				*ptr = new Node(value, parent, nil);

				//red black stuff
				#define INSERT_FIX(side, ar, br) { \
					Node	*y = z->parent->parent->side; \
					if (y->red) \
					{ \
						z->parent->red = false; \
						y->red = false; \
						z->parent->parent->red = true; \
						z = z->parent->parent; \
					} \
					else \
					{ \
						if (z == z->parent->side) \
						{ \
							z = z->parent; \
							ar(z); \
						} \
						z->parent->red = false; \
						z->parent->parent->red = true; \
						br(z->parent->parent); \
					} \
				}

				Node *z = *ptr;
				while (z->parent->red)
					if (z->parent == z->parent->parent->left)
						INSERT_FIX(right, _leftRotate, _rightRotate)
					else
						INSERT_FIX(left, _rightRotate, _leftRotate)
				root->red = false;

				return (*ptr);
			}
			Node *_cpy(Node *src)
			{
				if (src->nil) return (nil);
				Node *node = new Node(src, nil);
				node->right = _cpy(node->right);
				node->right->parent = node;
				node->left = _cpy(node->left);
				node->left->parent = node;
				return (node);
			}
		public:
			explicit map(const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type()) : nil(new Node()), root(nil) { (void)comp; (void)alloc; }
			map(const map &x) : nil(new Node()), root(_cpy(x->root)) {};
			~map() { _del(root); delete nil; }
			map &operator=(const map &other) { _del(root); root = _cpy(other->root); return (*this); }
			//allocator_type get_allocator() const {}

			T& at(const Key& key) { Node *node = _find(key); if (node->nil) throw std::out_of_range("element not in map"); return (node->data); }
			const T& at(const Key& key) const { Node *node = _find(key); if (node->nil) throw std::out_of_range("element not in map"); return (node->data); }
			T& operator[](const Key& key) { return (_insert(value_type(key, T()))->data); };

			/*
			iterator begin() { Node *node = root; while (!node->left->nil) node = node->left; return (iterator(node)); }
			const_iterator begin() const {}
			iterator end() { Node *node = root; while (!node->right->nil) node = node->right; return (iterator(node)); }
			const_iterator end() const {}
			reverse_iterator rbegin() { return (reverse_iterator(end())); }
			const_reverse_iterator rbegin() const {}
			reverse_iterator rend() { return (reverse_iterator(begin())); }
			const_reverse_iterator rend() const {}
			*/

			bool empty() const { return (root->nil); }
			size_type size() const { return _size(root); }
			// size_type max_size() const;

			void clear() { _del(root); root = nil; }
			void insert(const value_type &value) { _insert(value); }
			void erase(const Key &key) {
				Node	*node = _find(key);
				std::cout << (node->nil ? "not found " : "deleted ") << key << std::endl;
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
				{
					Node *min = node->right;
					while (!min->left->nil)
						min = min->left;
					min->right->parent = min;
					node->left->parent = min;
					min->left = node->left;
					min->red = node->red;
					node->right->parent = node->parent;
					*ptr = node->right;
				}
				delete node;
			}
			void swap(map& x) {
				std::swap(root, x.root);
				std::swap(nil, x.nil);
			};

			size_type count (const key_type& k) const { return (!_find(k)->nil); };
			mapped_type	*find(const Key &key) {
				Node	*node = _find(key);
				return (node->nil ? NULL : &node->data);
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
				if (parent->nil) std::cout << std::endl << std::flush;
			}
			void debug() { debug(root, nil); }
	};

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) { x.swap(y); }
}
