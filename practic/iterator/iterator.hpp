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
	struct iterator_traits;

	template< class T >
	struct iterator_traits<T*>;

	template< class T >
	struct iterator_traits<const T*>;
}

# endif
