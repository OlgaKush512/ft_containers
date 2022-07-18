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


			typedef typename std::size_t								size_type;
			typedef typename std::ptrdiff_t								difference_type;

			

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
				_nil->is_black = true;
				_header = _node_alloc.allocate(1);
				_node_alloc.construct(_header, Node<Value>());
				_header->is_nil = false;
				_header->is_black = true;
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

			bool	_is_header(node_pointer node)
			{
				return (node == _header);
			}

			//ROTATION

			void	_left_rotate(node_pointer node)
			{
				node_pointer child = node->right;

				node->right = child->left;
				child->left->parent = node;
				child->parent = node->parent;
				if (node->parent == _header)
					_root = child;
				else if (node == node->parent->left)
					node->parent->left = child;
				else
					node->parent->right = child;
				child->left = node;
				node->parent = child;
			}

			void	_right_rotate(node_pointer node)
			{
				node_pointer child = node->left;

				node->left = child->right;
				child->right->parent = node;
				child->parent = node->parent;
				if (node->parent == _header)
					_root = child;
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
				if (!node || _is_nill(node))
					return (NULL);
				if (_compare(value, *node->data))
					return (search(value, node->left));
				if (_compare(*node->data, value))
					return (search(value, node->right));
				return (node);
			}

			//PRINTING

			

		public:

			// CONSTRUCTORS

			RBTree(const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : 
				_alloc(alloc), _compare(comp), _size(0)
			{
				_init_nil_head();
				_root = _header;
			};

			RBTree() : _alloc(allocator_type()), _compare(value_compare()), _size(0)
			{
				_init_nil_head();
				_root = _header;
			};
			// RBTree() {}; // range
			RBTree(RBTree&) {}; // copy
			RBTree& operator=(RBTree&) {}; // =

			~RBTree()
			{
				if(_root != _header)
				{
					clear_tree(_root);
				}
				_node_alloc.destroy(_nil);
				_node_alloc.deallocate(_nil, 1);
				_alloc.destroy(_header->data);
				_alloc.deallocate(_header->data, 1);
				_node_alloc.destroy(_header);
				_node_alloc.deallocate(_header, 1);

			};

			void	clear_tree(node_pointer root)
			{
				if (!root || root->is_nil)
					return;
				clear_tree(root->left);
				clear_tree(root->right);
				_alloc.destroy(root->data);
				_alloc.deallocate(root->data, 1);
				_node_alloc.destroy(root);
				_node_alloc.deallocate(root, 1);
			}
		

			// iterators:

			iterator begin()
			{
				if (_size == 0)
					return (iterator(_header));
				else
					return (iterator(_min(_root)));
			}
			
			const_iterator begin()const
			{
				if (_size == 0)
					return (const_iterator(_header));
				else
					return (const_iterator(_min(_root)));
			}
			
			iterator end()
			{
				return (iterator(_header));
			}
			
			const_iterator end()const
			{
				return (const_iterator(_header));
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

			// void	print_node(node_pointer node)
			// {
			// 	std::cout <<"Node : " << &node << std::endl
			// 	<<"is_root : " << _is_root(node) << std::endl
			// 	<<"data : " << node->data->first << std::endl
			// 	<<"is_black : " << node->is_black << std::endl
			// 	<<"is_nil : " << node->is_nil << std::endl
			// 	<<"left : " << ( _is_nill(node->left)? 0 : node->left->data->first) << " address : " << node->left << std::endl
			// 	<<"right : " << (_is_nill(node->right)? 0 :node->right->data->first) << " address : " << node->right << std::endl
			// 	<<"parent : " << node->parent->data->first << " address : " << node->parent << std::endl
			// 	<<"root : " << _root->data->first << " address : " << _root << std::endl << std::endl << std::endl;
			// }

			void	print_tree(node_pointer root)
			{
				if (!root || root->is_nil)
					return;
				print_node(root);
				print_tree(root->left);
				print_tree(root->right);
			}

			node_pointer get_root()
			{
				return (_root);
			}

			// modifiers:

			void	rb_insert_fixup(node_pointer node)
			{
				node_pointer oncle;
				if (node != _root && node->parent != _root)
				{
					while (node != _root && node->parent->is_black == false)
					{
						if (node->parent == node->parent->parent->left)
						{
							oncle = node->parent->parent->right;
							if (oncle->is_black == false || _is_nill(oncle))
							{
								node->parent->is_black = true;
								oncle->is_black = true;
								node->parent->parent->is_black = false;
								node = node->parent->parent;
							}
							else
							{
								if (node == node->parent->right)
								{
									node = node->parent;
									_left_rotate(node);
								}
								node->parent->is_black = true;
								node->parent->parent->is_black = false;
								_right_rotate(node->parent->parent);
							}
						}
						else
						{
							oncle = node->parent->parent->left;
							if (oncle->is_black == false)
							{
								node->parent->is_black = true;
								oncle->is_black = true;
								node->parent->parent->is_black = false;
								node = node->parent->parent;
							}
							else
							{
								if (node == node->parent->left)
								{
									node = node->parent;
									_right_rotate(node);
								}
								node->parent->is_black = true;
								node->parent->parent->is_black = false;
								_left_rotate(node->parent->parent);
							}
						}
					}
				}
				_root->is_black = 1;
			}

			pointer	create_value(const value_type &value)
			{
				pointer new_val = _alloc.allocate(1);
				_alloc.construct(new_val, value);
				return new_val;
			}
				
			void	print_node(node_pointer node)
			{
				std::cout <<"Node : " << node << std::endl
				<<"is_root : " << _is_root(node) << std::endl
				<<"data : " << node->data->first << std::endl
				<<"is_black : " << node->is_black << std::endl
				<<"is_nil : " << node->is_nil << std::endl
				<<"left : " << ( _is_nill(node->left)? 0 : node->left->data->first) << " address : " << node->left << std::endl
				<<"right : " << (_is_nill(node->right)? 0 :node->right->data->first) << " address : " << node->right << std::endl
				<<"parent : " << node->parent->data->first << " address : " << node->parent << std::endl
				<<"root : " << _root->data->first << " address : " << _root << std::endl << std::endl << std::endl;
			}


			pair<iterator, bool>	insert(const value_type& value) // value_type = pair
			{
				node_pointer is_existe = search(value, this->_root);
				if (is_existe && !_is_nill(is_existe) && !_is_header(is_existe))
				{
					std:: cout << "node exist\n";
					return (ft::make_pair(is_existe, false));

				}

				
				node_pointer new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node, Node<value_type>(create_value(value)));
				new_node->is_nil = false;
				new_node->is_black = false;
				new_node->left = _nil;
				new_node->right = _nil;
				if (_root == _header)
				{
					// std:: cout << "C'est le premier node : \n\n\n";
					_root = new_node;
					new_node->parent = _header;
					new_node->is_black = true;
					// print_node(new_node);
					// std:: cout << "\n\n\n";
					return (ft::make_pair(new_node, true));
				}
				node_pointer y = NULL;
				node_pointer x = _root;
				while (!_is_nill(x))
				{
					y = x;
					// std:: cout << "new_node->data : " << new_node->data <<  " new_node->data : " <<x->data << "\n\n";
					if (new_node->data->first < x->data->first)
						x = x->left;
					else
						x = x->right;
				}
				new_node->parent = y;
				std:: cout << "new_node->parent->data : " << new_node->parent->data->first <<  " new_node->data : " <<new_node->data->first << "\n\n";
				if (new_node->data->first < y->data->first)
					y->left = new_node;
				else
					y->right = new_node;
				new_node->is_black = 0;

				// std:: cout << "before fix : \n\n\n";
				// print_node(new_node);
				// std:: cout << "\n\n\n";
				rb_insert_fixup(new_node);
				std:: cout << "new_node->parent->data : " << new_node->parent->data->first <<  " new_node->data : " <<new_node->data->first << "\n\n";
				_size++;
				// print_node(new_node);
				// std::cout << std::endl << std::endl;
				return (ft::make_pair(new_node, true));
			}


			// iterator insert(iterator position, const value_type& x);
			
			// template <class InputIterator>
			// void insert(InputIterator first, InputIterator last);

			// void erase(iterator position);

			// size_type erase(const key_type& x);

			// void erase(iterator first, iterator last); 
			
			// void swap(map<Key,T,Compare,Allocator>&);

			// void clear();

	};
};

# endif
