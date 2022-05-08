# ifndef STACK_HPP
# define STACK_HPP

# include <vector>

namespace ft
{
	template<class T, class Container = std::vector<T> >
	class stack
	{
		public:

			typedef Container								container_type;
			typedef typename Container::value_type			value_type;
			typedef typename Container::size_type			size_type;
			typedef typename Container::reference			reference;
			typedef typename Container::const_reference		const_reference;


			stack() : _c() {};

			explicit stack(const container_type& cont) : _c(cont) {};

			stack(const stack& other): _c(other._c) {};

			stack& operator=( const stack& other )
			{
				_c = other._c;
				return (*this);
			}

			~stack() {};

			bool	empty() const
			{
				return (_c.empty());
			};

			size_type	size() const
			{
				return (_c.size());
			};

			reference	top() // value_type&
			{
				return (_c.back());
			};

			const_reference	top() const // const value_type&
			{
				return (_c.back());
			};

			void	push(const value_type& x)
			{
				_c.push_back(x);
			};

			void	pop()
			{
				_c.pop_back();
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

			container_type	_c;

	};

	template< class A, class Cont >
	bool operator==(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return (lhs._c == rhs._c);
	}

	template< class A, class Cont >
	bool operator!=(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return (lhs._c != rhs._c);
	}

	template< class A, class Cont >
	bool operator<(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return (lhs._c < rhs._c);
	}

	template< class A, class Cont >
	bool operator<=(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return (lhs._c <= rhs._c);
	}

	template< class A, class Cont >
	bool operator>(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return (lhs._c > rhs._c);
	}

	template< class A, class Cont >
	bool operator>=(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return (lhs._c >= rhs._c);
	}
}

# endif
