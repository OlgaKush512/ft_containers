#include <vector>
#include <iostream>

int main()
{
	size_t N = 5;
	std::vector<char> v(N);

	std::cout << "size : " << v.size() << " capacity : " << v.capacity() << std::endl;

	for (size_t i = 0 ; i < N; ++i)
	{
		v.push_back('x');
		std::cout << "size : " << v.size() << " capacity : " << v.capacity() << std::endl;
	}


	return (0);
}



	// std::vector<char> v1; == std::vector<char, std::allocator<char>> v1;
	// std::vector<char, my_allocator<char> > v2;

	// v1 = v2;