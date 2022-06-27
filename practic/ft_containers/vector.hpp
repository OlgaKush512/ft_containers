# ifndef VECTOR_HPP
# define VECTOR_HPP

// # include <vector>
# include <memory>
# include <stdexcept>
# include <stdint.h>
# include <iostream>
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
			
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;

			typedef typename A::const_pointer				const_pointer;
			typedef typename A::reference					reference;
			typedef typename A::const_reference				const_reference;
			typedef typename A::value_type					value_type;

			typedef RandomAccessIterator<T>					iterator;
			typedef RandomAccessIterator<const T>			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;


			//CONSTRUCTORS

			vector() : _array(0), _size(0), _cap(0), _alloc(allocator_type()) {} ;

			explicit vector(const allocator_type& alloc) : _array(0), _size(0), _cap(0), _alloc(alloc) {} ;

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
			vector( InputIt first, InputIt last, const allocator_type& alloc = allocator_type()) : _array(0), _size(0), _cap(0), _alloc(alloc)
			{
				this->assign(first, last);
			}

			//COPY CONSTRUCTOR

			vector(const vector& other): _size(other._size), _cap(other._cap), _alloc(other._alloc)
			{
				_array = _alloc.allocate(_size);
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

			~vector()
			{
				if (_cap)
				{
					clear();
					_alloc.deallocate(_array, _cap);
				}
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
				return ((this->begin()));
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
				if (n > _cap)
					reserve(n);
				for (size_type i = _size; i < n; ++i)
					_alloc.construct(_array + i, value);
				if (n < _size)
				{
					for (size_type j = _size - (_size - n); j < _size; ++j)
						_alloc.destroy(_array + j);
				}
				_size = n;
			}

			bool empty() const
			{
				if (!_size)
					return (true);
				return (false);
			}

			void reserve(size_type n)
			{
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


			/*_____________________________________________________________________________________________________*/
			/*A_verifier___________________________________________________________________________________________*/
			/*_____________________________________________________________________________________________________*/

			template <class InputIterator>
			void assign(typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
			{
				size_type tmp_size = 0;
				InputIterator copy_first = first;

				for (; copy_first != last; ++copy_first)
					++tmp_size;
				clear();
				resize(tmp_size);
				copy_first = first;
				for (size_type i = 0; i < tmp_size; ++i, ++copy_first)
					*(_array + i) = *(copy_first);
			}

			/*_____________________________________________________________________________________________________*/
			/*A_verifier___________________________________________________________________________________________*/
			/*_____________________________________________________________________________________________________*/

			void assign (size_type n, const value_type& val)
			{
				clear();
				resize(n, val);
			}

			void push_back(const value_type& value)
			{
				if (_size == 0)
					reserve(1);
				else if (_cap == _size)
				{
					reserve(2 * _cap);
				}
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
				if (_size == _cap)
					reserve(2 * _cap);
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
				if (this->empty())
				{
					for (size_type i = 0; i < count; ++i)
						push_back(value);
					return;
				}
				size_type res = (this->end() - pos);
				size_type pos_i = _size - res;
				if ((_size + count) > _cap)
					reserve(_size + count);
				for (size_type i = 0; i < count; ++i)
					_alloc.construct(_array + _size + i , value);
				for (size_type i = 0; i < res; ++i)
					_array[_size - i - 1 + count] = _array[_size - i - 1];
				_size += count;
				for (size_type i = 0; i < count; ++i)
					_array[pos_i + i] = value;
			}

			template <class InputIt>
			void insert( iterator pos, typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type first, InputIt last)
			{
				// if (pos < this->begin() || pos >= this->end())
				// 	return; //error?
				// if (first > last)
				// 	return; //error?
				InputIt copy_first = first;
				size_t count = 0;
				while (copy_first != last)
				{
					++count;
					++copy_first;
				}
				size_type move = (this->end() - pos );
				size_type pos_i = _size - move;
				if ((_size + count) > _cap)
					reserve(_size + count);
				for (size_type i = 0; i < count; ++i)
					_alloc.construct(_array + _size + i , value_type());
				for (size_type i = 0; i < move; ++i)
					_array[_size - i - 1 + count] = _array[_size - i - 1];
				_size += count;
				for (size_type i = 0; first != last; ++first, ++i)
					_array[pos_i + i] = *first;
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
					_alloc.destroy(_array + pos_i + move + j); // ne marche non plus. voir avec le size non change
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
			
			// operator const_iterator () const
			// {
			// 	// RandomAccessIterator<const T> citer(_current);
			// 	return (iterator);
			// };

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
			if (lhs[i] > rhs[i]) // if string?
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
			if (lhs[i] > rhs[i]) // if string?
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
}

# endif
