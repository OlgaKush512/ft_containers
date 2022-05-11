#include <vector>
#include "vector.hpp"
#include <iostream>

int main()
{
	size_t N = 5;
	ft::vector<char> v(N);
	std::vector<char> gr(N);


	std::cout << "size : " << v.size() << " capacity : " << v.capacity() << std::endl;

	for (size_t i = 0 ; i < N; ++i)
	{
		v.push_back('x');
		std::cout << "size : " << v.size() << " capacity : " << v.capacity() << std::endl;
	}

	std::cout << "___________________TEST du methode assign(n, val)___________________" << std::endl;
	N = 10;
	v.assign(10, 'm');
	gr.assign(10, 'm');
	for (size_t i = 0 ; i < N; ++i)
	{
		std::cout << "vrai vector" << std::endl;
		std::cout << "size : " << gr.size() << " capacity : " << gr.capacity()
		<< " i : "<< i << " val: "<< gr.at(i) << std::endl;

		std::cout << "mon vector" << std::endl;
		std::cout << "size : " << v.size() << " capacity : " << v.capacity()
		<< " i : "<< i << " val: "<< v.at(i) << std::endl << std::endl;
	}
	std::cout << "___________________TEST du methode assign(begin, last)___________________" << std::endl;
	
	size_t P = 12;
	ft::vector<char> v1(P, 'f');
	v.assign(v1.data(), v1.data() + (P));
	gr.assign(gr.begin(), gr.end());
	for (size_t i = 0 ; i < N; ++i)
	{
		std::cout << "vrai vector" << std::endl;
		std::cout << "size : " << gr.size() << " capacity : " << gr.capacity()
		<< " i : "<< i << " val: "<< gr.at(i) << std::endl;

		std::cout << "mon vector v" << std::endl;
		std::cout << "size : " << v.size() << " capacity : " << v.capacity()
		<< " i : "<< i << " val: "<< v.at(i) << std::endl;

		std::cout << "mon vector v1" << std::endl;
		std::cout << "size : " << v1.size() << " capacity : " << v1.capacity()
		<< " i : "<< i << " val: "<< v1.at(i) << std::endl << std::endl;
	}
	for (size_t i = 0 ; i < P; ++i)
	{
		std::cout << "mon vector v" << std::endl;
		std::cout << "size : " << v.size() << " capacity : " << v.capacity()
		<< " i : "<< i << " val: "<< v.at(i) << std::endl;

		std::cout << "mon vector v1" << std::endl;
		std::cout << "size : " << v1.size() << " capacity : " << v1.capacity()
		<< " i : "<< i << " val: "<< v1.at(i) << std::endl << std::endl;
	}
	return (0);
}



	// std::vector<char> v1; == std::vector<char, std::allocator<char>> v1;
	// std::vector<char, my_allocator<char> > v2;

	// v1 = v2;