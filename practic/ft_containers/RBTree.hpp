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

	template <class Value>
	struct Node1
	{
		public:

			Value		*data;
			Node1 		*parent;
			Node1 		*left;
			Node1 		*right;
			bool		is_nil;
			bool		is_black;
	};


	template <class Value, class Compare = std::less<Value>, class Allocator = std::allocator<Value> >
	class RBTree
	{
		public:
			typedef Value												value_type;
			typedef Compare												value_compare;
			typedef Allocator											allocator_type;
			typedef typename std::allocator<Value>::template
									rebind<Node<value_type> >::other	node_allocator;
			typedef typename std::allocator<ft::Node<typename value_type::first_type> >		node_allocatorS;
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

				while(tmp != NULL && !_is_nill(tmp) && tmp->left != NULL && !tmp->left->is_nil)
					tmp = tmp->left;
				return (tmp);
			}

			node_pointer _max(node_pointer node) const
			{
				node_pointer tmp = node;

				while(tmp != NULL &&  !_is_nill(tmp) && tmp->right && !tmp->right->is_nil && tmp->right != _header)
					tmp = tmp->right;
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
				// _header->is_nil = false;
				_header->is_black = true;
				_header->data = _alloc.allocate(1);
				_alloc.construct(_header->data, Value());
			}

			bool	_is_root(node_pointer node)
			{
				return (node == _root);
			}
			
			bool	_is_nill(node_pointer node) const
			{
				return (node->is_nil || node == _header);
			}

			bool	_is_header(node_pointer node) const
			{
				return (node == _header);
			}

			//ROTATION

			void	_left_rotate(node_pointer node)
			{
				node_pointer child = node->right;

				node->right = child->left;
				child->left->parent = node;
				if (!_is_nill(child->left) && !_is_header(child->left))
					child->left->parent = node;
				child->parent = node->parent;
				if (node->parent == NULL)// 1st change
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
				if (!_is_nill(child->right) && !_is_header(child->right))
					child->right->parent = node;
				child->parent = node->parent;
				if (node->parent == NULL)// 1st change
					_root = child;
				else if (node == node->parent->left)
					node->parent->left = child;
				else if (node == node->parent->right)
					node->parent->right = child;
				child->right = node;
				node->parent = child;
			}

			// CHECKER

			node_pointer	search(value_type value, node_pointer node) const
			{
				if (!node || _is_nill(node) || _is_header(node))
					return (NULL);
				if (_compare(value, *node->data))
					return (search(value, node->left));
				if (_compare(*node->data, value))
					return (search(value, node->right));
				return (node);
			}

			//HELPERS FOR PRINTING

			void	_print_node(node_pointer node)
			{
				std::cout <<"Node : " << node << std::endl
				<<"is_root : " << _is_root(node) << std::endl
				<<"data : " << node->data->first << std::endl
				<<"is_black : " << node->is_black << std::endl
				<<"is_nil : " << node->is_nil << std::endl
				<<"left : " << ( _is_nill(node->left) ? 0 : node->left->data->first) << " address : " << node->left  << std::endl
				<<"right : " << (_is_nill(node->right)? 0 :node->right->data->first) << " address : " << node->right << std::endl
				<<"parent : " << node->parent->data->first << " address : " << node->parent << std::endl
				<<"root : " << _root->data->first << " address : " << _root << std::endl << std::endl << std::endl;
			}

			// HELPERS FOR DELETION

			void	_rb_transplant(node_pointer old, node_pointer new_node)
			{
				if (old == _root)
					_root = new_node;
				else if (old == old->parent->left)
					old->parent->left = new_node;
				else
					old->parent->right = new_node;
				new_node->parent = old->parent;
			}

			void	_clear_node(node_pointer node)
			{
				_alloc.destroy(node->data);
				_alloc.deallocate(node->data, 1);
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
			}

			void	_clear_tree(node_pointer root)
			{
				if (!root || root->is_nil || root == _header)
					return;
				_clear_tree(root->left);
				_clear_tree(root->right);
				_alloc.destroy(root->data);
				_alloc.deallocate(root->data, 1);
				_node_alloc.destroy(root);
				_node_alloc.deallocate(root, 1);
			}

			void	_deletion_fixup(node_pointer x)
			{
				node_pointer w;

				while (x != _root && x->is_black && !_is_nill(x))
				{
					// std::cout << "!!!x->is_nil: " << x->is_nil  << "\n";
					if (x == x->parent->left)
					{
						w = x->parent->right;
						if (w->is_black == false)
						{
							w->is_black = true;
							x->parent->is_black = false;
							_left_rotate(x->parent);
							w = x->parent->right;
						}
						if (!_is_nill(x))
						{
							if (w->left->is_black && w->right->is_black)
							{
								w->is_black = false;
								x = x->parent;
							}
							else
							{
								if (w->right->is_black)
								{
									w->left->is_black = true;
									w->is_black = false;
									_right_rotate(w);
									w = x->parent->right;
								}
								w->is_black = x->parent->is_black;
								x->parent->is_black = true;
								if (!_is_nill(w))
									w->right->is_black = true;
								// std::cout << "x->is_nil: " << x->is_nil  << "\n";
								_left_rotate(x->parent);
								x = _root;
							}
						}
					}
					else
					{
						w = x->parent->left;
						if (w->is_black == false)
						{
							w->is_black = true;
							x->parent->is_black = false;
							_right_rotate(x->parent);
							w = x->parent->left;
						}
						if (w->left->is_black && w->right->is_black)
						{
							w->is_black = false;
							x = x->parent;
						}
						else
						{
							if (w->left->is_black)
							{
								w->right->is_black = true;
								w->is_black = false;
								_left_rotate(w);
								w = x->parent->left;
							}
							w->is_black = x->parent->is_black;
							x->parent->is_black = true;
							w->left->is_black = true;
							_right_rotate(x->parent);
							x = _root;
						}		
					}
				}
				x->is_black = 1;
			}

			// HELPERS FOR INSERTION

			pointer	_create_value(const value_type &value)
			{
				pointer new_val = _alloc.allocate(1);
				_alloc.construct(new_val, value);
				return new_val;
			}
				
			node_pointer	_create_new_node(const value_type& value)
			{
				node_pointer new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node, Node<value_type>(_create_value(value)));
				new_node->is_nil = false;
				new_node->is_black = false;
				new_node->left = _nil;
				new_node->right = _nil;
				return (new_node);
			}

			node_pointer	_insert_to_node(node_pointer root, node_pointer new_node)
			{
				if (_compare(*new_node->data, *root->data))
				{
					if (!_is_nill(root) && !_is_nill(root->left) && !_is_header(root->left))
						return (_insert_to_node(root->left, new_node));
					root->left = new_node;
				}
				else
				{
					if (!_is_nill(root) && root != _header &&!_is_nill(root->right) && !_is_header(root->left)) // 2nd change
						return (_insert_to_node(root->right, new_node));
					root->right = new_node;
				}
				new_node->parent = root;
				return (new_node);
			}
		
			node_pointer _insert_into_tree(node_pointer new_node, node_pointer where)
			{
				if (_root == _header)
					_root = new_node;
				else
					_insert_to_node(where, new_node);
				return (new_node);
			}

			void	_insert_fixup(node_pointer node)
			{
				node_pointer oncle;
				if (node != _root && node->parent != _root)
				{
					while (node != _root && node->parent->is_black == false)
					{
						if (node->parent == node->parent->parent->left)
						{
							oncle = node->parent->parent->right;
							if (oncle->is_black == false)
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

			node_pointer copy_node(node_pointer other)
			{
				node_pointer new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node, Node<Value>());
				new_node->is_black = other->is_black;
				new_node->is_nil = other->is_nil;
				if (other->data)
				{
					new_node->data = _alloc.allocate(1);
					_alloc.construct(new_node->data, *other->data);
				}
				return (new_node);
			}
	
			void	copy_child(node_pointer my_node, node_pointer other)
			{
				if (other->left->is_nil)
					my_node->left = _nil;
				else
				{
					my_node->left = copy_node(other->left);
					my_node->left->parent = my_node;
					copy_child(my_node->left, other->left);
				}
				if (other->right->is_nil)
					my_node->right = _nil;
				else if (other->right->right == NULL)//3rd change
				{
					my_node->right = _header;
					_header->parent = my_node;
				}
				else{
					my_node->right = copy_node(other->right);
					my_node->right->parent = my_node;
					copy_child(my_node->right, other->right);
				}
			}

		public:

			// CONSTRUCTORS

			// allocator_type				_alloc;
			// node_allocator				_node_alloc;
			// value_compare 				_compare;
			// node_pointer				_nil;
			// node_pointer				_header;
			// node_pointer				_root;
			// size_type					_size;

			RBTree(const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : 
				 _alloc(alloc), _node_alloc(node_allocator()), _compare(comp), _size(0) 
			{
				_init_nil_head();
				_root = _header;
			};

			RBTree() : _alloc(allocator_type()), _node_alloc(node_allocator()), _compare(value_compare()), _size(0)
			{
				_init_nil_head();
				_root = _header;
			};

			template<class InputIt>
			RBTree(typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt >::type first, InputIt last,
				const Compare& comp, const allocator_type& alloc = allocator_type()):	_alloc(alloc),
		   																				_node_alloc(node_allocator()),
																						_compare(comp)
			{
				_init_nil_head();
				_root = _header;
				for (; first != last; ++first)
					insert(*first);
			}

			RBTree(const RBTree& src) :  _compare(src._compare), _root(NULL)
			{
				*this = src;
			}

			RBTree& operator=(const RBTree& src)
			{
				if (this == &src)
					return *this;
				if (!this->_root)
					_init_nil_head();
				else
					_clear_tree(_root);
				if (src._size == 0)
					this->_root = this->_header;
				else
				{
					this->_root = copy_node(src._root);
					copy_child(this->_root, src._root);
				}
				this->_size = src._size;//4th change
				this->_node_alloc = src._node_alloc;
				this->_alloc = src._alloc;
				this->_compare = src._compare;
				return *this;
			}

			~RBTree()
			{
				if(_root != _header)
				{
					_clear_tree(_root);
				}
				_node_alloc.destroy(_nil);
				_node_alloc.deallocate(_nil, 1);
				_alloc.destroy(_header->data);
				_alloc.deallocate(_header->data, 1);
				_node_alloc.destroy(_header);
				_node_alloc.deallocate(_header, 1);
			};

			// iterators:

			iterator begin()
			{
				if (_size == 0)
					return (iterator(_header));
				else
					return (iterator(_min(_root)));
			}
			
			const_iterator begin() const
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

			size_type max_size() const
			{
				typedef std::allocator<Node1<Value> > allocator_type_m;

				return (allocator_type_m().max_size() );
			}

			void	print_tree(node_pointer root)
			{
				if (!root || root->is_nil)
					return;
				_print_node(root);
				print_tree(root->left);
				print_tree(root->right);
			}

			node_pointer get_root()
			{
				return (_root);
			}

			
			// modifiers:

			pair<iterator, bool>	insert(const value_type& value) // value_type = pair
			{
				node_pointer is_existe = search(value, this->_root);
				if (is_existe && !_is_nill(is_existe) && !_is_header(is_existe))
					return (ft::make_pair(is_existe, false));
				node_pointer new_node = _create_new_node(value);
				if (_root == _header)
				{
					_root = new_node;
					_root->parent = NULL; //5th change!
					_header->parent = _root; //6th change!
					_root->right = _header; //9th change!
					new_node->is_black = true;
					_size++;
					return (ft::make_pair(new_node, true));
				}
				node_pointer y = NULL;
				node_pointer x = _root;
				int i = 0;
				while (!_is_nill(x) && !_is_header(x))
				{
					y = x;
					if (_compare(*new_node->data, *x->data))
					{
						x = x->left;
					}
					else
					{
						x = x->right;
					}
					
					i++;
				}
				new_node->parent = y;
				if (_compare(*new_node->data, *y->data)) // _change_comp
					y->left = new_node;
				else
					y->right = new_node;
				new_node->is_black = 0;
				_insert_fixup(new_node);
				_size++;
				node_pointer max_of_tree = _max(_root);//
				max_of_tree->right = _header;//
				_header->parent = max_of_tree;// 12th change
				return (ft::make_pair(new_node, true));
			}

			iterator insert(iterator position, const value_type& value)
			{
				node_pointer is_existe = search(value, _root);
				if (is_existe && !_is_nill(is_existe) && !_is_header(is_existe))
					return (iterator(is_existe));
				node_pointer new_node = _create_new_node(value);
				if (_root == _header)
				{
					_root = new_node;
					_root->parent = NULL; //5th change!
					_header->parent = _root; //6th change!
					_root->right = _header; //9th change!
					new_node->is_black = true;
					_size++;
					return (iterator(new_node));
				}
				if (position == begin())
				{
					if (position != end() && _compare(value, *position))
						_insert_into_tree(new_node, _min(_root));
					else
						_insert_into_tree(new_node, _root);
				}
				else if (position == end())
				{
					if (position != begin() && _compare(*(--position), value))
						_insert_into_tree(new_node, _header->parent);
					else
						_insert_into_tree(new_node, _root);
				}
				else
					_insert_into_tree(new_node, _root);
				_insert_fixup(new_node);
				_size++;
				node_pointer max_of_tree = _max(_root);//
				max_of_tree->right = _header;//
				_header->parent = max_of_tree;// 12th change
				return (iterator(new_node));	
			}

			template <class InputIterator>
			void insert(typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type first,
				InputIterator last)
			{
				for (; first != last; ++first)
					insert(*first);
			}

			size_type erase(const value_type& x)
			{
				iterator position = find(x);


				if (position != end())
					erase(position);
				return (position != end());
			}

			void erase(iterator position)
			{
				node_pointer z = position.get_node();
				node_pointer for_delete = z;
				node_pointer x;
				node_pointer y = z;

				if (z && !_is_nill(z) && !_is_header(z))
				{
					bool	origin_color = z->is_black;
					if (z->left->is_nil)
					{
						x = z->right;
						_rb_transplant(z, z->right);
					}
					else if (z->right->is_nil)
					{
						x = z->left;
						_rb_transplant(z, z->left);
					}
					else
					{
						y = _min(z->right);
						origin_color = y->is_black;
						x = y->right;
						// if (y->parent == z)
						// 	x->parent = y;
						if (y->parent != z)
						{
							_rb_transplant(y, y->right);
							y->right = z->right;
							y->right->parent = y;
						}
						_rb_transplant(z,y);
						y->left = z->left;
						y->left->parent = y;
						y->is_black = z->is_black;
					}
					_clear_node(for_delete);
					if (origin_color == true)
						_deletion_fixup(x);
					_size--;
					_nil->parent = NULL;//13th change
					if (_size == 0)
						_root = _header;
					else // 7th change
					{
						if (_size != 1)
							x = _max(_root);
						else
							x = _root;
						x->right = _header;
						_header->parent = x;
					}
				}
			}

			void erase(iterator first, iterator last)
			{
				while(first != last)
					erase(first++);
			}
			
			void swap(RBTree &other)
			{
				allocator_type	tmp_alloc = other._alloc;
				node_allocator	tmp_node_alloc = _node_alloc;
				value_compare 	tmp_compare = other._compare;
				node_pointer	tmp_nil =other. _nil;
				node_pointer	tmp_header = other._header;
				node_pointer	tmp_root = other._root;
				size_type		tmp_size = other._size;
	
				other._root = this->_root;
				other._nil = this->_nil;
				other._header = this->_header;
				other._size = this->_size;
				other._node_alloc = this->_node_alloc;
				other._alloc = this->_alloc;
				other._compare = this->_compare;

				this->_root = tmp_root;
				this->_nil = tmp_nil;
				this->_header = tmp_header;
				this->_size = tmp_size;
				this->_node_alloc = tmp_node_alloc;
				this->_alloc = tmp_alloc;
				this->_compare = tmp_compare;
			}

			void clear()
			{
				_clear_tree(_root);
				_root = _header;
				_header->parent = NULL;
				_size = 0;
			}

			// observers:
			value_compare get_compare() const
			{
				return (_compare);
			}

			// map operations:

			iterator find(const value_type& x)
			{
				node_pointer resultat = search(x, _root);
				if (resultat == NULL)
					return (end());
				else
					return (iterator(resultat));
			}

			const_iterator find(const value_type& x) const
			{
				node_pointer resultat = search(x, _root);
				if (resultat == NULL)
					return (end());
				else
					return (const_iterator(resultat));
			}

			size_type count(const value_type& x) const
			{
				return (find(x) != end());
			}

			iterator	lower_bound(const value_type& x)
			{
				iterator last = end();
				for (iterator it = begin(); it != last; it++)
				{
					if (!_compare(*it, x))
						return (it);
				}
				return (last);
			}

			const_iterator lower_bound(const value_type& x) const
			{
				const_iterator last = end();
				for (const_iterator it = begin(); it != last; it++)
				{
					if (!_compare(*it, x))
						return (it);
				}
				return (last);
			}

			iterator       upper_bound(const value_type& x)
			{
				iterator last = end();
				for (iterator it = begin(); it != last; it++)
				{
					if (_compare(x, *it))
						return (it);
				}
				return (last);
			}

			const_iterator upper_bound(const value_type& x) const
			{
				const_iterator last = end();
				for (const_iterator it = begin(); it != last; it++)
				{
					if (_compare(x, *it))
						return (it);
				}
				return (last);
			}

			ft::pair<iterator, iterator> equal_range(const value_type& x)
			{
				return (make_pair(lower_bound(x), upper_bound(x)));
			}

			ft::pair<const_iterator,const_iterator> equal_range(const value_type& x) const
			{
				return (make_pair(lower_bound(x), upper_bound(x)));
			}
			

	};

	template<class Content, class Compare, class Alloc>
	bool operator<(const RBTree<Content, Compare, Alloc>& lhs,  const RBTree<Content, Compare, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Content, class Compare, class Alloc>
	bool operator>(const RBTree<Content, Compare, Alloc>& lhs,  const RBTree<Content, Compare, Alloc>& rhs)
	{
		return (lhs < rhs);// erreur possible
	}


	template<class Content, class Compare, class Alloc>
	bool operator==(const RBTree<Content, Compare, Alloc>& lhs, const RBTree<Content, Compare, Alloc>& rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
};

# endif
