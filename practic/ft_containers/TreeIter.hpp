# ifndef TREE_ITER_HPP
# define TREE_ITER_HPP

// # include <vector>
# include <memory>
# include <stdexcept>
# include <stdint.h>
# include <iostream>
# include <functional>
# include "iterator.hpp"
# include "utility.hpp"
# include "type_traits.hpp"
# include "RandomAccessIterator.hpp"



namespace ft
{

	template <class Value>
	struct Node
	{
		public:

			Value		*data;
			Node 		*parent;
			Node 		*left;
			Node 		*right;
			bool		is_nil;
			bool		is_black;

		Node (Value *value = 0) : data(value), parent(0), left(0),
			right(0), is_nil(false), is_black(false) {};

		Node (const Node &other) : data(other.data), parent(other.parent), left(other.left),
			right(other.right), is_nil(other.is_nil), is_black(other.is_black) {};


		Node&	operator = (const Node &other)
		{
			
			data = other.data;
			parent = other.parent;
			left = other.left;
			right = other.right;
			is_nil = other.is_nil;
			is_black = other.is_black;
			return (*this);
		}

		virtual ~Node() {};

	};

	template <class T>
	class TreeIter
	{
		public:

			typedef ft::bidirectional_iterator_tag									iterator_category;
			typedef typename iterator_traits<T*>::value_type						value_type;
			typedef typename iterator_traits<T*>::difference_type					difference_type;
			typedef typename iterator_traits<T*>::pointer							pointer;
			typedef typename iterator_traits<T*>::reference							reference;
			typedef Node<typename ft::remove_const<value_type>::type>*		node_pointer;

		private:

			node_pointer	_node;

			node_pointer	_min_node(node_pointer node)
			{
				node_pointer tmp = node;

				while(tmp->left && !tmp->left->is_nil)
					tmp = tmp->left;
				return (tmp);
			}

			node_pointer	_max_node(node_pointer node)
			{
				node_pointer tmp = node;

				while(tmp->right && !tmp->right->is_nil)
					tmp = tmp->right;
				return (tmp);
			}
		
		public:

		// CONSTRUCTORS

			TreeIter() {};
			TreeIter(void *node) : _node(static_cast<node_pointer>(node)) {};
			TreeIter(TreeIter<typename ft::remove_const<value_type>::type>* const &other)
			{
				*this = other;
			}

			TreeIter& operator=(const TreeIter<typename ft::remove_const<value_type>::type>& other) {
			this->_node = other.node();
			return *this;
		}

			~TreeIter() {};

		// OPERATIONS

			reference operator*() const
			{
				return (*(_node->data));
			};

			pointer operator->() const
			{
				return (_node->data);
			};
				
			TreeIter& operator++()
			{
				if (!_node->right->is_nil)
					_node = _min_node(_node->right);
				else
				{
					node_pointer found = _node->parent;
					while (found != NULL && _node == found->right)
					{
						_node = found;
						found = found->parent;
					}
					_node = found;
				}
				return (*this);
			};
			
			TreeIter  operator++(int)
			{
				TreeIter temp = *this;
				if (!_node->right->is_nil)
					_node = _min_node(_node->right);
				else
				{
					node_pointer found = _node->parent;
					while (found != NULL && _node == found->right)
					{
						_node = found;
						found = found->parent;
					}
					_node = found;
				}
				return (temp);
			};

			TreeIter& operator--()
			{
				if (!_node->left->is_nil)
					_node = _max_node(_node->left);
				else
				{
					node_pointer found = _node->parent;
					while (found != NULL && _node == found->left)
					{
						_node = found;
						found = found->parent;
					}
					_node = found;
				}
				return (*this);
			};
			
			TreeIter  operator--(int)
			{
				TreeIter temp = *this;
				if (!_node->left->is_nil)
					_node = _max_node(_node->left);
				else
				{
					node_pointer found = _node->parent;
					while (found != NULL && _node == found->left)
					{
						_node = found;
						found = found->parent;
					}
					_node = found;
				}
				return (temp);
			};

		// getter
		node_pointer get_node() const {
			return _node;
		}
	};
};



# endif