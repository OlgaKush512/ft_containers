#include <iostream>
#include <vector>

//#include <algorithm>
//#include <iterator>
/*
template<typename Container>
struct back_insert_iterator {
private:
	Container& container;
public:
	back_insert_iterator<Container>& operator ++() { return *this; }
	back_insert_iterator<Container>& operator  *() { return *this; }
	typename  Container::value_type& operator  =(const typename Container::value_type& value) {
		container.push_back(value);
		return container.back();
	}
};
*/
int main()
{
	std::vector<int>  v(10);
	std::vector<int> vv;
	std::cout << "vector v  ";
	for (int i = 0; i < 10; ++i) { v[i] = i; std::cout << i << ", "; }
	std::cout << '\n';

	std::copy(v.begin(), v.end(), std::back_insert_iterator< std::vector<int> >(vv));
	std::cout << "vector vv ";
	for (int i = 0; i < 10; ++i) { std::cout << vv[i] << ", "; }
	std::cout << '\n';

}
/*
vector v  0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
vector vv 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,

*/