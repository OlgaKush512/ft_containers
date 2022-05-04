# ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

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
}

# endif
