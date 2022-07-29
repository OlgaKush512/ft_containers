# ifndef TREE_ITER_HPP
# define TREE_ITER_HPP

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
	};

	template <class T>
	class TreeIter : public ft::iterator<std::bidirectional_iterator_tag, T>
	{
		public:

			typedef std::bidirectional_iterator_tag									iterator_category;
			typedef typename iterator_traits<T*>::value_type						value_type;
			typedef typename iterator_traits<T*>::difference_type					difference_type;
			typedef typename iterator_traits<T*>::pointer							pointer;
			typedef typename iterator_traits<T*>::reference							reference;
			typedef Node<typename ft::remove_const<value_type>::type>*				node_pointer;


		private:

			node_pointer	_node;

			node_pointer	_min_node(node_pointer node)
			{
				node_pointer tmp = node;

				while(tmp && tmp->left != NULL && !tmp->left->is_nil)
					tmp = tmp->left;
				return (tmp);
			}

			node_pointer	_max_node(node_pointer node)
			{
				node_pointer tmp = node;

				while(tmp && tmp->right != NULL && !tmp->right->is_nil)
					tmp = tmp->right;
				return (tmp);
			}
		
		public:

		// CONSTRUCTORS

			TreeIter() {};
			TreeIter(void* node) : _node(static_cast<node_pointer>(node)) {};

			TreeIter(const TreeIter<typename ft::remove_const<value_type>::type> &other)
			{
				*this = other;
			}

			TreeIter& operator=(const TreeIter<typename ft::remove_const<value_type>::type>& other)
			{
				this->_node = other.get_node();
				return *this;
			}

			~TreeIter() {};

			// operator	TreeIter<value_type>() 
			// {
			// 	return TreeIter<value_type>(_node);
			// }

		// OPERATIONS

			reference operator*() const
			{
				return (*(_node->data));
			};

			pointer operator->() const
			{
				if (_node)
					return (_node->data);
				return (NULL);
			};
				
			TreeIter& operator++()
			{
				if (_node)
				{
					if ( _node->right && !_node->right->is_nil)
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
				}
				return (*this);
			};
			
			TreeIter  operator++(int)
			{
				TreeIter temp = *this;
				
					if (_node->right && !_node->right->is_nil)
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
				if (_node)
				{
					if (_node && _node->left && !_node->left->is_nil)
					_node = _max_node(_node->left);
					else
					{
						if ( _node)
						{
							node_pointer found = _node->parent;
							while (found != NULL && _node == found->left)
							{
								_node = found;
								found = found->parent;
							}
							_node = found;
						}
					}
				}
				return (*this);
			};
			
			TreeIter  operator--(int)
			{
				TreeIter temp = *this;
				if (_node)
				{
					if (_node->left && !_node->left->is_nil)
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
				}
				return (temp);
			};

		// getter
			node_pointer get_node() const
			{
				if (_node)
					return _node;
				else
					return (NULL);
			}
	};

	template <typename T1, typename T2>
	bool operator==(const TreeIter<T1> &lhs, const TreeIter<T2> &rhs)
	{
		return (lhs.get_node() == rhs.get_node());
	}

	template <typename T1, typename T2>
	bool operator!=(const TreeIter<T1> &lhs, const TreeIter<T2> &rhs)
	{
		return (lhs.get_node() != rhs.get_node());
	}

};

# endif
