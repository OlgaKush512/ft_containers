#include <map>
#include <stack>
#include <vector>

int main()
{
	const int size = 5;
	std::vector<int> v(size);
	std::vector<int>::reverse_iterator it(v.rbegin());
	std::iterator_traits<int>::difference_type n;
	std::reverse_iterator<int>::difference_type n;

}