# ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{
	template<class T, class U >
	struct pair
	{
		typedef T	first_type;
		typedef U	second_type;

		first_type	first;
		second_type	second;

		pair() : first(first_type()), second(second_type()) {};
		
		pair(const first_type& x, const second_type& y ) : first(x), second(y) {};

		template< class V, class M >
		pair( const pair<V, M>& p ) : first(p.first), second(p.second) {};

		pair( const pair& p ) : first(p.first), second(p.second) {};

		pair& operator=(const pair& other)
		{
			first = other.first;
			second = other.second;

			return (*this);
		}
	};


	template <class T ,class U>
	pair<T, U> make_pair (T x, U y)
	{
		return (pair<T, U>(x,y));
	}

	template< class T, class U >
	bool operator==( const ft::pair<T,U>& lhs, const ft::pair<T,U>& rhs )
	{
		if ((lhs.first == rhs.first) && (lhs.second == rhs.second))
			return (true);
		return (false);
	}

	template< class T, class U >
	bool operator!=( const ft::pair<T,U>& lhs, const ft::pair<T,U>& rhs )
	{
		return (!(lhs == rhs));
	}

	template< class T, class U >
	bool operator<( const ft::pair<T,U>& lhs, const ft::pair<T,U>& rhs )
	{
		if (lhs.first < rhs.first)
			return (true);
		else if ((lhs.first == rhs.first) && (lhs.second < rhs.second))
			return (true);
		return (false);
	}

	template< class T, class U >
	bool operator<=( const ft::pair<T,U>& lhs, const ft::pair<T,U>& rhs )
	{
		return (!(rhs < lhs));
	}

	template< class T, class U >
	bool operator>( const ft::pair<T,U>& lhs, const ft::pair<T,U>& rhs )
	{
		return (rhs < lhs);
	}

	template< class T, class U >
	bool operator>=( const ft::pair<T,U>& lhs, const ft::pair<T,U>& rhs )
	{
		return (!(lhs < rhs));
	}

	template<class T> struct remove_const { typedef T type; };

	template<class T> struct remove_const <const T> { typedef T type; };

	template <class InputIterator1, class InputIterator2>
	bool equal( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1!=last1)
		{
			if (!(*first1 == *first2))
			return false;
			++first1; ++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1) return false;
			else if (*first1<*first2) return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}

}

#endif
