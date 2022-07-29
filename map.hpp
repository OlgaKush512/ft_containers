# ifndef MAP_HPP
# define MAP_HPP

# include "iterator.hpp"
# include "utility.hpp"
# include "type_traits.hpp"
# include "RBTree.hpp"



namespace ft {

	template <class Key, class T, class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		
		public:
			// types:
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef pair<const Key, T>									value_type;
			typedef Compare												key_compare;
			typedef Allocator											allocator_type;
			typedef typename Allocator::reference						reference;
			typedef typename Allocator::const_reference					const_reference;
			typedef typename Allocator::pointer							pointer;
			typedef typename Allocator::const_pointer					const_pointer;
			typedef std::size_t											size_type;
			typedef std::ptrdiff_t										difference_type;

			

		private: 

			class value_compare
			{
				friend class map;
				protected:

					key_compare comp;
					value_compare(Compare c) : comp(c) {};

				public:

					bool operator()(const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

			
		public:

			typedef RBTree<value_type, value_compare, allocator_type>			tree_type;
			typedef typename tree_type::iterator								iterator;
			typedef	typename tree_type::const_iterator							const_iterator;
			typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;

			
		private:

			key_compare		_compare;
			allocator_type	_alloc;
			tree_type		_tree;

		public:

			// construct/copy/destroy:
			
			explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : _compare(comp),
				_alloc(alloc),_tree(comp, alloc) {} ;

			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const Compare& comp = Compare(), const Allocator& alloc = Allocator()) :
				 _compare(comp), _alloc(alloc), _tree(tree_type(first, last, comp, alloc)) {} ;

			map(const map<Key,T,Compare,Allocator>& other) : 
				_compare(other._compare), _alloc(other._alloc),  _tree(other._tree)
			{
				*this = other;
			}

			map<Key,T,Compare,Allocator>& operator=(const map<Key,T,Compare,Allocator>& x)
			{
				_compare = x._compare;
				_alloc = x._alloc;
				_tree = x._tree;
				return (*this);
			}

			~map() {};

			// HELPERS

			void	print_map()
			{
				_tree.print_tree(_tree.get_root());
			}

			// iterators:
			iterator begin()
			{
				return (_tree.begin());
			}
			
			const_iterator begin() const
			{
				return (_tree.begin());
			}
			
			iterator end()
			{
				return (_tree.end());
			}
			
			const_iterator end() const
			{
				return (_tree.end());
			}
			
			reverse_iterator rbegin()
			{
				return (_tree.rbegin());
			}
			
			const_reverse_iterator rbegin() const
			{
				return (_tree.rbegin());
			}
			
			reverse_iterator rend()
			{
				return (_tree.rend());
			}
			
			const_reverse_iterator rend() const
			{
				return (_tree.rend());
			}

			// capacity:
			bool empty() const
			{
				return (_tree.empty());
			}

			size_type size() const
			{
				return (_tree.size());
			}

			size_type max_size() const
			{
				return (_tree.max_size());
			}

			// element access:

			T& operator[](const key_type& x)
			{
				return ((*((this->insert(ft::make_pair(x,mapped_type()))).first)).second);
			}


			// modifiers:
			pair<iterator, bool>	insert(const value_type& x)
			{
				return(_tree.insert(x));
			}

			iterator insert(iterator position, const value_type& x)
			{
				return(_tree.insert(position, x));
			}
			
			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				_tree.insert(first, last);
			}

			void erase(iterator position)
			{
				_tree.erase(position);
			}

			size_type erase(const key_type& x)
			{
				return (_tree.erase(ft::make_pair(x, mapped_type())));
			}

			void erase(iterator first, iterator last)
			{
				_tree.erase(first, last);
			} 
			
			void swap(map<Key,T,Compare,Allocator>& x)
			{
				key_compare		tmp_compare = x._compare;
				allocator_type	tmp_alloc = x._alloc;

				x._compare = _compare;
				x._alloc = _alloc;
				_compare = tmp_compare;
				_alloc = tmp_alloc;

				_tree.swap(x._tree);
			}

			void clear()
			{
				_tree.clear();
			}

			// observers:
			key_compare key_comp() const
			{
				return (_compare);
			}

			value_compare value_comp() const
			{
				return (_tree.get_compare());
			}

			// map operations:
			
			iterator find(const key_type& x)
			{
				return (_tree.find(ft::make_pair(x, mapped_type())));
			}
			
			const_iterator find(const key_type& x) const
			{
				return (_tree.find(ft::make_pair(x, mapped_type())));
			}
			
			size_type count(const key_type& x) const
			{
				return (_tree.count(ft::make_pair(x, mapped_type())));

			}

			iterator	lower_bound(const key_type& x)
			{
				return (_tree.lower_bound(ft::make_pair(x, mapped_type())));
			}

			const_iterator	lower_bound(const key_type& x) const
			{
				return (_tree.lower_bound(ft::make_pair(x, mapped_type())));
			}

			iterator	upper_bound(const key_type& x)
			{
				return (_tree.upper_bound(ft::make_pair(x, mapped_type())));
			}

			const_iterator	upper_bound(const key_type& x) const
			{
				return (_tree.upper_bound(ft::make_pair(x, mapped_type())));
			}

			pair<iterator,iterator> equal_range(const key_type& x)
			{
				return (_tree.equal_range(ft::make_pair(x, mapped_type())));
			}

			pair<const_iterator,const_iterator> equal_range(const key_type& x) const
			{
				return (_tree.equal_range(ft::make_pair(x, mapped_type())));
			}

			allocator_type get_allocator() const
			{
				return (_alloc);
			}

	};

	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key,T,Compare,Allocator>& x,
					const map<Key,T,Compare,Allocator>& y)
	{
		return (x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()));
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator< (const map<Key,T,Compare,Allocator>& x,
					const map<Key,T,Compare,Allocator>& y)
	{
		return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key,T,Compare,Allocator>& x,
					const map<Key,T,Compare,Allocator>& y)
	{
		return !(x == y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator> (const map<Key,T,Compare,Allocator>& x,
					const map<Key,T,Compare,Allocator>& y)
	{
		return (y < x);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key,T,Compare,Allocator>& x,
					const map<Key,T,Compare,Allocator>& y)
	{
		return !(x < y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key,T,Compare,Allocator>& x,
					const map<Key,T,Compare,Allocator>& y)
	{
		return !(x > y);
	}

	// specialized algorithms:
	template <class Key, class T, class Compare, class Allocator>
	void swap(map<Key,T,Compare,Allocator>& x,
				map<Key,T,Compare,Allocator>& y)
	{
		x.swap(y);
	}
};

# endif
