#include "RBT.hpp"
#include <map>
#include <iostream>
#include "iterators.hpp"
// #include "map."
// define COLORS for terminal
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

int main()
{
    ft::RBT<std::pair<int, std::string>, std::less<int>> tree;

    tree.insert_(std::make_pair(1, "one"));
    tree.insert_(std::make_pair(2, "two"));
    tree.insert_(std::make_pair(3, "three"));
    tree.insert_(std::make_pair(4, "four"));
    tree.insert_(std::make_pair(5, "five"));

    // std::cout << tree.find(std::make_pair(1, "one"))->first << std::endl;

    std::map<int, std::string> map;
    map.insert(std::make_pair(1, "one"));
    map.insert(std::make_pair(2, "two"));
    map.insert(std::make_pair(3, "three"));
    map.insert(std::make_pair(4, "four"));
    map.insert(std::make_pair(5, "five"));
    // ft::RBT<std::pair<int, std::string>, std::less<int>>::iterator it = tree.begin();
    
    // while (it != tree._end_())
    // {
    //     std::cout << it->first << " " << it->second << std::endl;
    //     ++it;
    // }

    // std::cout << "==========================================" << std::endl;

    // ft::RBT<std::pair<int, std::string>, std::less<int>>::iterator it2 = tree._end_();
    // int i = 0;
    // --it2;
    // for (; it2 != tree.begin(); --it2)
    // {
    //     std::cout << it2->first << " " << it2->second << std::endl;
    //     ++i;
    // }

    // std::cout << "================================================"<< std::endl;
    // std::map<int, std::string>::iterator it3 = map.end();
    // --it3;
    // for (;it3 != map.begin(); --it3)
    // {
    //     std::cout << it3->first << " " << it3->second << std::endl;
    // }

    //rbegin
    ft::RBT<std::pair<int, std::string>, std::less<int>>::reverse_iterator it4 = tree.rbegin();
    for (; it4 != tree.rend(); ++it4)
    {
        std::cout << it4->first << " " << it4->second << std::endl;
    }

    std::cout << "================================================"<< std::endl;

    std::map<int, std::string>::reverse_iterator it5 = map.rbegin();
    for (; it5 != map.rend(); ++it5)
    {
        std::cout << it5->first << " " << it5->second << std::endl;
    }

    std::cout << "================================================"<< std::endl;

    // upper_bound
    ft::RBT<std::pair<int, std::string>, std::less<int>>::iterator it6 = tree.upper_bound(std::make_pair(3, "three"));
    for (; it6 != tree._end_(); ++it6)
    {
        std::cout << it6->first << " " << it6->second << std::endl;
    }

    std::cout << "================================================"<< std::endl;

    std::map<int, std::string>::iterator it7 = map.upper_bound(3);
    for (; it7 != map.end(); ++it7)
    {
        std::cout << it7->first << " " << it7->second << std::endl;
    }
    std::cout << "================================================"<< std::endl;

    // lower_bound
    ft::RBT<std::pair<int, std::string>, std::less<int>>::iterator it8 = tree.lower_bound(std::make_pair(3, "three"));
    for (; it8 != tree._end_(); ++it8)
    {
        std::cout << it8->first << " " << it8->second << std::endl;
    }

    std::cout << "================================================"<< std::endl;

    std::map<int, std::string>::iterator it9 = map.lower_bound(3);
    for (; it9 != map.end(); ++it9)
    {
        std::cout << it9->first << " " << it9->second << std::endl;
    }


    return 0;
}
