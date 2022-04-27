#include <iostream>
#include <vector>
#include <set>


template <typename Iterator, typename IterCategory>
void my_advance_helper(Iterator& iter, int n, IterCategory)
{
	for (int i = 0; i < n; ++i)
		++iter;
}

template <typename Iterator>
void my_advance_helper(Iterator& iter, int n, std::random_access_iterator_tag)
{
	for (int i = 0; i < n; ++i)
		iter += n;
}

template <typename Iterator>
void my_advance(Iterator& iter, int n)
{
	my_advance_helper(iter, n,
		typename std::iterator_traits<Iterator>::eterator_category());
}
/*_____________________________________________________________________*/

//Conditionl struct - pour choisir common ou const iterator*/

template <bool B, typename U, typename V>
struct conditional
{
	using type = V;
}

template <typename U, typename V>
struct conditional<true, U, V>
{
	using type = U;
}

template <bool B, typename U, typename V>
using conditional_t = typename conditional<B, U, V>::type;

template<typename Iterator>
class reverse_iterator 
{
	Iterator iter;

	public:
	reverse_iterator<Iterator> & operator++()
	{
		--iter;
		return (*this);
	}

	reverse_iterator<Iterator> & operator+=(int n)
	{
		iter -= n;
		return (*this);
	}

	Iterator base(int n) const
	{
		return (iter);
	}
	/*reverse_iterator::base возвращает обычный итератор не "на тоже самое",
	а на следующий элемент (в порядке до реверса). Т.е. v.rbegin().base() == v.end().
	Иначе например не очень понятно что должен вернуть итератор rend().base() - итератор 
	на элемент "до первого" звучит стремно, а v.rend().base() == v.begin() выглядит ок.*/
}


class Vector
{
	int sz;
	T *str;

	private:

		template <bool IsConst>
		struct common_iterator
		{
			private:

				using ConditionalPtr = std::conditional_t<IsConst, const T*, T*>;
				using conditionalRef= std::conditional_t<IsConst, const T&, T&>;

				Conditional_ptr ptr;
			public:

				common_iterator<IsConst> & operator += (int n)
				{
					ptr += n;
					return (*this);
				}

				common_iterator<IsConst> operator+(int n)
				{
					auto copy = *this;
					copy += n ;
					return (copy);
				}

				conditionalRef operator *()
				{
					return *ptr;
				}
				ConditionalPtr operator ->()
				{
					return ptr;
				}
		}
	public:

		using iterator = common_iterator<false>;
		using const_iterator = common_iterator<true>;

		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

};




String::iterator operator + (int n, const String::iterator & iter)
{
	return iter + n;
}

int main(void)
{

	std::vector<int> v(10);
	for (std::vector<int>::reverse_iterator rit = v.rbegin(); rit < v.rend(); ++rit)
		v.insert(i);

	std::set<int>::iterator it = s.begin();
	std::advance(it, 25);
	std::cout << *it;
	std::advance(it, -10);
	std::cout << *it;
}