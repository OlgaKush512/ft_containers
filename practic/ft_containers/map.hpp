# ifndef MAP_HPP
# define MAP_HPP

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

			typedef RBTree<value_type, value_compare, allocator_type>	tree_type;
			typedef tree_type::iterator									iterator;
			typedef	tree_type::const_iterator							const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

			
		private:

			allocator_type	_alloc;
			tree_type		_tree;
			key_compare		_compare;

		public:

			// construct/copy/destroy:
			
			explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator()) :
				_alloc(alloc), _compare(comp), _tree(tree_type(alloc, comp)) {} ;

			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const Compare& comp = Compare(), const Allocator& alloc = Allocator()) :
				_alloc(alloc), _compare(comp), _tree(tree_type(first, last, alloc, comp)) {} ;

			map(const map<Key,T,Compare,Allocator>& other) : 
				_alloc(other._alloc), _compare(other._comp), _tree(tree_type(first, last, alloc, comp)) {} ;
			{
				this = *other;
			}

			map<Key,T,Compare,Allocator>& operator=(const map<Key,T,Compare,Allocator>& x);

			~map();

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
				return (_alloc.max_size());
			}

			// element access:

			T& operator[](const key_type& x);


			// modifiers:
			pair<iterator, bool>	insert(const value_type& x);

			iterator insert(iterator position, const value_type& x);
			
			template <class InputIterator>
			void insert(InputIterator first, InputIterator last);

			void erase(iteratorposition);

			size_type erase(const key_type& x);

			void erase(iterator first, iterator last); 
			
			void swap(map<Key,T,Compare,Allocator>&);

			void clear();

			// observers:
			key_compare key_comp()const;

			value_compare value_comp() const;

			// 23.3.1.3 map operations:
			iterator find(const key_type& x);
			
			const_iterator find(const key_type& x) const;
			
			size_type count(const key_type& x) const;

			iterator       lower_bound(const key_type& x);

			const_iterator lower_bound(const key_type& x) const;

			iterator       upper_bound(const key_type& x);

			const_iterator upper_bound(const key_type& x) const;

			pair<iterator,iterator>
			equal_range(const key_type& x);

			pair<const_iterator,const_iterator>
			equal_range(const key_type& x) const;
};

		template <class Key, class T, class Compare, class Allocator>
		bool operator==(const map<Key,T,Compare,Allocator>& x,
						const map<Key,T,Compare,Allocator>& y);

		template <class Key, class T, class Compare, class Allocator>
		bool operator< (const map<Key,T,Compare,Allocator>& x,
						const map<Key,T,Compare,Allocator>& y);

		template <class Key, class T, class Compare, class Allocator>
		bool operator!=(const map<Key,T,Compare,Allocator>& x,
						const map<Key,T,Compare,Allocator>& y);

		template <class Key, class T, class Compare, class Allocator>
		bool operator> (const map<Key,T,Compare,Allocator>& x,
						const map<Key,T,Compare,Allocator>& y);

		template <class Key, class T, class Compare, class Allocator>
		bool operator>=(const map<Key,T,Compare,Allocator>& x,
						const map<Key,T,Compare,Allocator>& y);

		template <class Key, class T, class Compare, class Allocator>
		bool operator<=(const map<Key,T,Compare,Allocator>& x,
						const map<Key,T,Compare,Allocator>& y);

		// specialized algorithms:
		template <class Key, class T, class Compare, class Allocator>
		void swap(map<Key,T,Compare,Allocator>& x,
					map<Key,T,Compare,Allocator>& y);
};

# endif
