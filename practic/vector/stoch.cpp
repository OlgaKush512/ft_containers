# ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

# include <cstddef>
# include <uchar.h>


namespace ft
{	
	// template<class T, T v>
	// struct integral_constant
	// {
	// 	static const T value = v;

	// 	typedef T value_type;
	// 	typedef integral_constant<T,v> type;

	// 	const operator T() { return v;}
	// };

	// typedef integral_constant<bool,true> true_type;
	// typedef integral_constant<bool,false> false_type;

	template< class T > struct is_integral {static const bool value = false;};
	template<> struct is_integral<bool> {static const bool value = true;};
	template<> struct is_integral<char> {static const bool value = true;};
	// template<> struct is_integral<char16_t> {static const bool value = true;};
	// template<> struct is_integral<char32_t> {static const bool value = true;};
	template<> struct is_integral<wchar_t> {static const bool value = true;};
	template<> struct is_integral<signed char> {static const bool value = true;};
	template<> struct is_integral<short int> {static const bool value = true;};
	template<> struct is_integral<int> {static const bool value = true;};
	template<> struct is_integral<long int> {static const bool value = true;};
	template<> struct is_integral< long long int> {static const bool value = true;};
	template<> struct is_integral<unsigned char> {static const bool value = true;};
	template<> struct is_integral<unsigned short int> {static const bool value = true;};
	template<> struct is_integral<unsigned int> {static const bool value = true;};
	template<> struct is_integral<unsigned long int> {static const bool value = true;};
	template<> struct is_integral<unsigned long long int> {static const bool value = true;};

	template < bool B, class T =  void > struct enable_if {} ;
	
	template < class T > struct enable_if < true , T >  {  typedef T type ;  } ;
}

# endif
