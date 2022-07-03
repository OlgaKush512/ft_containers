# ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include <memory>

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	struct random_access_iterator_tag {};

	template<typename Iterator>
    struct iterator_traits
    {
      typedef typename Iterator::iterator_category iterator_category;
      typedef typename Iterator::value_type        value_type;
      typedef typename Iterator::difference_type   difference_type;
      typedef typename Iterator::pointer           pointer;
      typedef typename Iterator::reference         reference;
    };

	template< typename T >
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	template< class T >
	struct iterator_traits<const T*>
		{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef  const T*					pointer;
		typedef const T&					reference;
	};

	template<class Iterator>
	class reverse_iterator : public iterator< 
		typename iterator_traits<Iterator>::iterator_category,
		typename iterator_traits<Iterator>::value_type
		// typename iterator_traits<Iterator>::difference_type,
		// typename iterator_traits<Iterator>::pointer,
		/*typename iterator_traits<Iterator>::reference*/>
	{
		public:

			typedef reverse_iterator<Iterator>								MyType;
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::value_type			value_type;

			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

			//CONSTRUCTORS
			reverse_iterator() {};

			explicit reverse_iterator (iterator_type it) : _current(it) {};

			template <class U>
			reverse_iterator (const reverse_iterator<U>& rev_it) : _current(rev_it.base()) {};

			template< class U >
			reverse_iterator& operator=( const reverse_iterator<U>& other )
			{
				_current = other.base();
				return (*this);
			}

			//MEMBER FONCTIONS

			iterator_type base() const
			{
				return (_current);
			};
			
			pointer get_pointer() const
			{
				return (_current.base());
			}
			reference operator*() const
			{
				iterator_type tmp = _current;
				return (*--tmp);
			};

			pointer operator->() const
			{
				return &(operator*());
			};


			//OPERATIONS

			reverse_iterator& operator++() //pre-increment
			{
				--_current;
				return (*this);
			};

			reverse_iterator  operator++(int) // post-increment
			{
				reverse_iterator temp = *this;
				--_current;
				return (temp);
			};

			reverse_iterator& operator--()
			{
				++_current;
				return (*this);
			};

			reverse_iterator  operator--(int)//post
			{
				reverse_iterator temp = *this;
				++_current;
				return (temp);
			};

			reverse_iterator operator+(difference_type n) const
			{
				return (reverse_iterator(base() - n));
			};

			reverse_iterator& operator+=(difference_type n)
			{
				_current -= n;
				return (*this);
			};

			reverse_iterator operator-(difference_type n) const
			{
				return (reverse_iterator(base() + n));
			};

			reverse_iterator& operator-=(difference_type n)
			{
				_current += n;
				return (*this);
			};

			reference operator[] (difference_type n) const
			{
				return (base()[-n-1]);
			};

			operator const iterator_type () const
			{
				return (_current);
			};


			// operator const reverse_iterator<const value_type *>() 
			// {
			// 	return reverse_iterator<const value_type *>(const_cast<const value_type *>(this->_current));
			// }
			
			// operator const value_type () const
			// {
			// 	return (_current);
			// };
		protected:

			iterator_type	_current;
	};

	template< class Iterator1, class Iterator2 >
	bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() == rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() != rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() > rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() >= rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() < rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() <= rhs.base());
	}
	
	template <class Iterator>
	reverse_iterator<Iterator> operator+(
				typename reverse_iterator<Iterator>::difference_type n,
				const reverse_iterator<Iterator>& rev_it)
	{ 
		return (reverse_iterator<Iterator>(rev_it.base() - n));
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
				const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}

	template <class Iterator1, class Iterator2>
	typename Iterator1::difference_type operator-(
				const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs)
	{
		return ((rhs.base()).base() - (lhs.base()).base());
	}

	// template <class Iter1, class Iter2>
	// typename reverse_iterator<Iter1>::difference_type
    // operator-(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	// { return (rhs.base() - lhs.base()); }
		
};

# endif
