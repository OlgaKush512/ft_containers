/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:05:26 by okushnir          #+#    #+#             */
/*   Updated: 2022/08/01 17:05:29 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template<class T, class Container = ft::vector<T> >
	class stack
	{
		public:

			typedef Container								container_type;
			typedef typename Container::value_type			value_type;
			typedef typename Container::size_type			size_type;
			typedef typename Container::reference			reference;
			typedef typename Container::const_reference		const_reference;


			stack() : c() {};

			explicit stack(const container_type& cont) : c(cont) {};

			stack(const stack& other): c(other.c) {};

			stack& operator=( const stack& other )
			{
				c = other.c;
				return (*this);
			}

			~stack() {};

			bool	empty() const
			{
				return (c.empty());
			};

			size_type	size() const
			{
				return (c.size());
			};

			reference	top() // value_type&
			{
				return (c.back());
			};

			const_reference	top() const // const value_type&
			{
				return (c.back());
			};

			void	push(const value_type& x)
			{
				c.push_back(x);
			};

			void	pop()
			{
				c.pop_back();
			};

			template< class A, class Cont >
			friend bool operator==(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);

			template< class A, class Cont >
			friend bool operator!=(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);

			template< class A, class Cont >
			friend bool operator<(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);

			template< class A, class Cont >
			friend bool operator<=(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);
			
			template< class A, class Cont >
			friend bool operator>(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);
			
			template< class A, class Cont >
			friend bool operator>=(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);

		protected:

			container_type	c;

	};

	template< class A, class Cont >
	bool operator==(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return (lhs.c == rhs.c);
	}

	template< class A, class Cont >
	bool operator!=(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return (lhs.c != rhs.c);
	}

	template< class A, class Cont >
	bool operator<(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return (lhs.c < rhs.c);
	}

	template< class A, class Cont >
	bool operator<=(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template< class A, class Cont >
	bool operator>(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return (lhs.c > rhs.c);
	}

	template< class A, class Cont >
	bool operator>=(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return (lhs.c >= rhs.c);
	}
}

# endif
