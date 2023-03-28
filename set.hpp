/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:05:16 by okushnir          #+#    #+#             */
/*   Updated: 2022/08/01 17:05:18 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SET_HPP
# define SET_HPP

# include "iterator.hpp"
# include "utility.hpp"
# include "type_traits.hpp"
# include "RBTree.hpp"



namespace ft {

	template <class Key, class Compare = std::less<Key>,
		class Allocator = std::allocator<Key> >
	class set
	{
		
		public:
			// types:
			typedef Key															key_type;
			typedef Key															value_type;
			typedef Compare														key_compare;
			typedef Compare														value_compare;
			typedef Allocator													allocator_type;
			typedef typename Allocator::reference								reference;
			typedef typename Allocator::const_reference							const_reference;
			typedef typename Allocator::pointer									pointer;
			typedef typename Allocator::const_pointer							const_pointer;
			typedef std::size_t													size_type;
			typedef std::ptrdiff_t												difference_type;

			typedef RBTree<key_type, key_compare, allocator_type>				tree_type;
			typedef typename tree_type::const_iterator							iterator;
			typedef	typename tree_type::const_iterator							const_iterator;
			typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;

			
		private:

			key_compare		_compare;
			tree_type		_tree;

			operator	const_iterator()
			{
				return const_iterator(iterator());
			}

		public:

			// construct/copy/destroy:
			
			explicit set(const Compare& comp = Compare(), const Allocator& alloc = Allocator()) :
				_tree(comp, alloc) {} ;

			template <class InputIterator>
			set(InputIterator first, InputIterator last,
				const Compare& comp = Compare(), const Allocator& alloc = Allocator()) :
					_tree(tree_type(first, last, comp, alloc))
			{
				while (first != last)
					_tree.insert(*first++);
			}

			set(const set<Key,Compare,Allocator>& other) : _compare(other._compare), _tree(other._tree)
			{
				*this = other;
			}

			set<Key,Compare,Allocator>& operator=(const set<Key,Compare,Allocator>& x)
			{
				_compare = x._compare;
				_tree = x._tree;
				return (*this);
			}

			~set() {};

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
				return (_tree.erase(x));
			}

			void erase(iterator first, iterator last)
			{

				_tree.erase(first, last);
			} 
			
			void swap(set<Key,Compare,Allocator>& x)
			{
				_tree.swap(x._tree);
			}

			void clear()
			{
				_tree.clear();
			}

			// observers:
			key_compare key_comp() const
			{
				return (value_compare());
			}

			value_compare value_comp() const
			{
				return (_tree.get_compare());
			}

			// map operations:
			
			iterator find(const key_type& x)
			{
				return (_tree.find(x));
			}
			
			const_iterator find(const key_type& x) const
			{
				return (_tree.find(x));
			}
			
			size_type count(const key_type& x) const
			{
				return (_tree.count(x));

			}

			iterator	lower_bound(const key_type& x)
			{
				return (_tree.lower_bound(x));
			}

			const_iterator	lower_bound(const key_type& x) const
			{
				return (_tree.lower_bound(x));
			}

			iterator	upper_bound(const key_type& x)
			{
				return (_tree.upper_bound(x));
			}

			const_iterator	upper_bound(const key_type& x) const
			{
				return (_tree.upper_bound(x));
			}

			pair<iterator,iterator> equal_range(const key_type& x)
			{
				return (_tree.equal_range(x));
			}

			pair<const_iterator,const_iterator> equal_range(const key_type& x) const
			{
				return (_tree.equal_range(x));
			}

			allocator_type get_allocator() const
			{
				return (allocator_type());
			}
	};

		template <class Key, class Compare, class Allocator>
		bool operator==(const set<Key,Compare,Allocator>& x,
						const set<Key,Compare,Allocator>& y)
		{
			return (x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()));
		}

		template <class Key, class Compare, class Allocator>
		bool operator< (const set<Key,Compare,Allocator>& x,
						const set<Key,Compare,Allocator>& y)
		{
			return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
		}

		template <class Key, class Compare, class Allocator>
		bool operator!=(const set<Key,Compare,Allocator>& x,
						const set<Key,Compare,Allocator>& y)
		{
			return !(x == y);
		}

		template <class Key, class Compare, class Allocator>
		bool operator> (const set<Key,Compare,Allocator>& x,
						const set<Key,Compare,Allocator>& y)
		{
			return (y < x);
		}

		template <class Key, class Compare, class Allocator>
		bool operator>=(const set<Key,Compare,Allocator>& x,
						const set<Key,Compare,Allocator>& y)
		{
			return !(x < y);
		}

		template <class Key, class Compare, class Allocator>
		bool operator<=(const set<Key,Compare,Allocator>& x,
						const set<Key,Compare,Allocator>& y)
		{
			return !(x > y);
		}

		// specialized algorithms:
		template <class Key, class Compare, class Allocator>
		void swap(set<Key,Compare,Allocator>& x,
					set<Key,Compare,Allocator>& y)
		{
			x.swap(y);
		}
};

# endif
