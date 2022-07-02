# ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <memory>
# include <stdexcept>
# include <stdint.h>
# include <iostream>
# include "iterator.hpp"
# include "type_traits.hpp"


namespace ft
{
		template<class U>
		class RandomAccessIterator: public ft::iterator<std::random_access_iterator_tag, U>
		{
			
			public:

				typedef typename iterator_traits<U*>::value_type			value_type;
				typedef typename iterator_traits<U*>::difference_type		difference_type;
				typedef typename iterator_traits<U*>::pointer				pointer;
				// typedef typename iterator_traits<const U*>::const_pointer	const_pointer;
				typedef typename iterator_traits<U*>::reference				reference;


				// CONSTRUCTORS

				RandomAccessIterator<U>() {};
				explicit RandomAccessIterator(pointer const ptr) : _current(ptr) {};
				RandomAccessIterator(RandomAccessIterator<U> const &other) : _current(other.base()) {};

				RandomAccessIterator& operator=(RandomAccessIterator const &other)
				{
					_current = other.base();
					return (*this);
				}

				~RandomAccessIterator() {};

				// MEMBER FONCTIONS

				operator  RandomAccessIterator<const U> () const
				{
					RandomAccessIterator<const U> citer(_current);
					return (citer);
				};

				// operator  const_pointer () const
				// {
				// 	const_pointer citer(_current);
				// 	return (citer);
				// };
				
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
					return (_current);
				};

				// const_pointer operator->(typename ft::enable_if<!is_const<U>::value, U>::type)
				// {
				// 	return (const_pointer)(_current);
				// };

				template< class Iterator1 >
				bool operator==(const Iterator1& b) const
				{
					return (this->base() == b.base());
				};

				template< class Iterator1 >
				bool operator!=(const Iterator1& b) const
				{
					return (!(*this == b));
				};
				
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
					return (temp);
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

				RandomAccessIterator operator-=(difference_type n)
				{
					_current -= n;
					return (*this);
				};

				RandomAccessIterator operator-(difference_type n) const
				{
					return (RandomAccessIterator(_current - n));
				};

				difference_type operator-(const RandomAccessIterator& b) const
				{
					return (_current - b.base());
				};

				template< class Iterator1 >
				bool operator<(const Iterator1& b) const
				{
					return (this->base() < b.base());
				};

				template< class Iterator1 >
				bool operator>(const Iterator1& b) const
				{
					return (b.base() < this->base());
				};
				
				template< class Iterator1 >
				bool operator<=(const Iterator1& b) const
				{
					return (!(b.base() < this->base()));
				};

				template< class Iterator1 >
				bool operator>=(const Iterator1& b) const
				{
					return (!(this->base() < b.base()));
				};

				

				// operator  const_pointer () const
				// {
				// 	const_pointer citer(_current);
				// 	return (citer);
				// };

				// operator const value_type() const
				// {
				// 	const_value_type ret(*_current);
				// 	return (ret);
				// };

			protected:

				pointer	_current;

		};

	template<class U>
	RandomAccessIterator<U> operator+(
				typename RandomAccessIterator<U>::difference_type n,
				const RandomAccessIterator<U>& my_it)
	{ 
		return (RandomAccessIterator<U>(my_it.base() + n));
	}
}

# endif
