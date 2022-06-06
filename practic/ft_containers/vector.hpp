# ifndef VECTOR_HPP
# define VECTOR_HPP

// # include <vector>
# include <memory>
# include <vector>
# include <stdexcept>
# include <stdint.h>
# include <iostream>
# include "iterator.hpp"
# include "type_traits.hpp"


namespace ft
{
	template<class T, class A = std::allocator<T> >
	class vector
	{
		template<bool IsConst>
		class RandomAccessIterator: public ft::iterator<std::random_access_iterator_tag, T>
		{
			
			public:

				typedef typename iterator_traits<T*>::value_type			value_type;
				typedef typename iterator_traits<T*>::difference_type		difference_type;
				typedef typename iterator_traits<T*>::pointer				pointer;
				typedef typename iterator_traits<T*>::reference				reference;


				// CONSTRUCTORS

				RandomAccessIterator() {};
				explicit RandomAccessIterator(pointer const ptr) : _current(ptr) {};
				RandomAccessIterator(RandomAccessIterator const &other) : _current(other.base()) {};

				RandomAccessIterator& operator=(RandomAccessIterator const &other)
				{
					_current = other.base();
					return (*this);
				}

				~RandomAccessIterator() {};

				// MEMBER FONCTIONS

				pointer base() const
				{
					return (_current);
				};

				reference operator*() const
				{
					return (*_current);
				};

				pointer operator->() const
				{
					return (&**this);
				};

				// bool operator==(const RandomAccessIterator& b) const
				// {
				// 	return (_current == b._current);
				// };

				// bool operator!=(const RandomAccessIterator& b)
				// {
				// 	return (!(*this == b));
				// };
				
				RandomAccessIterator& operator++()
				{
					++_current;
					return (*this);
				};
				
				RandomAccessIterator  operator++(int)
				{
					RandomAccessIterator temp = *this;
					++(*this);
					return (temp);
				};

				RandomAccessIterator& operator--()
				{
					_current--;
					return (*this);
				};
				
				RandomAccessIterator  operator--(int)
				{
					RandomAccessIterator temp = *this;
					--(*this);
					return (*temp);
				};

				reference  operator[](difference_type n)
				{
					return (*(*this + n));
				};

				RandomAccessIterator& operator+=(difference_type n)
				{
					_current += n;
					return (*this);
				};

				RandomAccessIterator operator+(difference_type n) const
				{
					return (RandomAccessIterator(_current + n));
				};

				RandomAccessIterator operator-=(difference_type n) const
				{
					_current -= n;
					return (*this);
				};

				RandomAccessIterator operator-(difference_type n)
				{
					return (RandomAccessIterator(_current - n));
				};

				difference_type operator-(const RandomAccessIterator& b)
				{
					return (_current - b._current);
				};

				bool operator<(const RandomAccessIterator& b)
				{
					return (_current < b._current);
				};

				bool operator>(const RandomAccessIterator& b)
				{
					return (b._current < _current);
				};
				
				bool operator<=(const RandomAccessIterator& b)
				{
					return (!(b._current < _current));
				};

				bool operator>=(const RandomAccessIterator& b)
				{
					return (!(_current < b._current));
				};

			protected:

				pointer	_current;

		};

		public :

		public:

			typedef A										allocator_type;
			typedef typename A::pointer						pointer;
			
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;

			typedef typename A::const_pointer				const_pointer;
			typedef typename A::reference					reference;
			typedef typename A::const_reference				const_reference;
			typedef typename A::value_type					value_type;

			typedef RandomAccessIterator<false>					iterator;
			typedef RandomAccessIterator<true>			const_iterator;
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
				return (this->end());
			}

			const_reverse_iterator rbegin() const
			{
				return (this->end());
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
				for (size_type i = 0; (first + i) != last; ++i)
					++tmp_size;
				clear();
				resize(tmp_size);
				for (size_type i = 0; i < tmp_size; ++i)
					*(_array + i) = *(first + i);
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
					reserve(2 * _cap);
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
				if (pos < this->begin() || pos >= this->end())
					return; //error?
				if (first > last)
					return; //error?
				size_t count = last - first;
				size_type move = (this->end() - pos );
				size_type pos_i = _size - move;
				std::cout << "count: " << count << std::endl;
				std::cout << "move: " << move << std::endl;
				// std::cout << "pos_i: " << pos_i << std::endl;
				if ((_size + count) > _cap)
					reserve(_size + count);
				for (size_type i = 0; i < count; ++i)
					_alloc.construct(_array + _size + i , value_type());
				std::cout << "size: " << _size << std::endl;
				std::cout << "_cap: " << _cap << std::endl;

				for (size_t i = 0; i < this->size(); i++)
					std::cout << this->at(i) << ' ';
				std::cout << std::endl << std::endl;
				for (size_type i = 0; i < move; ++i){
					_array[_size - i - 1 + count] = _array[_size - i - 1];
					std::cout << "moved: " << _array[_size - i - 1 + count] << std::endl;
				}
				_size += count;
				for (size_t i = 0; i < this->size(); i++)
					std::cout << this->at(i) << ' ';
				std::cout << std::endl << std::endl;
				for (size_type i = 0; first < last; ++first, ++i)
					_array[pos_i + i] = *first;
			}

			// // ERASE
			iterator erase(iterator pos)
			{
				if (!this->empty())
				{
					size_type res = (this->end() - pos);
					size_type pos_i = _size - res;
					for (size_type i = 0; i < res; ++i)
						_array[pos_i + i] = _array[pos_i + i + 1];
					--_size;
					_alloc.destroy(_array + _size);
					return (iterator(&(_array[pos_i + 1])));
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

				std::cout << "move : " << move << std::endl;
				std::cout << "erasing : " << erasing << std::endl;
				std::cout << "pos_i : " << pos_i << std::endl;

				long long i = 0;
				for (; i < move; ++i)
					_array[pos_i + i] = _array[pos_i + erasing + i];
				for (long long j = 0; j < erasing; ++j)
					_alloc.destroy(_array + pos_i + move + j); // ne marche non plus. voir avec le size non change
				_size -= erasing;
				return (iterator(_array + pos_i + move));			
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
			
			// NON_MEMBER FONCTIONS

			/*template< class T, class Alloc >
			friend bool operator<(const ft::vector<T,Alloc>& lhs,
							const ft::vector<T,Alloc>& rhs);

			template< class T, class Alloc >
			friend bool operator<=(const ft::vector<T,Alloc>& lhs,
							const ft::vector<T,Alloc>& rhs);
			
			template< class T, class Alloc >
			friend bool operator>(const ft::vector<T,Alloc>& lhs,
							const ft::vector<T,Alloc>& rhs);
			
			template< class T, class Alloc >
			friend bool operator>=(const ft::vector<T,Alloc>& lhs,
							const ft::vector<T,Alloc>& rhs);*/

		private:

			pointer			_array;
			size_type		_size;
			size_type		_cap;
			allocator_type	_alloc;
	};

	template<typename C, typename I, typename J>
	bool operator==(const typename ft::vector<C>::RandomAccessIterator<I> & lhs, const typename ft::vector<C>::RandomAccessIterator<J> & rhs)
	{
		return &(*lhs) == &(*rhs);
	}

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


	// template<typename C, typename I, typename J>
	// bool operator==(const typename ft::vector<C>::RandomAccessIterator<I> & lhs, const typename ft::vector<C>::RandomAccessIterator<J> & rhs)
	// {
	// 	return &(*lhs) == &(*rhs);
	// }


	/*template< class T, class Alloc >
	friend bool operator<(const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs);

	template< class T, class Alloc >
	friend bool operator<=(const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs);
	
	template< class T, class Alloc >
	friend bool operator>(const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs);
	
	template< class T, class Alloc >
	friend bool operator>=(const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs);*/
}

# endif
