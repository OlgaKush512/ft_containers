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
			explicit reverse_iterator (iterator_type it);
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it);

			//MEMBER FONCTIONS

			iterator_type base() const;
			reference operator*() const;
			reverse_iterator operator+ (difference_type n) const;
			reverse_iterator& operator++(); //pre-increment
			reverse_iterator  operator++(int) // post-increment
			{
				reverse_iterator temp = *this;
				++(*this);
				return temp;
			};

			reverse_iterator& operator+= (difference_type n);
			reverse_iterator operator- (difference_type n) const;

			reverse_iterator& operator--();
			reverse_iterator  operator--(int)//post
			{
				reverse_iterator temp = *this;
				--(*this);
				return temp;
			};
			reverse_iterator& operator-= (difference_type n);
			pointer operator->() const
			{
				return &(operator*());
			}
			reference operator[] (difference_type n) const;	
	};
}

# endif
