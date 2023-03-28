/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:04:54 by okushnir          #+#    #+#             */
/*   Updated: 2022/08/01 17:04:56 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator.hpp"
# include "type_traits.hpp"


namespace ft
{
		template<class U>
		class RandomAccessIterator: public ft::iterator<std::random_access_iterator_tag, U>
		{
			
			public:

				typedef std::random_access_iterator_tag						iterator_category;
				typedef typename iterator_traits<U*>::value_type			value_type;
				typedef typename iterator_traits<U*>::difference_type		difference_type;
				typedef typename iterator_traits<U*>::pointer				pointer;
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

				operator  RandomAccessIterator<U> ()
				{
					RandomAccessIterator<U> citer(_current);
					return (citer);
				};

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

	template <class Iterator1, class Iterator2>
	typename Iterator1::difference_type operator-(
				const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs)
	{
		return ((rhs.base()).base() - (lhs.base()).base());
	}
}

# endif
