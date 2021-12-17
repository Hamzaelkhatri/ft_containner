#include "RBT.hpp"
#include <iostream>
#include <map>

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

    // add values to the tree with pair
    ft::RBT<int, std::string> tree;
    tree.insert(std::pair<int, std::string>(1, "1"));
    tree.insert(std::pair<int, std::string>(2, "2"));
    tree.insert(std::pair<int, std::string>(3, "3"));
    tree.insert(std::pair<int, std::string>(4, "4"));
    tree.insert(std::pair<int, std::string>(5, "5"));
    tree.insert(std::pair<int, std::string>(6, "6"));
    tree.printTree();
    std::cout << (tree.isRBProper() ? "\033[0;32mGOOD RBT" : "\033[0;31mNOT GOOD RDT") << RESET << std::endl;
    std::cout << tree._end_() << std::endl;
    std::cout << tree.search(2) << std::endl;
    std::cout << tree._begin_() << std::endl;
    std::cout << tree._size_() << std::endl;

    return 0;
}
