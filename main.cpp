/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:04:16 by okushnir          #+#    #+#             */
/*   Updated: 2022/08/01 17:04:19 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <typeinfo>

#include <iostream>
#include <utility>

#include <ctime>
#include <sys/time.h>

#include <vector>
#include <map>
#include <stack>
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"

#ifdef NS
    #define NS std
#else
    #define NS ft
#endif

void showSizeCapacity(NS::vector<int> const &vct)
{
    std::cout << "size: " << vct.size() << std::endl;
    std::cout << "max_size: " << vct.max_size() << std::endl;
    NS::vector<int>::const_iterator it = vct.begin();
    NS::vector<int>::const_iterator ite = vct.end();
    std::cout << std::endl
              << "Content is:" << std::endl;
    for (; it != ite; ++it)
        std::cout << "- " << *it << std::endl;
}

void printVector(NS::vector<std::string> const &vct)
{
    NS::vector<std::string>::const_iterator it = vct.begin();
    NS::vector<std::string>::const_iterator ite = vct.end();
    for (; it != ite; ++it)
        std::cout << *it << std::endl;
}

void ft_constructor()
{
    std::cout << "VECTOR CONSTRUCTORS:" << std::endl;
    NS::vector<int> first;
    NS::vector<int> second(4, 100);
    NS::vector<int> third(second.begin(), second.end());

    int myints[] = {16, 2, 77, 29};
    NS::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

    for (NS::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << std::endl;

    ft::vector<int> ft_vec;
    std::vector<int> std_vec;

    std::allocator<int> my_alloc;
    ft::vector<int> ft_vec1(my_alloc);

    std::vector<int> std_vec2(5);
    ft::vector<int> ft_vec2(5);

    ft::vector<int>::iterator it = ft_vec2.begin();
    ft::vector<int>::iterator ite = ft_vec2.end();
    while (it != ite)
    {
        std::cout << (*it) << std::endl;
        it++;
    }
    std::vector<int> std_vec3(5, 4);
    ft::vector<int> ft_vec3(5, 4);
    ft::vector<int>::iterator it1 = ft_vec3.begin();
    ft::vector<int>::iterator ite1 = ft_vec3.end();
    while (it1 != ite1)
    {
        std::cout << (*it1) << std::endl;
        it1++;
    }

    ft::vector<int> test(ft_vec3.begin(), ft_vec3.end());
    it = test.begin();
    ite = test.end();
    while (it != ite)
    {
        std::cout << (*it) << std::endl;
        it++;
    }

    ft::vector<int> copy(test);
    it = copy.begin();
    ite = copy.end();
    while (it != ite)
    {
        std::cout << (*it) << std::endl;
        it++;
    }
    std::cout << std::endl;
}

void ite(void)
{
    int size = 5;
    NS::vector<int> vct(size);

    NS::vector<int>::iterator it = vct.begin();
    for (int i = 0; i < size; ++i)
        it[i] = i;
    std::cout << std::endl;
    return;
}

int vector_copy_construct(void)
{
    NS::vector<int> vct(5);
    NS::vector<int>::iterator it = vct.begin(), ite = vct.end();

    std::cout << "len: " << (ite - it) << std::endl;
    for (; it != ite; ++it)
        *it = (ite - it);

    it = vct.begin();
    NS::vector<int> vct_range(it, --(--ite));
    for (int i = 0; it != ite; ++it)
        *it = ++i * 5;

    it = vct.begin();
    NS::vector<int> vct_copy(vct);
    for (int i = 0; it != ite; ++it)
        *it = ++i * 7;
    vct_copy.push_back(42);
    vct_copy.push_back(21);

    vct = vct_copy;
    vct_copy = vct_range;

    showSizeCapacity(vct);
    showSizeCapacity(vct_copy);
    showSizeCapacity(vct_range);

    std::cout << std::endl;
    return (0);
}

int rite_arrow(void)
{
    const int size = 5;
    NS::vector<int> vct(size);
    NS::vector<int>::reverse_iterator it(vct.rbegin());
    NS::vector<int>::const_reverse_iterator ite(vct.rend());

    for (int i = 1; it != ite; ++i)
        *it++ = (i * 7);

    it = vct.rbegin();
    ite = vct.rbegin();

    std::cout << *(++ite) << std::endl;
    std::cout << *(ite++) << std::endl;
    std::cout << *ite++ << std::endl;
    std::cout << *++ite << std::endl;

    std::cout << *(++it) << std::endl;
    std::cout << *(it++) << std::endl;
    std::cout << *it++ << std::endl;
    std::cout << *++it << std::endl;

    std::cout << *(--ite) << std::endl;
    std::cout << *(ite--) << std::endl;
    std::cout << *--ite << std::endl;
    std::cout << *ite-- << std::endl;

    std::cout << *(--it) << std::endl;
    std::cout << *(it--) << std::endl;
    std::cout << *it-- << std::endl;
    std::cout << *--it << std::endl;
    return (0);
}

void ft_insert()
{
    NS::vector<int> vec(3, 100);
    NS::vector<int>::iterator it = vec.begin();
    it = vec.insert(it, 200);
    showSizeCapacity(vec);

    vec.insert(it, 2, 300);
    showSizeCapacity(vec);
    it = vec.begin();

    NS::vector<int> vec2(2, 400);
    vec.insert(it + 2, vec2.begin(), vec2.end());
    showSizeCapacity(vec);

    int arr[] = {501, 502, 503};
    vec.insert(vec.begin(), arr, arr + 3);
    showSizeCapacity(vec);
}

void ft_swap()
{
    NS::vector<int> one(4, 6), two(6, 7);
    NS::swap(one, two);

    for (NS::vector<int>::iterator it = one.begin(); it != one.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << std::endl;

    NS::vector<int> foo(3, 10);
    NS::vector<int> bar(5, 20);

    foo.swap(bar);

    for (unsigned i = 0; i < foo.size(); i++)
        std::cout << ' ' << foo[i];
    std::cout << std::endl;

    for (unsigned i = 0; i < bar.size(); i++)
        std::cout << ' ' << bar[i];
    std::cout << std::endl;

    NS::vector<int> a1;
    a1.push_back(1);
    a1.push_back(2);
    a1.push_back(3);
    NS::vector<int> a2;
    a2.push_back(4);
    a2.push_back(5);
    a1.swap(a2);
    showSizeCapacity(a1);
    showSizeCapacity(a2);
    std::cout << std::endl;
}

void ft_reverse_iterator()
{
    NS::vector<int> myvector;

    for (int i = 0; i < 10; i++)
        myvector.push_back(i);

    NS::vector<int>::reverse_iterator rev = myvector.rbegin();
    rev++;
    rev--;

    NS::vector<int>::reverse_iterator rev2 = myvector.rend();
    rev2--;
    rev2++;
    std::cout << std::endl;
}

void ft_reserve()
{
    NS::vector<int>::size_type sz;
    NS::vector<int> foo;
    sz = foo.capacity();
    for (int i = 0; i < 100; ++i)
    {
        foo.push_back(i);
        if (sz != foo.capacity())
        {
            sz = foo.capacity();
            std::cout << sz << ' ';
        }
    }

    NS::vector<int> bar;
    sz = bar.capacity();
    bar.reserve(100);
    for (int i = 0; i < 100; ++i)
    {
        bar.push_back(i);
        if (sz != bar.capacity())
        {
            sz = bar.capacity();
            std::cout << sz << ' ';
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void ft_erase()
{
    NS::vector<int> myvector;
    for (int i = 1; i <= 10; i++)
        myvector.push_back(i);

    myvector.erase(myvector.begin() + 5);
    myvector.erase(myvector.begin(), myvector.begin() + 3);
    for (unsigned i = 0; i < myvector.size(); ++i)
        std::cout << ' ' << myvector[i];

    std::cout << std::endl;
    NS::vector<int> myvector2;
    for (int i = 1; i <= 10; i++)
        myvector2.push_back(i);
    myvector2.erase(myvector2.begin() + 5);
    myvector2.erase(myvector2.begin(), myvector2.begin() + 3);
    for (unsigned i = 0; i < myvector2.size(); ++i)
        std::cout << ' ' << myvector2[i];
    std::cout << std::endl;

    NS::vector<int> cnt;
    cnt.push_back(4);
    cnt.push_back(-1);
    cnt.push_back(10);
    cnt.push_back(2);

    NS::vector<int>::iterator it = cnt.begin();
    cnt.erase(it);
    it = cnt.begin();
    NS::vector<int>::iterator ite = cnt.end();
    while (it != ite)
    {
        std::cout << (*it) << " ";
        it++;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void vector_assign(void)
{
    NS::vector<int> first;
    NS::vector<int> second;
    NS::vector<int> third;

    first.assign(7, 100);
    NS::vector<int>::iterator it;
    it = first.begin() + 1;

    second.assign(it, first.end() - 1);
    int myints[] = {1776, 7, 4};
    third.assign(myints, myints + 3);

    std::cout << "Size of first: " << int(first.size()) << std::endl;
    std::cout << "Size of second: " << int(second.size()) << std::endl;
    std::cout << "Size of third: " << int(third.size()) << std::endl;

    NS::vector<char> characters(10);
    characters.assign(5, 'a');
    NS::vector<char>::iterator it1 = characters.begin();
    NS::vector<char>::iterator ite1 = characters.end();
    while (it1 != ite1)
    {
        std::cout << (*it1);
        it1++;
    }
    std::cout << std::endl;
    it1 = characters.begin();
    ite1 = characters.end();
    characters.assign(6, 'b');
    while (it1 != ite1)
    {
        std::cout << (*it1);
        it1++;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    return;
}

void vector_at(void)
{
    NS::vector<int> vec(3, 5);
    try
    {
        int &ref = vec.at(1);
        std::cout << ref << std::endl;
    }
    catch (std::out_of_range) {
        std::cout << "Out of range error" << std::endl;
    }
    catch (...) {
        std::cout << "Error" << std::endl;
    }
    NS::vector<int> myvector(10);
    for (unsigned i = 0; i < myvector.size(); i++)
        myvector.at(i) = i;
    for (unsigned i = 0; i < myvector.size(); i++)
        std::cout << ' ' << myvector.at(i);
    std::cout << std::endl;

    NS::vector<int> data(6, 6);
    data.at(1) = 88;
    std::cout << "Element at index 2 has value " << data.at(2) << std::endl;
    std::cout << "data size = " << data.size() << std::endl;
    try {
        data.at(5) = 666;
    }
    catch (std::out_of_range const &exc) {
        std::cout << exc.what() << std::endl;
    }
    NS::vector<int>::iterator it = data.begin();
    NS::vector<int>::iterator ite = data.end();
    while (it != ite)
    {
        std::cout << (*it);
        it++;
    }
    std::cout << std::endl;
    NS::vector<int> vct(7);
    for (unsigned long int i = 0; i < vct.size(); ++i)
    {
        vct.at(i) = (vct.size() - i) * 3;
        std::cout << "vct.at(): " << vct.at(i) << " | ";
        std::cout << "vct[]: " << vct[i] << std::endl;
    }
    return;
}

void vector_at_const(void)
{
    NS::vector<int> data(6, 6);
    data.at(1) = 88;
    std::cout << "Element at index 2 has value " << data.at(2) << std::endl;
    std::cout << "data size = " << data.size() << std::endl;
    try {
        data.at(5) = 666;
    }
    catch (std::out_of_range const &exc) {
        std::cout << exc.what() << std::endl;
    }
    std::cout << "data: " << std::endl;
    NS::vector<int>::iterator it = data.begin();
    NS::vector<int>::iterator ite = data.end();
    while (it != ite)
    {
        std::cout << (*it) << " ";
        it++;
    }
    std::cout << std::endl;
    return;
}

void vector_size(void)
{
    ft::vector<int> myints;
    std::cout << "size: " << myints.size() << std::endl;

    for (int i = 0; i < 10; i++)
        myints.push_back(i);
    std::cout << "size: " << myints.size() << std::endl;

    myints.insert(myints.end(), 10, 100);
    std::cout << "size: " << myints.size() << std::endl;

    myints.pop_back();
    std::cout << "size: " << myints.size() << std::endl;
    return;
}

void vector_push_back(void)
{
    NS::vector<int> vec;
    int i = 0;
    while (i < 100)
    {
        vec.push_back(i);
        i++;
    }
    NS::vector<int>::iterator it = vec.begin();
    NS::vector<int>::iterator ite = vec.end();
    while (it != ite)
    {
        std::cout << (*it) << " ";
        it++;
    }
    std::cout << std::endl;
    NS::vector<int> myvector;
    myvector.push_back(100);
    myvector.push_back(200);
    myvector.push_back(300);
    while (!myvector.empty())
    {
        myvector.pop_back();
    }
    showSizeCapacity(myvector);

    NS::vector<int> numbers;
    numbers.push_back(5);
    numbers.push_back(3);
    numbers.push_back(4);
    showSizeCapacity(numbers);
    return;
}

void capacity(void)
{
    int sz = 200;
    NS::vector<int> v1;

    unsigned long cap = v1.capacity();
    std::cout << "initial capacity = " << cap << std::endl;

    for (int n = 0; n < sz; ++n)
    {
        v1.push_back(n);
        if (cap != v1.capacity())
        {
            cap = v1.capacity();
            std::cout << "new capacity = " << cap << std::endl;
        }
    }
    std::cout << "final size = " << v1.size() << std::endl;
    std::cout << "final capacity = " << v1.capacity() << std::endl;

    NS::vector<int> myvector;
    for (int i = 0; i < 100; i++)
        myvector.push_back(i);
    std::cout << "size: " << (int)myvector.size() << std::endl;
    std::cout << "capacity: " << (int)myvector.capacity() << std::endl;
    std::cout << "max_size: " << (int)myvector.max_size() << std::endl;
}

void empty(void)
{
    NS::vector<int> myvector;
    int sum(0);

    for (int i = 1; i <= 10; i++)
        myvector.push_back(i);

    while (!myvector.empty())
    {
        sum += myvector.back();
        myvector.pop_back();
    }
    std::cout << "total: " << sum << std::endl;
    std::cout << std::boolalpha;
    std::vector<int> numbers;
    std::cout << "Initially, numbers.empty(): " << numbers.empty() << std::endl;

    numbers.push_back(42);
    std::cout << "After adding elements, numbers.empty(): " << numbers.empty() << std::endl;
    return;
}

void clear(void)
{
    NS::vector<int> myvector;
    myvector.push_back(100);
    myvector.push_back(200);
    myvector.push_back(300);

    for (unsigned i = 0; i < myvector.size(); i++)
        std::cout << ' ' << myvector[i];
    std::cout << std::endl;

    myvector.clear();
    myvector.push_back(1101);
    myvector.push_back(2202);

    for (unsigned i = 0; i < myvector.size(); i++)
        std::cout << ' ' << myvector[i];
    return;
}

void max_size(void)
{
    NS::vector<int> myvector;
    for (int i = 0; i < 100; i++)
        myvector.push_back(i);

    std::cout << "size: " << myvector.size() << std::endl;
    std::cout << "capacity: " << myvector.capacity() << std::endl;
    std::cout << "max_size: " << myvector.max_size() << std::endl;
    return;
}

void vector_pop_back(void)
{
    NS::vector<std::string> words;
    words.push_back("Hello");
    words.push_back("you");
    words.push_back("there");
    printVector(words);
    while (!words.empty())
    {
        words.pop_back();
        printVector(words);
    }
    return;
}

void resize(void)
{
    NS::vector<int> myvector;
    for (int i = 1; i < 10; i++)
        myvector.push_back(i);

    myvector.resize(5);
    myvector.resize(8, 100);
    myvector.resize(12);

    std::cout << "myvector contains:";
    for (unsigned long i = 0; i < myvector.size(); i++)
        std::cout << ' ' << myvector[i];
    return;
}

void front(void)
{
    std::vector<int> myvector;
    myvector.push_back(78);
    myvector.push_back(16);
    myvector.front() -= myvector.back();
    std::cout << "myvector.front() is now " << myvector.front() << std::endl;

    NS::vector<char> letters;
    letters.push_back('a');
    letters.push_back('e');
    letters.push_back('i');
    letters.push_back('o');
    letters.push_back('u');
    if (!letters.empty())
        std::cout << "The first character is '" << letters.front() << std::endl;
}

void back(void)
{
    std::vector<int> myvector;

    myvector.push_back(10);

    while (myvector.back() != 0)
        myvector.push_back(myvector.back() - 1);
    for (unsigned i = 0; i < myvector.size(); i++)
        std::cout << ' ' << myvector[i];
    std::cout << std::endl;

    std::vector<char> letters;
    letters.push_back('a');
    letters.push_back('b');
    letters.push_back('c');
    letters.push_back('d');

    if (!letters.empty())
        std::cout << "The last character is '" << letters.back() << std::endl;
    return;
}

void operator_bracket(void)
{
    NS::vector<int> myvector(10);
    NS::vector<int>::size_type sz = myvector.size();
    for (unsigned i = 0; i < sz; i++)
        myvector[i] = i;

    for (unsigned i = 0; i < sz / 2; i++)
    {
        int temp;
        temp = myvector[sz - 1 - i];
        myvector[sz - 1 - i] = myvector[i];
        myvector[i] = temp;
    }
    for (unsigned i = 0; i < sz; i++)
        std::cout << ' ' << myvector[i];
    return;
}

void get_allocator(void)
{
    NS::vector<int> myvector;
    int *p;
    unsigned int i;
    p = myvector.get_allocator().allocate(5);
    for (i = 0; i < 5; i++)
        myvector.get_allocator().construct(&p[i], i);

    for (i = 0; i < 5; i++)
        std::cout << ' ' << p[i];
    std::cout << std::endl;
    for (i = 0; i < 5; i++)
        myvector.get_allocator().destroy(&p[i]);
    myvector.get_allocator().deallocate(p, 5);
    return;
}

void operator_assignation(void)
{
    NS::vector<int> foo(3, 0);
    NS::vector<int> bar(5, 0);

    bar = foo;

    std::cout << "Size of foo: " << int(foo.size()) << std::endl;
    std::cout << "Size of bar: " << int(bar.size()) << std::endl;
    return;
}

void reverse_operator_overloads(void)
{
    NS::vector<int> vec(5, 2);
    vec.push_back(17);

    NS::vector<int>::reverse_iterator rev = vec.rbegin();
    NS::vector<int>::reverse_iterator reve = vec.rend();
    std::cout << (rev == reve) << std::endl;
    std::cout << (rev != reve) << std::endl;
    std::cout << (rev > reve) << std::endl;
    std::cout << (rev < reve) << std::endl;
    std::cout << (rev >= reve) << std::endl;
    std::cout << (rev <= reve) << std::endl;

    NS::vector<int>::reverse_iterator rev1 = rev + 1;
    NS::vector<int>::reverse_iterator rev2 = rev - 1;

    (void)rev1;
    (void)rev2;
    return;
}

void iterator_traits(void)
{
    typedef NS::iterator_traits<int *> traits;
    if (typeid(traits::iterator_category) == typeid(std::random_access_iterator_tag))
        std::cout << "int* is a random-access iterator" << std::endl;
    if (typeid(traits::iterator_category) == typeid(std::input_iterator_tag))
        std::cout << "int* is an input_iterator_tag" << std::endl;
    if (typeid(traits::iterator_category) == typeid(std::output_iterator_tag))
        std::cout << "int* is a output_iterator_tag" << std::endl;
    if (typeid(traits::iterator_category) == typeid(std::forward_iterator_tag))
        std::cout << "int* is a forward_iterator_tag" << std::endl;
    if (typeid(traits::iterator_category) == typeid(std::bidirectional_iterator_tag))
        std::cout << "int* is a bidirectional_iterator_tag" << std::endl;
    return;
}

bool mycomp(char c1, char c2)
{
    return std::tolower(c1) < std::tolower(c2);
}

void lexico(void)
{
    char foo[] = "Apple";
    char bar[] = "tree";

    std::cout << std::boolalpha;
    std::cout << "Comparing foo and bar lexicographically (foo<bar): " << std::endl;

    std::cout << "Using default comparison (operator<): ";
    std::cout << std::lexicographical_compare(foo, foo + 5, bar, bar + 9);
    std::cout << std::endl;

    std::cout << "Using mycomp as comparison object: ";
    std::cout << std::lexicographical_compare(foo, foo + 5, bar, bar + 9, mycomp) << std::endl;
    return;
}

void vector_iterator(void)
{
    NS::vector<std::string> words;
    words.push_back("pie");
    words.push_back("pah");
    words.push_back("puh");
    words.push_back("buh");

    NS::vector<std::string>::iterator it = words.begin();
    NS::vector<std::string>::iterator ite = words.end();
    while (it != ite)
    {
        std::cout << (*it) << " ";
        it++;
    }
    std::cout << std::endl;
    it = words.begin();
    ite--;
    std::cout << (it == ite) << std::endl;
    std::cout << (it != ite) << std::endl;
    std::cout << (it > ite) << std::endl;
    std::cout << (it >= ite) << std::endl;
    std::cout << (it < ite) << std::endl;
    std::cout << (it <= ite) << std::endl;
    it = it + 2;
    it = it - 2;
    it += 2;
    it -= 2;
    ite--;
    std::ptrdiff_t diff = ite - it;
    (void)diff;
    return;
}

void stack_empty(void)
{
    NS::stack<int> mystack;
    if (mystack.empty())
        std::cout << "empty stack." << std::endl;
    else
        std::cout << "Stack is not empty." << std::endl;
    mystack.push(42);
    std::cout << "After adding elements, container.empty(): " << mystack.empty() << " " << std::endl;
    return;
}

void stack_size(void)
{
    NS::stack<int> myints;
    std::cout << "size: " << myints.size() << std::endl;

    for (int i = 0; i < 5; i++)
        myints.push(i);
    std::cout << "size: " << myints.size() << std::endl;

    myints.pop();
    std::cout << "size: " << myints.size() << std::endl;

    NS::stack<int> container;
    std::cout << "Initially, container.size(): " << container.size() << std::endl;
    for (int i = 0; i < 7; ++i)
        container.push(i);
    std::cout << "After adding elements, container.size(): " << container.size() << std::endl;
    return;
}

void StackSize(const std::stack<int> &s)
{
    std::cout << s.size() << " elements on stack" << std::endl;
}

void StackTop(const std::stack<int> &s)
{
    std::cout << "Top element: " << s.top() << std::endl;
}

void stack_top(void)
{
    NS::stack<int> mystack;

    mystack.push(10);
    mystack.push(20);

    mystack.top() -= 5;
    std::cout << "mystack.top() is now " << mystack.top() << std::endl;

    std::stack<int> s;
    s.push(2);
    s.push(6);
    s.push(51);

    StackSize(s);
    StackTop(s);

    StackSize(s);
    s.pop();

    StackSize(s);
    StackTop(s);
    return;
}

void stack_push(void)
{
    NS::stack<int> mystack;

    for (int i = 0; i < 5; ++i)
        mystack.push(i);
    std::cout << "Popping out elements...";
    while (!mystack.empty())
    {
        std::cout << ' ' << mystack.top();
        mystack.pop();
    }
    std::cout << std::endl;
    return;
}

void stack_pop(void)
{
    NS::stack<int> mystack;

    for (int i = 0; i < 5; ++i)
        mystack.push(i);
    while (!mystack.empty())
    {
        std::cout << ' ' << mystack.top();
        mystack.pop();
    }
    std::cout << std::endl;
    return;
}

void make_pair(void)
{

    NS::pair<int, int> foo;
    NS::pair<int, int> bar;

    foo = NS::make_pair(10, 20);
    bar = NS::make_pair(10.5, 'A');
    std::cout << "foo: " << foo.first << ", " << foo.second << std::endl;
    std::cout << "bar: " << bar.first << ", " << bar.second << std::endl;
    return;
}

void key_comp(void)
{
    NS::map<char, int> mymap;
    NS::map<char, int>::key_compare mycomp = mymap.key_comp();

    mymap['a'] = 100;
    mymap['b'] = 200;
    mymap['c'] = 300;

    char highest = mymap.rbegin()->first;
    NS::map<char, int>::iterator it = mymap.begin();
    while (mycomp((*it++).first, highest))
        std::cout << it->first << " => " << it->second << std::endl;
}

void map_value_compare(void)
{
    NS::map<char, int> mymap;

    mymap['x'] = 1001;
    mymap['y'] = 2002;
    mymap['z'] = 3003;

    NS::pair<char, int> highest = *mymap.rbegin();
    NS::map<char, int>::iterator it = mymap.begin();

    (void)it;
    (void)highest;
    while (mymap.value_comp()(*it++, highest))
        std::cout << it->first << " => " << it->second << std::endl;
    return;
}

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
    bool operator()(const char &lhs, const char &rhs) const
    {
        return lhs < rhs;
    }
};

void map_constructors(void)
{
    NS::map<char, int> first;
    first['a'] = 10;
    first['b'] = 30;
    first['c'] = 50;
    first['d'] = 70;

    NS::map<char, int> second(first.begin(), first.end());
    NS::map<char, int> third(second);
    NS::map<char, int, classcomp> fourth;

    bool (*fn_pt)(char, char) = fncomp;
    NS::map<char, int, bool (*)(char, char)> fifth(fn_pt);
    NS::map<char, int> sixth = third;
    return;
}

void map_lower_bound(void)
{
    NS::map<char, int> mymap;
    NS::map<char, int>::iterator itlow, itup;

    mymap['a'] = 20;
    mymap['b'] = 40;
    mymap['c'] = 60;
    mymap['d'] = 80;
    mymap['e'] = 100;

    itlow = mymap.lower_bound('b');
    mymap.erase(itlow);

    for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;
    itlow = mymap.lower_bound('d');
    std::cout << "----" << std::endl;
    mymap.erase(itlow);
    for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;
    return;
}

void map_upper_bound(void)
{
    NS::map<char, int> mymap;
    NS::map<char, int>::iterator itlow, itup;

    mymap['a'] = 20;
    mymap['b'] = 40;
    mymap['c'] = 60;
    mymap['d'] = 80;
    mymap['e'] = 100;

    itlow = mymap.lower_bound('b');
    itup = mymap.upper_bound('d');

    mymap.erase(itlow, itup);

    for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;
    return;
}
void map_empty(void)
{
    NS::map<char, int> mymap;

    mymap['a'] = 10;
    mymap['b'] = 20;
    mymap['c'] = 30;

    while (!mymap.empty())
    {
        std::cout << mymap.begin()->first << " => " << mymap.begin()->second << std::endl;
        mymap.erase(mymap.begin());
    }
    return;
}

void map_size(void)
{
    NS::map<char, int> mymap;
    mymap['a'] = 101;
    mymap['b'] = 202;
    mymap['c'] = 302;

    std::cout << "mymap.size() is " << mymap.size() << std::endl;
    return;
}

void map_max_size(void)
{
    int i;
    NS::map<int, int> mymap;

    if (mymap.max_size() > 1000)
    {
        for (i = 0; i < 1000; i++)
            mymap[i] = 0;
        std::cout << "The map contains 1000 elements." << std::endl;
    }
    else
        std::cout << "The map could not hold 1000 elements." << std::endl;
    return;
}

void map_iterators(void)
{
    NS::map<char, int> mymap;

    mymap['b'] = 100;
    mymap['a'] = 200;
    mymap['c'] = 300;

    for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;

    for (NS::map<char, int>::const_iterator it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;

    NS::map<char, int> mymap1;

    mymap1['b'] = 100;
    mymap1['a'] = 200;
    mymap1['c'] = 300;

    for (NS::map<char, int>::reverse_iterator it = mymap1.rbegin(); it != mymap1.rend(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;

    for (NS::map<char, int>::const_reverse_iterator it = mymap1.rbegin(); it != mymap1.rend(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;

    std::map<char, int> mymap2;

    mymap2['b'] = 100;
    mymap2['a'] = 200;
    mymap2['c'] = 300;

    for (std::map<char, int>::iterator it = mymap2.begin(); it != mymap2.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;

    for (std::map<char, int>::const_iterator it = mymap2.begin(); it != mymap2.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;
    NS::map<char, int> mymap3;

    mymap3['b'] = 100;
    mymap3['a'] = 200;
    mymap3['c'] = 300;

    for (NS::map<char, int>::reverse_iterator it = mymap3.rbegin(); it != mymap3.rend(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;

    for (NS::map<char, int>::const_reverse_iterator it = mymap3.rbegin(); it != mymap3.rend(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;
    return;
}

void map_clear(void)
{
    NS::map<char, int> mymap;

    mymap['x'] = 100;
    mymap['y'] = 200;
    mymap['z'] = 300;

    for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;

    mymap.clear();
    return;
}

void map_erase(void)
{
    NS::map<char, int> mymap;
    NS::map<char, int>::iterator it;

    mymap['a'] = 10;
    mymap['b'] = 20;
    mymap['c'] = 30;
    mymap['d'] = 40;
    mymap['e'] = 50;
    mymap['f'] = 60;

    it = mymap.find('b');
    mymap.erase(it); // erasing by iterator

    mymap.erase('c'); // erasing by key

    it = mymap.find('e');
    mymap.erase(it, mymap.end()); // erasing by range

    for (it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;
    return;
}

void map_find(void)
{
    NS::map<char, int> mymap;
    NS::map<char, int>::iterator it;

    mymap['a'] = 50;
    mymap['b'] = 100;
    mymap['c'] = 150;
    mymap['d'] = 200;

    it = mymap.find('b');
    if (it != mymap.end())
        mymap.erase(it);

    std::cout << "elements in mymap:" << std::endl;
    std::cout << "a => " << mymap.find('a')->second << std::endl;
    std::cout << "c => " << mymap.find('c')->second << std::endl;
    std::cout << "d => " << mymap.find('d')->second << std::endl;
    return;
}

void map_insert(void)
{
    NS::map<char, int> mymap;
    mymap.insert(NS::pair<char, int>('a', 100));
    mymap.insert(NS::pair<char, int>('z', 200));

    NS::pair<NS::map<char, int>::iterator, bool> ret;
    ret = mymap.insert(NS::pair<char, int>('z', 500));
    if (ret.second == false)
    {
        std::cout << "element 'z' already existed";
        std::cout << " with a value of " << ret.first->second << std::endl;
    }

    NS::map<char, int>::iterator it = mymap.begin();
    mymap.insert(it, NS::pair<char, int>('b', 300)); // max efficiency inserting
    mymap.insert(it, NS::pair<char, int>('c', 400)); // no max efficiency inserting

    NS::map<char, int> anothermap;
    anothermap.insert(mymap.begin(), mymap.find('c'));

    for (it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;

    for (it = anothermap.begin(); it != anothermap.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;
    return;
}

void map_count(void)
{
    NS::map<char, int> mymap;
    char c;

    mymap['a'] = 101;
    mymap['c'] = 202;
    mymap['f'] = 303;

    for (c = 'a'; c < 'h'; c++)
    {
        std::cout << c;
        if (mymap.count(c) > 0)
            std::cout << " is an element of mymap." << std::endl;
        else
            std::cout << " is not an element of mymap." << std::endl;
    }
    return;
}

void map_equal_range(void)
{
    NS::map<char, int> mymap;

    mymap['a'] = 10;
    mymap['b'] = 20;
    mymap['c'] = 30;

    NS::pair<NS::map<char, int>::iterator, NS::map<char, int>::iterator> ret;
    ret = mymap.equal_range('b');

    std::cout << "lower bound points to: ";
    std::cout << ret.first->first << " => " << ret.first->second << std::endl;

    std::cout << "upper bound points to: ";
    std::cout << ret.second->first << " => " << ret.second->second << std::endl;
    return;
}

void map_get_allocator(void)
{
    int psize;
    NS::map<char, int> mymap;
    NS::pair<const char, int> *p;

    p = mymap.get_allocator().allocate(5);
    psize = sizeof(std::map<char, int>::value_type) * 5;

    std::cout << "The allocated array has a size of " << psize << " bytes." << std::endl;
    mymap.get_allocator().deallocate(p, 5);
    return;
}

void map_swap(void)
{
    NS::map<char, int> foo, bar;

    foo['x'] = 100;
    foo['y'] = 200;

    bar['a'] = 11;
    bar['b'] = 22;
    bar['c'] = 33;

    foo.swap(bar);

    for (NS::map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;

    for (NS::map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;
    return;
}

void map_copy_construct(void)
{
    NS::map<char, int> first;
    first['a'] = 10;
    first['b'] = 30;
    first['c'] = 50;
    first['d'] = 70;

    NS::map<char, int> second(first.begin(), first.end());
    NS::map<char, int> third(second);
    NS::map<char, int, classcomp> fourth;

    bool (*fn_pt)(char, char) = fncomp;
    NS::map<char, int, bool (*)(char, char)> fifth(fn_pt);
    return;
}

void map_overloads(void)
{
    NS::map<char, int> first;
    first['a'] = 10;
    first['b'] = 30;
    first['c'] = 50;
    first['d'] = 70;

    NS::map<char, int> second;
    first['e'] = 90;
    first['f'] = 110;
    first['g'] = 130;
    first['h'] = 150;

    std::cout << (first == second) << std::endl;
    std::cout << (first != second) << std::endl;
    std::cout << (first >= second) << std::endl;
    std::cout << (first > second) << std::endl;
    std::cout << (first <= second) << std::endl;
    std::cout << (first < second) << std::endl;

    NS::swap(first, second);
    return;
}

void stack_correc(void)
{
    std::cout << "-------" << std::endl;
    std::cout << "default (vector) stack:" << std::endl;
    NS::stack<int> c1;
    c1.push(5);
    std::cout << "Taille de la stack par defaut apres un ajout:" << c1.size() << std::endl;
    std::cout << "Default stack OK !" << std::endl;
    std::cout << "-------" << std::endl;
    NS::vector<int> vec;
    NS::stack<int, NS::vector<int> > c2(vec);
    c2.push(1);
    c2.push(2);
    std::cout << "Taille de la stack de vecteur apres 2 ajouts:" << c2.size() << std::endl;
    std::cout << "Vector stack OK !" << std::endl;
    std::cout << "-------" << std::endl;
    NS::stack<int, std::deque<int> > c3;
    c3.push(1);
    c3.push(2);
    std::cout << "Taille de la stack de vecteur apres 2 ajouts:" << c3.size() << std::endl;
    std::cout << "Deque stack OK !" << std::endl;
    std::cout << "-------" << std::endl;

    NS::stack<int, std::list<int> > c4;
    c4.push(1);
    c4.push(2);
    std::cout << "Taille de la stack de vecteur apres 2 ajouts:" << c4.size() << std::endl;
    std::cout << "List stack OK !" << std::endl;
    std::cout << "-------" << std::endl;
    return;
}

void map_correc(void)
{
    std::cout << "pair:" << std::endl;
    NS::pair<int, char> mypair;
    mypair.first = 1;
    mypair.second = 'a';
    std::cout << "Pair first is:" << mypair.first << ", pair second is:" << mypair.second << std::endl;

    NS::pair<int, int> foo;
    NS::pair<int, int> bar;

    foo = NS::make_pair(1, 2);
    bar = NS::make_pair(3, 4);

    std::cout << "foo: " << foo.first << ", " << foo.second << std::endl;
    std::cout << "bar: " << bar.first << ", " << bar.second << std::endl;
    NS::map<int, int> map;
    map.insert(NS::pair<int, int>(1, 10));
    std::cout << "Adding 1, 10 successfully." << std::endl;
    map.insert(NS::pair<int, int>(-2, -20));
    std::cout << "Adding 2, -20 successfully." << std::endl;
    map.insert(NS::pair<int, int>(0, 0));
    std::cout << "Adding 0, 0 successfully." << std::endl;
    map.insert(NS::pair<int, int>(1, -20));
    std::cout << "Tried to add 1, -20" << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << "Let's check if it was added:" << std::endl;
    NS::map<int, int>::iterator it = map.begin();
    NS::map<int, int>::iterator ite = map.end();
    int check = (*it).first;
    while (it != ite)
    {
        if (check > (*it).first)
            std::cout << "Error, the map is not ordered !" << std::endl; //will never happen
        check = (*it).first;
        std::cout << "First is:" << (*it).first << ", second is:" << (*it).second << std::endl;
        it++;
    }
    std::cout << "Wow, the map is ordered as well !" << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << std::endl;
    std::cout << "For further iterator test use the tester." << std::endl;
    std::cout << "if swap is moving pointers and not data:" << std::endl;
    std::cout << std::endl;
    NS::map<int, int> map1;
    map1.insert(bar);
    NS::map<int, int>::iterator it1 = map1.begin();
    NS::map<int, int> map2;
    map2.insert(foo);
    NS::map<int, int>::iterator it2 = map2.begin();
    NS::swap(map1, map2);
    std::cout << (it1 == map2.begin()) << std::endl;
	std::cout << (it2 == map1.begin()) << std::endl;
    return;
}

void    my_utils_tests()
{
    lexico();
    iterator_traits();
    make_pair();
    reverse_operator_overloads();
}

void    my_vector_tests()
{
    vector_iterator();
    ft_constructor();
    vector_copy_construct();
    operator_assignation();
    vector_assign();
    get_allocator();

    vector_at();
    vector_at_const();
    operator_bracket();
    front();
    back();
    
    ite();
    ft_reverse_iterator();
    rite_arrow();
    ft_reserve();

    empty();
    vector_size();
    max_size();
    capacity();

    clear();
    ft_insert();
    ft_erase();
    vector_push_back();
    vector_pop_back();
    resize();
    ft_swap();
}

void    my_stack_tests() {
    stack_correc();
    stack_empty();
    stack_size();
    stack_push();
    stack_pop();
    stack_top();

}

void    my_map_tests() {
    map_correc();
    map_overloads();
    map_value_compare();
    key_comp();
    map_constructors();
    map_iterators();
    map_copy_construct();
    map_get_allocator();
    map_equal_range();
    map_count();
    map_upper_bound();
    map_swap();
    map_insert();
    map_erase();
    map_find();
    map_clear();
    map_iterators();
    map_max_size();
    map_size();
    map_empty();
    map_lower_bound();
}

int main(void)
{
    std::cout << "UTILS:" << std::endl;
    my_utils_tests();
    std::cout << "\t\tUTILS END" << std::endl;

    std::cout << "VECTORS:" << std::endl;
    my_vector_tests();
    std::cout << "\t\tVECTOR END" << std::endl;

    std::cout << "STACK:" << std::endl;
    my_stack_tests();
    std::cout << "\t\tSTACK END" << std::endl;

    std::cout << "MAP:" << std::endl;
    my_map_tests();
    std::cout << "\t\tMAP END" << std::endl;
    return (0);
}
