# ifndef RB_TREE_HPP
# define RB_TREE_HPP

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
			typedef typename std::allocator<Value>::template
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

			value_compare 				_compare;
			allocator_type				_alloc;
			node_allocator				_node_alloc;
			size_type					_size;
			node_pointer				_nil;
			node_pointer				_header;
			node_pointer				_root;

			// HELPERS

			node_pointer _min(node_pointer node) const
			{
				node_pointer tmp = node;

				while(tmp && !_is_nill(tmp) && tmp->left && !_is_nill(tmp->left))
					tmp = tmp->left;
				return (tmp);
			}

			node_pointer _max(node_pointer node) const
			{
				node_pointer tmp = node;

				while(tmp && !_is_nill(tmp) && tmp->right && !_is_nill(tmp->right))
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
				_header->data = _alloc.allocate(1);
				_alloc.construct(_header->data, Value());
				_header->is_black = true;
			}

			

			//ROTATION

			void	_left_rotate(node_pointer node)
			{
				node_pointer child = node->right;

				node->right = child->left;
				child->left->parent = node;
				if (!_is_nill(child->left))
					child->left->parent = node;
				child->parent = node->parent;
				if (node->parent == NULL)
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
				if (!_is_nill(child->right))
					child->right->parent = node;
				child->parent = node->parent;
				if (node->parent == NULL)
					_root = child;
				else if (node == node->parent->left)
					node->parent->left = child;
				else if (node == node->parent->right)
					node->parent->right = child;
				child->right = node;
				node->parent = child;
			}

			// CHECKER

			bool	_is_nill(node_pointer node) const
			{
				return (node == _nil || node == _header);
			}

			node_pointer	_search(value_type value, node_pointer node) const
			{
				if (!node || _is_nill(node))
					return (NULL);
				if (_compare(value, *node->data))
					return (_search(value, node->left));
				if (_compare(*node->data, value))
					return (_search(value, node->right));
				return (node);
			}

			//HELPERS FOR PRINTING

			void	_print_node(node_pointer node)
			{
				std::cout <<"Node : " << node << std::endl
				<<"is_root : " << (node == _root) << std::endl
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

			void	_deletion_fixup(node_pointer node)
			{
				node_pointer brother;

				while (node != _root && node->is_black && !_is_nill(node))
				{
					if (node == node->parent->left)
					{
						brother = node->parent->right;
						if (brother->is_black == false)
						{
							brother->is_black = true;
							node->parent->is_black = false;
							_left_rotate(node->parent);
							brother = node->parent->right;
						}
						if (!_is_nill(node))
						{
							if (brother->left->is_black && brother->right->is_black)
							{
								brother->is_black = false;
								node = node->parent;
							}
							else
							{
								if (brother->right->is_black)
								{
									brother->left->is_black = true;
									brother->is_black = false;
									_right_rotate(brother);
									brother = node->parent->right;
								}
								brother->is_black = node->parent->is_black;
								node->parent->is_black = true;
								if (!_is_nill(brother))
									brother->right->is_black = true;
								_left_rotate(node->parent);
								node = _root;
							}
						}
					}
					else
					{
						brother = node->parent->left;
						if (brother->is_black == false)
						{
							brother->is_black = true;
							node->parent->is_black = false;
							_right_rotate(node->parent);
							brother = node->parent->left;
						}
						if (brother->left->is_black && brother->right->is_black)
						{
							brother->is_black = false;
							node = node->parent;
						}
						else
						{
							if (brother->left->is_black)
							{
								brother->right->is_black = true;
								brother->is_black = false;
								_left_rotate(brother);
								brother = node->parent->left;
							}
							brother->is_black = node->parent->is_black;
							node->parent->is_black = true;
							brother->left->is_black = true;
							_right_rotate(node->parent);
							node = _root;
						}		
					}
				}
				node->is_black = true;
			}

			// HELPERS FOR INSERTION
				
			node_pointer	_create_new_node(const value_type& value)
			{
				node_pointer new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node, Node<value_type>());
				new_node->data = _alloc.allocate(1);
				_alloc.construct(new_node->data, value);
				new_node->is_nil = false;
				new_node->is_black = false;
				new_node->left = _nil;
				new_node->right = _nil;
				return (new_node);
			}

			node_pointer	_insert_into_tree(node_pointer root, node_pointer new_node)
			{
				if (_compare(*new_node->data, *root->data))
				{
					if (!_is_nill(root) && !_is_nill(root->left))
						return (_insert_into_tree(root->left, new_node));
					root->left = new_node;
				}
				else
				{
					if (!_is_nill(root) &&!_is_nill(root->right))
						return (_insert_into_tree(root->right, new_node));
					root->right = new_node;
				}
				new_node->parent = root;
				new_node->is_black = false;
				return (new_node);
			}

			void	_inaguration_tree(node_pointer node)
			{
				_root = node;
				_root->parent = NULL;
				_header->parent = _root;
				_root->right = _header;
				node->is_black = true;
			}

			void	_correction_header()
			{
				node_pointer max_of_tree = _max(_root);
				max_of_tree->right = _header;
				_header->parent = max_of_tree;
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
				_root->is_black = true;
			}

			// HELPERS FOR COPYING

			node_pointer _copy_node(node_pointer other)
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
	
			void	_copy_child(node_pointer my_node, node_pointer other)
			{
				if (other->left->is_nil)
					my_node->left = _nil;
				else
				{
					my_node->left = _copy_node(other->left);
					my_node->left->parent = my_node;
					_copy_child(my_node->left, other->left);
				}
				if (other->right->is_nil)
					my_node->right = _nil;
				else if (other->right->right == NULL)
				{
					my_node->right = _header;
					_header->parent = my_node;
				}
				else{
					my_node->right = _copy_node(other->right);
					my_node->right->parent = my_node;
					_copy_child(my_node->right, other->right);
				}
			}

		public:

			RBTree(const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : 
				_compare(comp), _alloc(alloc), _node_alloc(node_allocator()), _size(0) 
			{
				_init_nil_head();
				_root = _header;
			};

			RBTree() : _compare(value_compare()), _alloc(allocator_type()), _node_alloc(node_allocator()), _size(0)
			{
				_init_nil_head();
				_root = _header;
			};

			template<class InputIt>
			RBTree(typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt >::type first, InputIt last,
				const Compare& comp, const allocator_type& alloc = allocator_type()):	_compare(comp),
																						_alloc(alloc),
		   																				_node_alloc(node_allocator()),
																						_size(0)
																						
			{
				_init_nil_head();
				_root = _header;
				for (; first != last; ++first)
					insert(*first);
			}

			RBTree(const RBTree& src) :  _compare(src._compare), _size(0)
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
					this->_root = _copy_node(src._root);
					_copy_child(this->_root, src._root);
				}
				this->_size = src._size;
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

			// external helpers

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
				return (node_allocator().max_size());
			}

			// modifiers:

			pair<iterator, bool>	insert(const value_type& value)
			{
				node_pointer is_existe = _search(value, this->_root);
				if (is_existe && !_is_nill(is_existe))
					return (ft::make_pair(is_existe, false));
				node_pointer new_node = _create_new_node(value);
				if (empty())
					_inaguration_tree(new_node);
				else
				{
					_insert_into_tree(_root, new_node);
					_insert_fixup(new_node);
				}
				_size++;
				_correction_header();
				return (ft::make_pair(new_node, true));
			}

			iterator insert(const_iterator position, const value_type& value)
			{
				node_pointer is_existe = _search(value, _root);
				if (is_existe && !_is_nill(is_existe))
					return (iterator(is_existe));
				node_pointer new_node = _create_new_node(value);
				if (empty())
					_inaguration_tree(new_node);
				else
				{
					if (position == begin() && position != end()
						&& _compare(value, *position))
						_insert_into_tree(_min(_root), new_node);
					else if (position == end() && position != begin()
						&& _compare(*(--position), value))
						_insert_into_tree(_max(_root), new_node);
					else
						_insert_into_tree(_root, new_node);
					_insert_fixup(new_node);
				}
				_size++;
				_correction_header();
				return (iterator(new_node));	
			}

			template <class InputIterator>
			void insert(typename ft::enable_if< !ft::is_integral<InputIterator>::value,
														InputIterator >::type first,
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

			void erase(const_iterator position)
			{
				node_pointer pos = position.get_node();
				node_pointer for_delete = pos;
				node_pointer subtree_replace;
				node_pointer twin = pos;

				if (pos && !_is_nill(pos))
				{
					bool	origin_color = pos->is_black;
					if (pos->left->is_nil)
					{
						subtree_replace = pos->right;
						_rb_transplant(pos, pos->right);
					}
					else if (pos->right->is_nil)
					{
						subtree_replace = pos->left;
						_rb_transplant(pos, pos->left);
					}
					else
					{
						twin = _min(pos->right);
						origin_color = twin->is_black;
						subtree_replace = twin->right;
						if (twin->parent != pos)
						{
							_rb_transplant(twin, twin->right);
							twin->right = pos->right;
							twin->right->parent = twin;
						}
						_rb_transplant(pos,twin);
						twin->left = pos->left;
						twin->left->parent = twin;
						twin->is_black = pos->is_black;
					}
					_clear_node(for_delete); // regarder avec valgrin, au lieu for_delete juste pos. s'il n'y a pas de leak.
					if (origin_color == true)
						_deletion_fixup(subtree_replace);
					_size--;
					if (_size == 0)
						_root = _header;
					else
					{
						if (_size != 1)
							subtree_replace = _max(_root);
						else
							subtree_replace = _root;
						subtree_replace->right = _header;
						_header->parent = subtree_replace;
					}
				}
			}
			
			void erase(const_iterator first, const_iterator last)
			{
				while(first != last)
					erase(first++);
			}
			
			void swap(RBTree &other)
			{
				node_pointer	tmp_root = other._root;
				node_pointer	tmp_nil = other._nil;
				node_pointer	tmp_header = other._header;
				size_type		tmp_size = other._size;
	
				other._root = this->_root;
				other._nil = this->_nil;
				other._header = this->_header;
				other._size = this->_size;

				this->_root = tmp_root;
				this->_nil = tmp_nil;
				this->_header = tmp_header;
				this->_size = tmp_size;
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
				node_pointer resultat = _search(x, _root);
				if (resultat == NULL)
					return (end());
				else
					return (iterator(resultat));
			}

			const_iterator find(const value_type& x) const
			{
				node_pointer resultat = _search(x, _root);
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
					if (!_compare(*it, x))
						return (it);
				return (last);
			}

			const_iterator lower_bound(const value_type& x) const
			{
				const_iterator last = end();
				for (const_iterator it = begin(); it != last; it++)
					if (!_compare(*it, x))
						return (it);
				return (last);
			}

			iterator       upper_bound(const value_type& x)
			{
				iterator last = end();
				for (iterator it = begin(); it != last; it++)
					if (_compare(x, *it))
						return (it);
				return (last);
			}

			const_iterator upper_bound(const value_type& x) const
			{
				const_iterator last = end();
				for (const_iterator it = begin(); it != last; it++)
					if (_compare(x, *it))
						return (it);
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
		return (lhs < rhs);
	}

	template<class Content, class Compare, class Alloc>
	bool operator==(const RBTree<Content, Compare, Alloc>& lhs, const RBTree<Content, Compare, Alloc>& rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
};

# endif
