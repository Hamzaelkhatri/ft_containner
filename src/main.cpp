#include <iostream> // std::cout
#include <iterator> // std::iterator_traits
#include <typeinfo> // typeid

int main()
{
    // typedef std::iterator_traits<int *> traits;
    // if (typeid(traits::iterator_category) == typeid(std::random_access_iterator_tag))
    //     std::cout << "int* is a random-access iterator\n";
    // typedef ft::iterators_traits<int *> traits2;
    // if (typeid(traits2::iterator_category) == typeid(std::random_access_iterator_tag))
    //     std::cout << "int* is a random-access iterator\n";
    ft::reverse_iterator<int *> rit(0);
    // std::cout << "reverse_iterator<int *> rit(0) = " << rit<< '\n';
    std::reverse_iterator<int *> rit2(0);
    // rit2.__t
    // std::cout << "reverse_iterator<int *> rit(0) = " << rit2. << '\n';

    return 0;
}