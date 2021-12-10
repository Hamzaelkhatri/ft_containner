#include <iostream>
#include "vector.hpp"
#include <vector>

int main()
{
    ft::vector<int> foo(3, 0);
    ft::vector<int> bar(5, 0);

    bar = foo;
    foo = ft::vector<int>();

    std::cout
        << "Size of foo: " << int(foo.size()) << '\n';
    std::cout << "Size of bar: " << int(bar.size()) << '\n';
    // ft::vector<int>::iterator it = ft::vector<int>::iterator();
    // std::vector<int>::iterator it2 = std::vector<int>::iterator();

    return 0;
}
