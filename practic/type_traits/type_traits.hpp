# ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

# include <cstddef>

namespace ft
{	
	template<class T, T v>
	struct integral_constant
	{
		static const T value = v;

		typedef T value_type;
		typedef integral_constant<T,v> type;

		const operator T() { return v;}
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template< class T > struct is_integral : public false_type {};
	template< bool > struct is_integral : public true_type {};
	template< char > struct is_integral : public true_type {};
	template< char16_t > struct is_integral : public true_type {};
	template< char32_t > struct is_integral : public true_type {};
	template< wchar_t > struct is_integral : public true_type {};
	template< signed char > struct is_integral : public true_type {};
	template< short int > struct is_integral : public true_type {};
	template< int > struct is_integral : public true_type {};
	template< long int > struct is_integral : public true_type {};
	template< long long int > struct is_integral : public true_type {};
	template< unsigned char > struct is_integral : public true_type {};
	template< unsigned short int > struct is_integral : public true_type {};
	template< unsigned int > struct is_integral : public true_type {};
	template< unsigned long int > struct is_integral : public true_type {};
	template< unsigned long long int > struct is_integral : public true_type {};

	template < bool B, class T =  void > struct enable_if {} ;
	
	template < class T > struct enable_if < true , T >  {  typedef T type ;  } ;
}

# endif
