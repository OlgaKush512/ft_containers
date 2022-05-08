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


	template< class Iterator >
	struct iterator_traits
	{
		typedef Iterator::iterator_category	iterator_category;
		typedef Iterator::value_type		value_type;
		typedef Iterator::difference_type	difference_type;
		typedef Iterator::pointer			pointer;
		typedef Iterator::reference			reference;
	};

	template< class T >
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
		typedef T*							pointer;
		typedef T&							reference;
	};

	template<class Iterator>
	class reverse_iterator
	{
		public:

			typedef Iterator										iterator_type;
			typedef iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef iterator_traits<Iterator>::value_type			value_type;
			typedef iterator_traits<Iterator>::difference_type		difference_type;
			typedef iterator_traits<Iterator>::pointer				pointer;
			typedef iterator_traits<Iterator>::reference			reference;

			//CONSTRUCTORS
			reverse_iterator();
			explicit reverse_iterator (iterator_type it) : _current(it) {};
			template <class Iterator>
			reverse_iterator (const reverse_iterator<Iterator>& rev_it) : _current(rev_it.base());

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

			reference operator*() const
			{
				iterator_type tmp = _current;
				return (*--tmp);
			};

			pointer operator->() const
			{
				return (&(operator*()));
			};

			reverse_iterator operator+(difference_type n) const
			{
				return (reverse_iterator(base() - n));
			};

			reverse_iterator& operator++(); //pre-increment
			{
				_current--;
				return (*this);
			};
			
			reverse_iterator  operator++(int) // post-increment
			{
				reverse_iterator temp = *this;
				++(*this);
				return temp;
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

			reverse_iterator& operator--()
			{
				_current++;
				return (*this);
			};

			reverse_iterator  operator--(int)//post
			{
				reverse_iterator temp = *this;
				--(*this);
				return temp;
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
		
		protected:

			iterator_type	_current;
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
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
		
}

# endif
