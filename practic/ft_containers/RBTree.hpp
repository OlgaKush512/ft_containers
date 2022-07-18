# ifndef RB_TREE_HPP
# define RB_TREE_HPP

// # include <vector>
# include <memory>
# include <stdexcept>
# include <stdint.h>
# include <iostream>
# include <functional>
# include "iterator.hpp"
# include "utility.hpp"
# include "type_traits.hpp"
# include "TreeIter.hpp"



namespace ft {

	template <class Value, class Compare = std::less<Value>, class Allocator = std::allocator<Value> >
	class RBTree
	{
		public:
			typedef Value												value_type;
			typedef Compare												value_compare;
			typedef Allocator											allocator_type;
			typedef typename Allocator::template
									rebind<Node<value_type> >::other	node_allocator;
			typedef typename node_allocator::pointer					node_pointer;


			typedef allocator_type::size_t								size_type;
			typedef allocator_type::ptrdiff_t							difference_type;

			

			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;

			typedef TreeIter<Value>										iterator;
			typedef TreeIter<const Value>								const_iterator;
			typedef	ft::reverse_iterator<iterator>						reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>				const_reverse_iterator;

		private:

			allocator_type				_alloc;
			node_allocator				_node_alloc;
			value_compare 				_compare;
			node_pointer				_nil;
			node_pointer				_header;
			node_pointer				_root;
			size_type					_size;

			// HELPER

			node_pointer _min(node_pointer node) const
			{
				node_pointer tmp = node;

				while(tmp->left && !tmp->left->is_nil)
					tmp = tmp->left;
				return (tmp);
			}

			node_pointer _max(node_pointer node) const
			{
				node_pointer tmp = node;

				while(tmp->left && !tmp->left->is_nil)
					tmp = tmp->left;
				return (tmp);
			}

			void	_init_nil_head()
			{
				_nil = _node_alloc.allocate(1);
				_node_alloc.construct(_nil, Node<Value>());
				_nil->is_nil = true;
				_nil->is_nil = true;
				_header = _node_alloc.allocate(1);
				_node_alloc.construct(_header, Node<Value>());
				_header->is_nil = false;
				_header->is_nil = true;
				_header->data = _alloc.allocate(1);
				_alloc.construct(_header->data, Value());
			}

			bool	_is_root(node_pointer node)
			{
				return (node == _root);
			}
			
			bool	_is_nill(node_pointer node)
			{
				return (node->is_nil);
			}

			//ROTATION

			void	_left_rotate(node_pointer node)
			{
				node_pointer child = node->right;

				node->right = child->left;
				child->left->parent = node;
				child->parent = node->parent;
				if (node->parent->is_nil)
				{
					child->is_root = 1;
					_root = child;
					node->is_root = 0;
				}
				else if (node == node->parent->left)
					node->parent->left = child;
				else
					node->parent->right = child;
				child->left = node;
				node->parent = child;
			}

			void	_right_rotate(node_pointer *node)
			{
				node_pointer *child = node->left;

				node->left = child->right;
				child->right->parent = node;
				child->parent = node->parent;
				if (node->parent->is_nil)
				{
					child->is_root = 1;
					g_root = child;
					node->is_root = 0;
				}
				else if (node == node->parent->left)
					node->parent->left = child;
				else if (node == node->parent->right)
					node->parent->right = child;
				child->right = node;
				node->parent = child;
			}

			// CHECKER

			node_pointer	search(value_type value, node_pointer node)
			{
				if (!node || is_nill(node))
					return (NULL);
				if (_compare(_value, node->_value))
					search(value, node->_left);
				if (_compare(*node->_value, value))
					search(value, node->_right);
				return (node);
			}

		public:

			// CONSTRUCTORS

			RBTree(const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : 
				_alloc(alloc), _compare(comp), _size(0)
			{
				_init_nil_head();
				_root = head;
			};

			RBTree() : _alloc(allocator_type()), _compare(value_compare()), _size(0)
			{
				_init_nil_head();
				_root = head;
			};
			RBTree() {}; // range
			RBTree(RBTree&) {}; // copy
			RBTree& operator=(RBTree&) {}; // =

			~RBTree() {}; //destructor

			// iterators:

			iterator begin()
			{
				if (_size == 0)
					return (iterator(_head));
				else
					return (iterator(_min(_root)));
			}
			
			const_iterator begin()const
			{
				if (_size == 0)
					return (const_iterator(_head));
				else
					return (const_iterator(_min(_root)));
			}
			
			iterator end()
			{
				return (iterator(_head));
			}
			
			const_iterator end()const
			{
				return (const_iterator(_head));
			}
			
			reverse_iterator rbegin()
			{
				return (reverse_iterator(end()));
				// if (_size == 0)
				// 	return (reverse_iterator(_head));
				// else
				// 	return (reverse_iterator(_max(_root)));
			}
			
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(end()));
			}
			
			reverse_iterator rend()
			{
				return (reverse_iterator(begin()));
			}
			
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(begin()));
			}

			// capacity:
			bool empty() const
			{
				return (_size == 0);
			}

			size_type size() const
			{
				return (_size);
			}


			// modifiers:

			pair<iterator, bool>	insert(const value_type& x) // value_type = pair
			{
				node_pointer is_existe = search(x, this->_root);
				if (is_existe)
					return (is_existe, false);

				node_pointer new_node = create_node(new_node)
				
			}

			void rb_insert(t_node **root, int data)
			{
				t_node *new = create(*root, data);
				t_node *x = *root;
				if (*root == NULL)
				{
					*root = new;
					// printf("data of root: %d\n", new->data);
					return;
				}
				// printf("data of root1: %d\n", x->data);
				t_node *y = NULL;
				x = *root;
				while (x->is_nil != 1)
				{
					y = x;
					if (new->data < x->data)
						x = x->left;
					else
						x = x->right;
				}
				new->parent = y;
				if (y == NULL)
					*root = new;
				else if (new->data < y->data)
					y->left = new;
				else
					y->right = new;
				new->left = create_nil(new);
				new->right = create_nil(new);
				new->is_black = 0;
				rb_insert_fixup(*root, new);
			}






			iterator insert(iterator position, const value_type& x);
			
			template <class InputIterator>
			void insert(InputIterator first, InputIterator last);

			void erase(iteratorposition);

			size_type erase(const key_type& x);

			void erase(iterator first, iterator last); 
			
			void swap(map<Key,T,Compare,Allocator>&);

			void clear();

	};
};

# endif
