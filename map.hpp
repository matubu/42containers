/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:39:27 by mberger-          #+#    #+#             */
/*   Updated: 2022/03/14 13:35:50 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "iterator.hpp"

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
			typedef Key                                    key_type;
			typedef T                                      mapped_type;
			typedef ft::pair<const Key, T>                 value_type;
			typedef std::size_t                            size_type;
			typedef std::ptrdiff_t                         difference_type;
			typedef Compare                                key_compare;
			typedef Allocator                              allocator_type;
			typedef T&                                     reference;
			typedef const T&                               const_reference;
			typedef typename Allocator::pointer            pointer;
			typedef typename Allocator::const_pointer      const_pointer;
		private:
			struct Node {
				value_type	data;
				Node		*parent;
				Node		*left;
				Node		*right;
				bool		red;
				bool		nil;

				typedef value_type &reference;
				typedef value_type *pointer;
				typedef value_type type;

				Node() :
					data(),
					parent(this), left(this), right(this),
					red(false), nil(true) {}
				Node(const value_type &value, Node *_parent, Node *_nil) :
					data(value),
					parent(_parent), left(_nil), right(_nil),
					red(true), nil(false) {}
				Node(const Node &other, Node *_nil) :
					data(other.data),
					parent(_nil), left(_nil), right(_nil),
					red(other.red), nil(false) {}
			};

			Node		*nil;
			Node		*root;
			typename Allocator::template rebind<Node>::other	allocator;

			Node	*_find(const Key &key) const
			{
				Node	*node = root;
				while (!node->nil)
					if (node->data.first == key)
						break ;
					else
						node = Compare()(key, node->data.first) ? node->left : node->right;
				return (node);
			}
			void	_leftRotate(Node *pivot)
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
			void	_rightRotate(Node *pivot)
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
			void	_del(Node *node)
			{
				if (node->nil) return ;
				_del(node->left);
				_del(node->right);
				allocator.destroy(node);
				allocator.deallocate(node, 1);
			}
			size_type	_size(Node *node) const
			{
				if (node->nil) return (0);
				return (_size(node->left) + _size(node->right) + 1);
			}
			Node	*_insert(const value_type &value, bool *inserted = NULL) {
				Node	*parent = nil;
				Node	**ptr = &root;

				while (!(*ptr)->nil)
				{
					if ((*ptr)->data.first == value.first)
					{
						if (inserted) *inserted = false;
						return (*ptr);
					}
					parent = *ptr;
					ptr = Compare()(value.first, (*ptr)->data.first) ? &(*ptr)->left : &(*ptr)->right;
				}
				*ptr = allocator.allocate(1);
				allocator.construct(*ptr, Node(value, parent, nil));

				if (nil->left->nil || Compare()((*ptr)->data.first, nil->left->data.first))
					nil->left = *ptr;
				if (nil->right->nil || Compare()(nil->right->data.first, (*ptr)->data.first))
					nil->right = *ptr;

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

				if (inserted) *inserted = true;

				return (*ptr);
			}
			size_type	_erase(Node *node) {
				if (node->nil) return (0);
				if (node == nil->left)
					nil->left = (++iterator(nil->left)).ptr;
				if (node == nil->right)
					nil->right = (--iterator(nil->right)).ptr;
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
				allocator.destroy(node);
				allocator.deallocate(node, 1);
				return (1);
			}
			Node	*_cpy(Node *src)
			{
				if (src->nil) return (nil);
				Node	*node = allocator.allocate(1);
				allocator.construct(node, Node(*src, nil));
				node->right = _cpy(src->right);
				node->right->parent = node;
				node->left = _cpy(src->left);
				node->left->parent = node;
				return (node);
			}

		public:
			typedef ft::bidirectional_iterator<Node, value_type>       iterator;
			// typedef ft::bidirectional_iterator<const Node> const_iterator;
			typedef ft::bidirectional_iterator<Node, const value_type>       const_iterator;
			typedef ft::reverse_iterator<iterator>         reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>   const_reverse_iterator;

			explicit map(const key_compare &comp = key_compare(),
						const allocator_type &alloc = allocator_type()) : allocator()
			{
				(void)alloc;
				(void)comp;
				nil = allocator.allocate(1);
				allocator.construct(nil, Node());
				root = nil;
			}
			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : allocator() {
				(void)alloc;
				(void)comp;
				nil = allocator.allocate(1);
				allocator.construct(nil, Node());
				root = nil;
				while (first != last)
				{
					insert(*first);
					++first;
				}
			}
			map(const map &x) : allocator(x.allocator)
			{
				nil = allocator.allocate(1);
				allocator.construct(nil, Node());
				root = _cpy(x.root);
			};

			~map()
			{
				_del(root);
				allocator.destroy(nil);
				allocator.deallocate(nil, 1);
			}

			map &operator=(const map &other)
			{
				_del(root);
				root = _cpy(other.root);
				return (*this);
			}
			allocator_type get_allocator() const { return (allocator); }

			T &operator[](const Key &key) { return (_insert(value_type(key, T()))->data.second); };
			T &at(const Key& key) { Node *node = _find(key); if (node->nil) throw std::out_of_range(""); return (node->data.second); }
			const T &at(const Key& key) const { Node *node = _find(key); if (node->nil) throw std::out_of_range(""); return (node->data.second); }

			iterator begin()
			{
				Node	*node = root;
				while (!node->left->nil)
					node = node->left;
				return (iterator(node));
			}
			const_iterator begin() const
			{
				Node	*node = root;
				while (!node->left->nil)
					node = node->left;
				return (const_iterator(node));
			}
			iterator end() { return (iterator(nil)); }
			const_iterator end() const { return (const_iterator(nil)); }
			reverse_iterator rbegin() { return (reverse_iterator(end())); }
			const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }
			reverse_iterator rend() { return (reverse_iterator(begin())); }
			const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

			bool empty() const { return (root->nil); }
			size_type size() const { return _size(root); }
			size_type max_size() const { return (allocator.max_size()); }

			void clear() {
				_del(root);
				root = nil;
				nil->left = nil;
				nil->right = nil;
			}
			ft::pair<iterator, bool>	insert(const value_type &value)
			{
				bool	inserted;
				iterator it(_insert(value, &inserted));
				return (ft::make_pair<iterator, bool>(it, inserted));
			}
			iterator	insert(iterator hint, const value_type &value)
			{
				(void)hint;
				return (insert(value).first);
			}
			template <class InputIt>
			void	insert(InputIt first, InputIt last)
			{
				while (first != last)
				{
					insert(*first);
					++first;
				}
			}
			void	erase(iterator pos)
			{ _erase(pos.ptr); }
			void	erase(iterator first, iterator last)
			{
				while (first != last)
				{
					iterator tmp = first;
					++first;
					_erase(tmp.ptr);
				}
			}
			size_type	erase(const Key &key)
			{ return _erase(_find(key)); }
			void	swap(map& x) {
				std::swap(root, x.root);
				std::swap(nil, x.nil);
			};

			size_type	count(const Key &k) const { return (!_find(k)->nil); };
			iterator	find(const Key& key) { return (iterator(_find(key))); }
			const_iterator	find(const Key& key) const { return (const_iterator(_find(key))); }
			ft::pair<iterator, iterator>	equal_range(const Key &key)
			{
				Node *node = _find(key);
				iterator it(node);
				if (node->nil)
					return (ft::make_pair<iterator, iterator>(it, it));
				while (it->first == key)
					++it;
				return (ft::make_pair<iterator, iterator>(iterator(node), it));
			}
			ft::pair<const_iterator,const_iterator>	equal_range(const Key &key) const
			{
				Node *node = _find(key);
				const_iterator it(node);
				if (node->nil)
					return (ft::make_pair<const_iterator, const_iterator>(it, it));
				while (it->first == key)
					++it;
				return (ft::make_pair<const_iterator, const_iterator>(const_iterator(node), it));
			}
			iterator	lower_bound(const Key &key)
			{
				(void)key;
				return (iterator(nil));
			}
			const_iterator	lower_bound(const Key &key) const
			{
				(void)key;
				return (const_iterator(nil));
			}
			iterator	upper_bound(const Key &key)
			{
				(void)key;
				return (iterator(nil));
			}
			const_iterator	upper_bound(const Key &key) const
			{
				(void)key;
				return (const_iterator(nil));
			}

			key_compare	key_comp() const { return (Compare()); };
			class value_compare
			{
				protected:
					friend class map;
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type &x, const value_type &y) const
					{ return comp(x.first, y.first); }
			};
			value_compare	value_comp() const { return (value_compare(Compare())); };

			void	debug(Node *node, Node *parent, std::string buf = "", bool right = true)
			{
				if (!parent->nil)
				{
					std::cout << buf;
					if (right) std::cout << "├──";
					else std::cout << "└──";
					buf += right ? "│  " : "   ";
				}
				if (!node->nil)
					std::cout << (node->red ? "\033[101;30m" : "\033[40;97m") << node->data.second << "\033[0m" << (node->parent != parent ? " \033[91m(error)" : "") << "\033[0m" << std::endl;
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

			friend bool operator==(const map &lhs, const map &rhs)
			{
				if (lhs.size() != rhs.size()) return (false);
				return (true);
			}
			friend bool operator!=(const map &lhs, const map &rhs) { return (!(lhs == rhs)); }
			friend bool operator<(const map &lhs, const map &rhs)
			{
				return (lhs.size() < rhs.size());
			}
			friend bool operator>=(const map &lhs, const map &rhs)
			{ return (!(lhs < rhs)); }
			friend bool operator>(const map &lhs, const map &rhs)
			{ return (rhs < lhs); }
			friend bool operator<=(const map &lhs, const map &rhs)
			{ return (!(lhs > rhs)); }

			friend void swap(map &x, map &y) { x.swap(y); }
	};

}
