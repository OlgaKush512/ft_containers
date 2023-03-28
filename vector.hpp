/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:06:55 by okushnir          #+#    #+#             */
/*   Updated: 2022/08/01 17:06:58 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef VECTOR_HPP
# define VECTOR_HPP

# include "iterator.hpp"
# include "type_traits.hpp"
# include "RandomAccessIterator.hpp"



namespace ft
{
	template<class T, class A = std::allocator<T> >
	class vector
	{
		public:

			typedef A										allocator_type;
			typedef typename A::pointer						pointer;
			typedef typename A::const_pointer				const_pointer;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;

			typedef typename A::reference					reference;
			typedef typename A::const_reference				const_reference;
			typedef typename A::value_type					value_type;

			typedef RandomAccessIterator<T>					iterator;
			typedef RandomAccessIterator<const T>			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;


			//CONSTRUCTORS

			vector() : _array(0), _size(0), _cap(0), _alloc(allocator_type()) {} ;

			explicit vector(const allocator_type& alloc) : _array(0), _size(0), _cap(0), _alloc(alloc) {};

			explicit vector(size_type count, const T& value = T(), const allocator_type& alloc = allocator_type()) : 
			_size(count), _cap(count), _alloc(alloc)
			{
				_array = _alloc.allocate(count);
				for (size_type i = 0; i < _size; ++i)
				{
					_alloc.construct(_array + i, value);
				}
			}
			template< class InputIt >
			vector( typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type first, InputIt last, const allocator_type& alloc = allocator_type()) : _array(0), _size(0), _cap(0), _alloc(alloc)
			{
				this->assign(first, last);
			}

			//COPY CONSTRUCTOR

			vector(const vector& other): _size(other._size), _cap(other._size), _alloc(other._alloc)
			{
				_array = _alloc.allocate(_cap);
				for (size_type i = 0; i < _size; ++i)
				{
					_alloc.construct(_array + i,  other._array[i]);
				}
			};

			//OPERATOR =

			vector& operator=( const vector& other )
			{
				clear();
				reserve(other._cap);
				_size = other._size;
				for (size_type i = 0; i < _size; ++i)
				{
					_alloc.construct(_array + i, other._array[i]);
				}
				return (*this);
			}

			//DESTRUCTOR

			virtual ~vector()
			{
				clear();
					_alloc.deallocate(_array, _cap);
			}

			// ALLOCATOR

			allocator_type get_allocator() const
			{
				return (_alloc);
			}

			//ITERATORS

			iterator begin()
			{
				return (iterator(_array));
			}

			const_iterator begin() const
			{
				return (const_iterator(_array));
			}

			iterator end()
			{
				return (iterator(_array + _size));
			}

			const_iterator end() const
			{
				return (const_iterator(_array + _size));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->end()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->begin()));
			}

			//ELEMENT ACCESS

			reference operator[](size_type n)
			{
				return (_array[n]);
			}

			const_reference operator[](size_type n) const
			{
				return (_array[n]);
			}

			reference at(size_type n) 
			{
				if (n >= _size)
					throw std::out_of_range("...");
				return (_array[n]);
			}

			const_reference at(size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("...");
				return (_array[n]);
			}

			reference front()
			{
				return (_array[0]);
			}

			const_reference front() const
			{
				return (_array[0]);
			}

			reference back()
			{
				return (_array[_size - 1]);
			}

			const_reference back() const
			{
				return (_array[_size - 1]);
			}

			pointer data()
			{
				return (_array);
			}

			const_pointer data() const
			{
				return (_array);
			}
			
			// CAPACITY

			size_type size() const
			{
				return (_size);
			}

			size_type max_size() const
			{
				return (_alloc.max_size());
			}

			size_type capacity() const
			{
				return (_cap);
			}

			void resize(size_type n, value_type value = value_type())
			{
				if (n > size())
				{
					insert(end(), n - size(), value);
				}
				else if (n < size())
				{
					erase(begin() + n, end());
				}
				return ;
			}

			bool empty() const
			{
				if (!_size)
					return (true);
				return (false);
			}

			void reserve(size_type n)
			{
				if (n > _alloc.max_size())
					throw (std::length_error("vector::reserve"));
				if (n <= _cap)
					return;
				pointer new_arr = _alloc.allocate(n);
				size_type i = 0;
				for (; i < _size; ++i)
				{
					_alloc.construct(new_arr + i, _array[i]);
				}
				for (i = 0; i < _size; ++i)
					_alloc.destroy(_array + i);
				_alloc.deallocate(_array, n);
				_array = new_arr;
				_cap = n;
			}

			// MODIFIERS

			template <class InputIterator>
			void assign(typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
			{
				if (capacity() == 0)
				{
					size_type	new_size = 0;

					for (InputIterator test = first; test != last; ++test, ++new_size)
						;
					reserve(new_size);
				}
				erase(begin(), end());
				insert(begin(), first, last);
			}

			void assign (size_type n, const value_type& val)
			{
				clear();
				resize(n, val);
			}

			void push_back(const value_type& value)
			{
				if (size() + 1 > capacity())
					reserve(capacity() == 0 ? 1 : capacity() * 2);
				_alloc.construct(_array + _size, value);
				++_size;
			}

			void pop_back()
			{
				_alloc.destroy(_array + (_size - 1));
				--_size;
			}

			// INSERT

			//single element (1)	

			iterator insert(iterator pos, const T& value )
			{
				if (this->empty())
				{
					push_back(value);
					return (this->begin());
				}
				size_type res = (this->end() - pos);
				if (size() + 1 > capacity())
				{
					if (size() > 1)
						reserve(size() * 2);
					else
						reserve(size() + 1);
				}
				size_type pos_i = _size - res;
				_alloc.construct(_array + _size, value);
				for (size_type i = 0; i < res; ++i)
					_array[_size - i] = _array[_size - i - 1];
				++_size;
				_array[pos_i] = value;
				return (iterator(&_array[pos_i]));
			}

			// fill

			void insert( iterator pos, size_type count, const T& value )
			{
				if (count == 0)
					return;
				size_type res = (this->end() - pos);
				size_type pos_i = _size - res;
				if (size() + count > capacity())
				{
					if (size() > count)
						reserve(size() * 2);
					else
						reserve(size() + count);
				}
				for (size_type i = 0; i < count; ++i)
					_alloc.construct(_array + _size + i , value);
				for (size_type i = 0; i < res; ++i)
					_array[_size - i - 1 + count] = _array[_size - i - 1];
				_size += count;
				for (size_type i = 0; i < count; ++i)
					_array[pos_i + i] = value;
			}

			template <class InputIterator>
			void insert( iterator pos, InputIterator first, InputIterator last)
			{
				_insert_dispatch(pos, first, last, is_integral<InputIterator>());
			}

			template<typename InputIterator>
			void
			_insert_dispatch(iterator pos, InputIterator first,
					InputIterator last, false_type)
			{
				_range_insert(pos, first, last);
			}
			template<typename Integer>
			void
			_insert_dispatch(iterator pos, Integer n, Integer val,
					true_type)
			{
				_fill_insert(pos, n, val);
			}

			template<typename InputIterator>
			void _range_insert(iterator pos, InputIterator first,
					InputIterator last)
			{
				if (pos == end())
				{
					for (; first != last; ++first)
						insert(end(), *first);
				}
				else if (first != last)
				{
					for (difference_type i = pos - begin(); first != last; ++first, ++i)
						insert(begin() + i, *first);
				}
			}

			void	_fill_insert(iterator position, size_type n, const value_type& val)
			{
				const difference_type	diff = position - begin();

				if (n == 0)
					return ;
				if (size() + n > capacity())
				{
					if (size() > n)
						reserve(size() * 2);
					else
						reserve(size() + n);
				}
				for (difference_type i = size() - 1; i >= diff; i--)
				{
					_alloc.construct(&_array[i + n], _array[i]);
					_alloc.destroy(&_array[i]);
				}
				for (size_type i = diff; i < diff + n; i++)
					_alloc.construct(&_array[i], val);
				_size += n;
			}

			// // ERASE
			iterator erase(iterator pos)
			{
				if (!this->empty())
				{
					size_type res = (this->end() - pos) - 1;
					size_type pos_i = _size - res - 1;
					for (size_type i = 0; i < res; ++i)
						_array[pos_i + i] = _array[pos_i + i + 1];
					--_size;
					_alloc.destroy(_array + _size);
					return (iterator(&(_array[pos_i])));
				}
				return (this->begin());
			}

			iterator erase( iterator first, iterator last )
			{
				if (first == last)
					return (last);
				long long	move = (this->end() - last);
				long long	erasing = (last - first);
				long long	pos_i = _size - erasing - move;
				long long i = 0;
				for (; i < move; ++i)
					_array[pos_i + i] = _array[pos_i + erasing + i];
				for (long long j = 0; j < erasing; ++j)
					_alloc.destroy(_array + pos_i + move + j);
				_size -= erasing;
				return (iterator(_array + pos_i ));			
			}

			void swap(vector& other)
			{
				pointer	array_temp = _array;
				size_type size_temp(_size);
				size_type cap_temp(_cap);

				_array = other._array;
				_size = other._size;
				_cap = other._cap;

				other._array = array_temp;
				other._size = size_temp;
				other._cap = cap_temp;
			}
			
			void clear()
			{
				if (_size != 0)
				{
					for (size_type i = 0; i < _size; ++i)
						_alloc.destroy(_array + i);
					_size = 0;
				}
			}

		private:

			pointer			_array;
			size_type		_size;
			size_type		_cap;
			allocator_type	_alloc;
	};

	template< class T, class Alloc >
	bool operator==(const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		for (size_t i = 0; i < lhs.size(); ++i)
		{
			if (lhs[i] != rhs[i])
				return (false);
		}
		return (true);
	}


	template< class T, class Alloc >
	bool operator!=(const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (true);
		for (size_t i = 0; i < lhs.size(); ++i)
		{
			if (lhs[i] != rhs[i])
				return (true);
		}
		return (false);
	}

	template< class T, class Alloc >
	bool operator<(const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs)
	{
		size_t size_tmp = (lhs.size() < rhs.size() ) ? lhs.size() : rhs.size();
		for (size_t i = 0; i < size_tmp; ++i)
		{
			if (lhs[i] > rhs[i])
				return (false);
			if (lhs[i] < rhs[i])
				return (true);
		}
		if ((lhs.size() == rhs.size()) || (lhs.size() > rhs.size()))
			return (false);
		return (true);
	}

	template< class T, class Alloc >
	bool operator<=(const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs)
	{
		size_t size_tmp = (lhs.size() < rhs.size() ) ? lhs.size() : rhs.size();
		for (size_t i = 0; i < size_tmp; ++i)
		{
			if (lhs[i] > rhs[i])
				return (false);
			if (lhs[i] < rhs[i])
				return (true);
		}
		if (lhs.size() > rhs.size())
			return (false);
		return (true);
	}
	
	template< class T, class Alloc >
	bool operator>(const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs)
	{
		return (!(lhs <= rhs));
	}
	
	template< class T, class Alloc >
	bool operator>=(const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		return (x.swap(y));
	}
}

# endif
