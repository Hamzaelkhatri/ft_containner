

#include <iostream>
#include <cmath>

#include <vector>
#include <stack>
#include <map>
#include <set>

#include "./set.hpp"

#ifndef NS
#define NS ft
#endif

template <typename T>
void print_namespace(NS::set<T> const &st)
{
	st.empty();
	std::cout << "\nNAMESPACE : ft" << std::endl;
}

template <typename T>
void print_set(NS::set<T> &st, char const *label)
{
	if (st.size() > 0)
	{
		std::cout << "\nmap Size: " << st.size();
		std::cout << "\nmap [" << label << "] contains: ";
		if (!st.size())
			std::cout << "nothing";
		else
			std::cout << "\n\n";
		for (typename NS::set<T>::iterator it = st.begin(); it != st.end(); ++it)
		{
			std::cout << "here" << " ";
			std::cout << "[" << *it << "]"
					  << " = " << *it << std::endl;
		}
		std::cout << std::endl;
	}
}

// a predicate implemented as a function:
bool single_digit(const int &value) { return (value < 10); }

// a predicate implemented as a class:
struct is_odd
{
	bool operator()(const int &value) { return (value % 2) == 1; }
};

// a binary predicate implemented as a function:
bool same_integral_part(double first, double second)
{
	return (int(first) == int(second));
}

// a binary predicate implemented as a class:
struct is_near
{
	bool operator()(double first, double second)
	{
		return (fabs(first - second) < 5.0);
	}
};

// compare only integral part:
bool mycomparison(double first, double second)
{
	return (int(first) < int(second));
}

int main()
{
	NS::set<int> setGolbal;
	print_namespace(setGolbal);

	// begin()
	// {
	// 	std::cout << "\nbegin() & end() " << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// 	NS::set<int> set1;
	// 	set1.insert(5);
	// 	set1.insert(10);
	// 	set1.insert(4);
	// 	set1.insert(2);
	// 	NS::set<int>::iterator it = set1.begin();
	// 	print_set(set1, "set1");
	// 	std::cout << "set1.begin(): " << (*it) << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// }

	// // assign operator=()
	// {
	// 	std::cout << "\nassign operator=()" << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// 	NS::set<int> set1;
	// 	set1.insert(5);
	// 	set1.insert(2);
	// 	set1.insert(10);
	// 	set1.insert(4);
	// 	print_set(set1, "set1");
	// 	NS::set<int> set2;
	// 	std::cout << "before assigning set1 to set2" << std::endl;
	// 	print_set(set2, "set2");
	// 	set2 = set1;
	// 	std::cout << "after assigning set1 to set2" << std::endl;
	// 	print_set(set2, "set2");
	// 	std::cout << "=======================================" << std::endl;
	// }

	// // clear()
	// {
	// 	std::cout << "\nclear()" << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// 	NS::set<int> set1;
	// 	set1.insert(5);
	// 	set1.insert(2);
	// 	set1.insert(10);
	// 	set1.insert(4);
	// 	print_set(set1, "set1");
	// 	set1.clear();
	// 	std::cout << "after clearing set1" << std::endl;
	// 	print_set(set1, "set1");
	// 	std::cout << "=======================================" << std::endl;
	// }

	// // count()
	// {
	// 	std::cout << "\ncount()" << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// 	NS::set<int> set1;
	// 	set1.insert(5);
	// 	set1.insert(2);
	// 	set1.insert(10);
	// 	set1.insert(4);
	// 	print_set(set1, "set1");
	// 	std::cout << "set1.count(5): " << set1.count(5) << std::endl;
	// 	std::cout << "set1.count(6): " << set1.count(6) << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// }

	// // empty() and size()
	// {
	// 	std::cout << "\nempty()" << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// 	NS::set<int> set1;
	// 	set1.insert(5);
	// 	set1.insert(2);
	// 	set1.insert(10);
	// 	set1.insert(4);
	// 	print_set(set1, "set1");
	// 	std::cout << "set1.empty(): " << set1.empty() << std::endl;
	// 	set1.clear();
	// 	std::cout << "after clearing set1" << std::endl;
	// 	print_set(set1, "set1");
	// 	std::cout << "set1.empty(): " << set1.empty() << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// }
	// // find()
	// {
	// 	std::cout << "\nfind()" << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// 	NS::set<int> set1;
	// 	set1.insert(5);
	// 	set1.insert(2);
	// 	set1.insert(10);
	// 	print_set(set1, "set1");
	// 	if (set1.find(5) != set1.end())
	// 		std::cout << "5 has been found and its second is = " << *(set1.find(5)) << std::endl;
	// 	else
	// 		std::cout << "5 has not been found" << std::endl;
	// 	if (set1.find(6) != set1.end())
	// 		std::cout << "6 has been found and its second is = " << *(set1.find(6)) << std::endl;
	// 	else
	// 		std::cout << "6 has not been found" << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// }

	// // insert()
	// {
	// 	std::cout << "\ninsert()" << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// 	NS::set<int> set1;
	// 	set1.insert(5);
	// 	set1.insert(2);
	// 	set1.insert(10);
	// 	print_set(set1, "set1");
	// 	NS::set<int>::iterator it = set1.insert(4).first;
	// 	print_set(set1, "set1");
	// 	std::cout << "inserted 4, 4 at " << (*it) << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// }

	// // set constructors
	// {
	// 	std::cout << "\nmap constructors" << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// 	NS::set<int> set1;
	// 	set1.insert(5);
	// 	set1.insert(2);
	// 	print_set(set1, "set1");
	// 	NS::set<int> set2(set1);
	// 	print_set(set2, "set2");
	// 	NS::set<int> map3(set2.begin(), set2.end());
	// 	print_set(map3, "map3");
	// 	std::cout << "=======================================" << std::endl;
	// }

	// // erase()
	// {
	// 	std::cout << "\nerase()" << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// 	NS::set<int> set1;
	// 	set1.insert(0);
	// 	set1.insert(2);
	// 	set1.insert(10);
	// 	set1.insert(4);
	// 	set1.insert(3);
	// 	set1.insert(3);
	// 	set1.insert(1);
	// 	set1.insert(0);
	// 	print_set(set1, "set1");
	// 	std::cout << "set1.erase(0): " << set1.erase(0) << std::endl;
	// 	NS::set<int>::iterator it = set1.begin();
	// 	std::advance(it, 2);
	// 	set1.erase(set1.begin(), it);
	// 	print_set(set1, "set1");
	// 	set1.erase(set1.begin());
	// 	print_set(set1, "set1");

	// 	std::cout << "=======================================" << std::endl;
	// }

	// max_size()
	{
		std::cout << "\nmax_size()" << std::endl;
		std::cout << "=======================================" << std::endl;
		ft::set<int> set1;
		std::cout << "set1.max_size(): " << set1.max_size() << std::endl;
		std::cout << "================std=======================" << std::endl; 
		std::set<int> set2;
		std::cout << "set1.max_size(): " << set2.max_size() << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// // swap()
	// {
	// 	std::cout << "\nswap()" << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// 	NS::set<int> set1;
	// 	set1.insert(5);
	// 	set1.insert(2);
	// 	set1.insert(10);
	// 	set1.insert(4);
	// 	print_set(set1, "set1");
	// 	NS::set<int> set2;
	// 	set2.insert(0);
	// 	set2.insert(2);
	// 	set2.insert(10);
	// 	set2.insert(4);
	// 	print_set(set2, "set2");
	// 	set1.swap(set2);
	// 	print_set(set1, "set1");
	// 	print_set(set2, "set2");
	// 	std::cout << "=======================================" << std::endl;
	// }

	// // lower_bound()
	// {
	// 	std::cout << "\nlower_bound()" << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// 	NS::set<int> set1;
	// 	set1.insert(5);
	// 	set1.insert(2);
	// 	set1.insert(10);
	// 	set1.insert(4);
	// 	print_set(set1, "set1");
	// 	NS::set<int>::iterator it = set1.lower_bound(3);
	// 	std::cout << "set1.lower_bound(3): " << (*it) << std::endl;
	// 	it = set1.lower_bound(5);
	// 	std::cout << "set1.lower_bound(5): " << (*it) << std::endl;
	// 	it = set1.lower_bound(6);
	// 	std::cout << "set1.lower_bound(6): " << (*it) << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// }

	// // upper_bound()
	// {
	// 	std::cout << "\nupper_bound()" << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// 	NS::set<int> set1;
	// 	set1.insert(5);
	// 	set1.insert(2);
	// 	set1.insert(10);
	// 	set1.insert(4);
	// 	print_set(set1, "set1");
	// 	NS::set<int>::iterator it = set1.upper_bound(3);
	// 	std::cout << "set1.upper_bound(3): " << (*it) << std::endl;
	// 	it = set1.upper_bound(5);
	// 	std::cout << "set1.upper_bound(5): " << (*it) << std::endl;
	// 	it = set1.upper_bound(6);
	// 	std::cout << "set1.upper_bound(6): " << (*it) << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// }

	// // equal_range()
	// {
	// 	std::cout << "\nequal_range()" << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// 	NS::set<int> set1;
	// 	set1.insert(5);
	// 	set1.insert(2);
	// 	set1.insert(10);
	// 	set1.insert(4);
	// 	print_set(set1, "set1");
	// 	NS::pair<NS::set<int>::const_iterator, NS::set<int>::const_iterator> range = set1.equal_range(3);
	// 	std::cout << "set1.equal_range(3): " << *range.first << " " << *range.second << std::endl;
	// 	range = set1.equal_range(5);
	// 	std::cout << "set1.equal_range(5): " << *range.first << " " << *range.second << std::endl;
	// 	range = set1.equal_range(6);
	// 	std::cout << "set1.equal_range(6): " << *range.first << " " << *range.second << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// }

	// // get_allocator()
	// {
	// 	std::cout << "\nget_allocator()" << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// 	NS::set<int> set1;
	// 	print_set(set1, "set1");
	// 	NS::set<int>::allocator_type alloc = set1.get_allocator();
	// 	std::cout << "alloc max size: " << alloc.max_size() << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// }

	// // const iterators
	// {
	// 	std::cout << "\nconst iterators" << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// 	NS::set<int> set1;
	// 	set1.insert(5);
	// 	set1.insert(2);
	// 	set1.insert(10);
	// 	set1.insert(4);
	// 	print_set(set1, "set1");
	// 	NS::set<int>::const_iterator it = set1.begin();
	// 	std::cout << "set1.begin(): " << (*it) << std::endl;
	// 	it = set1.end();
	// 	--it;
	// 	std::cout << "set1.end(): " << (*it) << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// }

	// // reverse iterators
	// {
	// 	std::cout << "\nreverse iterators" << std::endl;
	// 	std::cout << "=======================================" << std::endl;
	// 	NS::set<int> set1;
	// 	set1.insert(5);
	// 	set1.insert(2);
	// 	set1.insert(10);
	// 	set1.insert(4);
	// 	print_set(set1, "set1");
	// 	NS::set<int>::reverse_iterator it = set1.rbegin();
	// 	// print all elements in reverse order
	// 	for (; it != set1.rend(); ++it)
	// 	{
	// 		std::cout << "[" << (*it) << "] = " << (*it) << std::endl;
	// 	}

	// 	std::cout << "=======================================" << std::endl;
	// }
}
