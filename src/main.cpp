#include "RBT.hpp"
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
    ft::RBT<int, int> tree;
    // insert using pair main.cpp:21:17: note: in instantiation of function template specialization 'std::__1::pair<std::__1::basic_string<char>, std::__1::less<std::__1::basic_string<char> > >::pair<const char *, const char *>' requested here
    // add values to the tree with pair
    // tree.insert(std::make_pair("red", "apple"));
    // tree.insert(std::make_pair("green", "lemon"));
    // tree.insert(std::make_pair("yellow", "banana"));
    // tree.insert(std::make_pair("blue", "blueberry"));
    tree.insert(std::make_pair(2, 2));
    tree.insert(std::make_pair(1, 1));
    tree.insert(std::make_pair(3, 3));
    tree.insert(std::make_pair(4, 4));
    tree.insert(std::make_pair(5, 5));
    tree.insert(std::make_pair(6, 6));
    tree.insert(std::make_pair(7, 7));
    
    tree.deleteNode(1);
    // tree[-100] = "world";
    // tree[-1] = "world2";
    // tree[-71] = "world3";
    // tree[741] = "world4";
    // tree[-252] = "world5";
    // tree[252] = "world5";

    // print the tree
    // int i = -101;
    // // std::cout << "Print the map with iterato: " << tree.size() << std::endl;
    // while (i < tree.size())
    // {
    //     std::cout << tree[i] << std::endl;
    //     i++;
    // }

    // tree.insert(std::pair<int, std::string>(1, "1"));
    // tree.insert(std::pair<int, std::string>(2, "2"));
    // tree.insert(std::pair<int, std::string>(3, "3"));
    // tree.insert(std::pair<int, std::string>(4, "4"));
    // tree.insert(std::pair<int, std::string>(5, "5"));
    // tree.insert(std::pair<int, std::string>(6, "6"));
    // tree.printTree();
    // std::cout << (tree.isRBProper() ? "\033[0;32mGOOD RBT" : "\033[0;31mNOT GOOD RDT") << RESET << std::endl;
    // std::cout << tree._end_() << std::endl;
    // std::cout << tree.search(2) << std::endl;
    // std::cout << tree._begin_() << std::endl;
    // std::cout << tree._size_() << std::endl;

    // add a lot of values to the tree

    // for (int i = 0; i < 100; i++)
    // {
    //     tree.insert(std::pair<std::string, std::string>(std::to_string(i), std::to_string(i)));
    // }
    // tree.printTree();
    // std::cout << "size of tree " << tree._size_() << "\n"
    //           << (tree.isRBProper() ? "\033[0;32mGOOD RBT" : "\033[0;31mNOT GOOD RDT") << RESET << std::endl;
    // // remove a value from the tree
    tree.printTree();
    // std::cout << "size of tree " << tree._size_() << "\n"
            //   << (tree.isRBProper() ? "\033[0;32mGOOD RBT" : "\033[0;31mNOT GOOD RDT") << RESET << std::endl;
    // tree._end_();
    // std::cout << tree.begin() << std::endl;
    //print tree with iterator
    // for (auto it = tree.begin(); it != tree.end(); ++it)
    // {
    //     std::cout << it->first << " " << it->second << std::endl;
    // }
    return 0;
}
