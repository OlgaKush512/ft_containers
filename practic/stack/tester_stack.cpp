# include "stack.hpp"
# include <iostream>
# include <deque>
# include <list>
# include <assert.h>

int main(void)
{
	typedef std::allocator<char> Myal;

	typedef std::deque<char, Myal> Myimp1;
	typedef ft::stack<char, Myimp1> Mycont;

	// typedef std::list<char, Myal> Myimp2;
	// typedef ft::stack<char, Myimp2> Mycont2;

	// typedef std::vector<char, Myal> Myimp3;
	// typedef ft::stack<char, Myimp3> Mycont3;


	Mycont		v0(Myimp1(3, 'x')), v0a;
	// Mycont2		v2(Myimp2(3, 'x')), v2a;
	// Mycont3		v3(Myimp3(3, 'x')), v3a;

	std::cout << "testing <stack> on <deque>" << std::endl << std::endl;

	assert(v0.size() == 3 && v0.top() == 'x');
	assert(v0a.empty());
	v0 = v0a;
	v0.push('a');
	assert(v0.size() == 1 && v0.top() == 'a');
	v0.push('b');
	assert(v0.size() == 2 && v0.top() == 'b');
	v0.push('c');
	assert(v0.size() == 3 && v0.top() == 'c');

	assert(v0 == v0 && v0a < v0);
	assert(v0 != v0a && v0 > v0a);
	assert(v0a <= v0 && v0 >= v0a);

	v0.pop();
	assert(v0.top() == 'b');
	v0.pop();
	assert(v0.top() == 'a');
	v0.pop();
	assert(v0.empty());

	std::cout << "SUCCESS testing <stack> on <deque>" << std::endl << std::endl;
	// {
	// 	std::cout << "testing <stack> on <list>" << std::endl << std::endl;

	// 	assert(v2.size() == 3 && v2.top() == 'x');
	// 	assert(v2a.empty());
	// 	v2 = v2a;
	// 	v2.push('a');
	// 	assert(v2.size() == 1 && v2.top() == 'a');
	// 	v2.push('b');
	// 	assert(v2.size() == 2 && v2.top() == 'b');
	// 	v2.push('c');
	// 	assert(v2.size() == 3 && v2.top() == 'c');

	// 	assert(v2 == v2 && v2a < v2);
	// 	assert(v2 != v2a && v2 > v2a);
	// 	assert(v2a <= v2 && v2 >= v2a);

	// 	v2.pop();
	// 	assert(v2.top() == 'b');
	// 	v2.pop();
	// 	assert(v2.top() == 'a');
	// 	v2.pop();
	// 	assert(v2.empty());

	// 	std::cout << "SUCCESS testing <stack> on <list>" << std::endl << std::endl;
	// }
	// {
	// 	std::cout << "testing <stack> on <vector>" << std::endl << std::endl;

	// 	assert(v3.size() == 3 && v3.top() == 'x');
	// 	assert(v3a.empty());
	// 	v3 = v3a;
	// 	v3.push('a');
	// 	assert(v3.size() == 1 && v3.top() == 'a');
	// 	v3.push('b');
	// 	assert(v3.size() == 2 && v3.top() == 'b');
	// 	v3.push('c');
	// 	assert(v3.size() == 3 && v3.top() == 'c');

	// 	assert(v3 == v3 && v3a < v3);
	// 	assert(v3 != v3a && v3 > v3a);
	// 	assert(v3a <= v3 && v3 >= v3a);

	// 	v3.pop();
	// 	assert(v3.top() == 'b');
	// 	v3.pop();
	// 	assert(v3.top() == 'a');
	// 	v3.pop();
	// 	assert(v3.empty());

	// 	std::cout << "SUCCESS testing <stack> on <vector>" << std::endl << std::endl;
	// }
	return (0);
}