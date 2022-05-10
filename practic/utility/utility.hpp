# ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{
	template<class T, class U >
	struct pair
	{
		typedef T	first _type;
		typedef U	second_type;

		first _type	first;
		second_type	second;

		pair() : first(first_type()), second(second_type()) {};
		pair( const first_type& x, const second_type& y ) : first(x), second(y) {};

		template< class T, class U >
		pair( const pair<T, U>& p ) : first(p.first), second(p.second) {};

		pair( const pair& p )
		{
			first = p.first;
			second = p.second;
		};

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
		return (ft::pair<T, U>(x,y));
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
/*
	template <bool B, typename U, typename V>
	struct conditional
	{
		typedef V type;
	};

	template <typename U, typename V>
	struct conditional<true, U, V>
	{
		typedef U type;
	};

	template <bool B, typename U, typename V>
	using conditional_t = typename conditional<B, U, V>::type;
	*/
}

#endif
