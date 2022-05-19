#include <vector>
#include <iterator>
#include "vector.hpp"
#include <iostream>

class Lala {
	public:
		Lala () {}
		~Lala () {
			std::cout << "destructor called" << std::endl;
		}
};

int main()
{
	size_t N = 5;
	ft::vector<char> v(N);
	std::vector<char> gr(N);



	std::cout << "size : " << v.size() << " capacity : " << v.capacity() << std::endl;

	// v.begin();
	// gr.begin();

	// gr.resize(10);

	// std::cout << "v.begin(); " << *v.begin() << std::endl;
	// std::cout << "gr.begin()" << *gr.begin()<< std::endl;

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
	
	// size_t P = 12;
	// ft::vector<char> v1(P, 'f');
	// v.assign(v1.begin(), v1.end());
	// gr.assign(gr.begin(), gr.end());
	// for (size_t i = 0 ; i < N; ++i)
	// {
	// 	std::cout << "vrai vector" << std::endl;
	// 	std::cout << "size : " << gr.size() << " capacity : " << gr.capacity()
	// 	<< " i : "<< i << " val: "<< gr.at(i) << std::endl;

	// 	std::cout << "mon vector v" << std::endl;
	// 	std::cout << "size : " << v.size() << " capacity : " << v.capacity()
	// 	<< " i : "<< i << " val: "<< v.at(i) << std::endl;

	// 	std::cout << "mon vector v1" << std::endl;
	// 	std::cout << "size : " << v1.size() << " capacity : " << v1.capacity()
	// 	<< " i : "<< i << " val: "<< v1.at(i) << std::endl << std::endl;
	// }
	// for (size_t i = 0 ; i < P; ++i)
	// {
	// 	std::cout << "mon vector v" << std::endl;
	// 	std::cout << "size : " << v.size() << " capacity : " << v.capacity()
	// 	<< " i : "<< i << " val: "<< v.at(i) << std::endl;

	// 	std::cout << "mon vector v1" << std::endl;
	// 	std::cout << "size : " << v1.size() << " capacity : " << v1.capacity()
	// 	<< " i : "<< i << " val: "<< v1.at(i) << std::endl << std::endl;
	// }

	N = 5;
	ft::vector<int> my_v(N);
	std::vector<int> tr(N);
	for (size_t i = 0; i < N; i++)
	{
		my_v[i] = i;
		tr[i] = i;
		// std::cout << "my vector : i : " << i << " val: "<< my_v.at(i) << std::endl << std::endl;
		// std::cout << "vrai vector : i : " << i << " val: "<< tr.at(i) << std::endl << std::endl;

	}
	for (size_t i = 0; i < N; i++)
		std::cout << my_v.at(i) << ' ';
	std::cout << std::endl << std::endl;
	for (size_t i = 0; i < N; i++)
		std::cout << tr.at(i) << ' ';
	std::cout << std::endl << std::endl;
	ft::vector<int>::iterator ptr_b = my_v.begin();
	std::vector<int>::iterator it = tr.begin();
	ft::vector<int>::iterator ptr_e = my_v.end();
	std::vector<int>::iterator it_e = tr.end();
	std::cout << "my begin() : " << *ptr_b << std::endl;
	std::cout << "vrai begin() : " << *it << std::endl;
	std::cout << "my end() : " << *ptr_e << std::endl;
	std::cout << "vrai end() : " << *it_e << std::endl;

	std::cout << "my front() : " << my_v.front() << std::endl;
	std::cout << "vrai front() : " << tr.front() << std::endl;
	std::cout << "my back() : " << my_v.back() << std::endl;
	std::cout << "vrai back() : " << tr.back() << std::endl;
	std::cout << "my[0] : " << my_v[0] << std::endl;
	std::cout << "vrai[0]: " << tr[0] << std::endl;
	std::cout << "my[N - 1] : " << my_v[N - 1] << std::endl;
	std::cout << "vrai[N - 1]: " << tr[N - 1] << std::endl;

	std::cout << "___________________TEST du methode insert(iterator pos, const T& value )___________________" << std::endl;
	my_v.insert(my_v.begin(), 48);
	tr.insert(tr.begin(), 48);
	for (size_t i = 0; i < N; i++)
		std::cout << my_v.at(i) << ' ';
	std::cout << std::endl << std::endl;
	for (size_t i = 0; i < N; i++)
		std::cout << tr.at(i) << ' ';
	std::cout << std::endl << std::endl;

	std::cout << "___________________TEST du methode insert(iterator pos, size_t count, const T& value)___________________" << std::endl;

	my_v.insert(my_v.begin() + 2, 8, 8);
	tr.insert(tr.begin() + 2, 8, 8);
	for (size_t i = 0; i < my_v.size(); i++)
		std::cout << my_v.at(i) << ' ';
	std::cout << std::endl << std::endl;
	for (size_t i = 0; i < tr.size(); i++)
		std::cout << tr.at(i) << ' ';
	std::cout << std::endl << std::endl;

	std::cout << "___________________TEST du methode erase(iterator pos)___________________" << std::endl;

	my_v.erase(my_v.begin() + 1);
	tr.erase(tr.begin() + 1);

	for (size_t i = 0; i < my_v.size(); i++)
		std::cout << my_v.at(i) << ' ';
	std::cout << std::endl << std::endl;
	for (size_t i = 0; i < tr.size(); i++)
		std::cout << tr.at(i) << ' ';
	std::cout << std::endl << std::endl;

	// ETRANGE!!!!
	// ft::vector<int> myne_empty(0);
	// // std::vector<int> true_empty(0);

	// myne_empty.erase(myne_empty.begin());
	// // true_empty.erase(true_empty.begin());

	std::cout << "___________________TEST du methode erase(iterator first, iterator last)___________________" << std::endl;

	std::cout << my_v.size() << std::endl;
	my_v.erase(my_v.begin() + 2, my_v.begin() + 6);
	tr.erase(tr.begin() + 2, tr.begin() + 6);

	for (size_t i = 0; i < my_v.size(); i++)
		std::cout << my_v[i] << ' ';
	std::cout << std::endl << std::endl;
	for (size_t i = 0; i < tr.size(); i++)
		std::cout << tr[i] << ' ';
	std::cout << std::endl << std::endl;



	std::vector<Lala> lala(4);

	lala.resize(1);

	std::cout << "___________________TEST du methode insert(iterator pos, size_t count, const T& value)___________________" << std::endl;

	N = 3;
	ft::vector<int> f1(N);
	ft::vector<int> f2(N);
	std::vector<int> tr1(N);

	for (size_t i = 0; i < 3; i++){
		f2[i] = i;
		tr1[i] = i;
	}
	f1.assign(8,8);

	std::cout << "f1" << std::endl;
	for (size_t i = 0; i < f1.size(); i++)
		std::cout << f1.at(i) << ' ';
	std::cout << std::endl << std::endl;
	std::cout << "f2" << std::endl;
	for (size_t i = 0; i < f2.size(); i++)
		std::cout << f2.at(i) << ' ';
	std::cout << std::endl << std::endl;
	std::cout << "tr1" << std::endl;
	for (size_t i = 0; i < tr1.size(); i++)
		std::cout << tr1.at(i) << ' ';
	std::cout << std::endl << std::endl;

	f2.insert(f2.begin() + 1, f1.begin(), f1.end());
	std::cout << "new f2" << std::endl;
	for (size_t i = 0; i < f2.size(); i++)
		std::cout << f2.at(i) << ' ';
	std::cout << std::endl << std::endl;

/* 
	std::cout << "___________________TEST du operator=(value_type b) d'iterator___________________" << std::endl;

	ft::vector<int>::iterator it2;
	it2 = my_v.begin() + 2;

	std::cout << *it2 << std::endl;

	*it2 = 2;

	for (size_t i = 0; i < my_v.size(); i++)
		std::cout << my_v.at(i) << ' '; */
	return (0);
}



	// std::vector<char> v1; == std::vector<char, std::allocator<char>> v1;
	// std::vector<char, my_allocator<char> > v2;

	// v1 = v2;