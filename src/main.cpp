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
    tree.insert(std::pair<int, std::string>(1, "one"));
    tree.insert(std::pair<int, std::string>(2, "two"));
    tree.insert(std::pair<int, std::string>(3, "three"));
    tree.insert(std::pair<int, std::string>(4, "four"));
    tree.insert(std::pair<int, std::string>(5, "five"));
    tree.insert(std::pair<int, std::string>(6, "six"));

    // add a lot of values to the tree with pair
    for (int i = 0; i < 100; i++)
    {
        tree.insert(std::pair<int, std::string>(i, std::to_string(i)));
    }
   
    // add same values to the map
    std::map<int, int> map;
    map.insert(std::pair<int, int>(20, 20));
    map.insert(std::pair<int, int>(52, 52));
    map.insert(std::pair<int, int>(55, 55));
    map.insert(std::pair<int, int>(16, 16));
    map.insert(std::pair<int, int>(93, 93));
    map.insert(std::pair<int, int>(61, 61));
    map.insert(std::pair<int, int>(76, 76));
    map.insert(std::pair<int, int>(71, 71));
    map.insert(std::pair<int, int>(85, 85));
    map.insert(std::pair<int, int>(101, 101));
    map.insert(std::pair<int, int>(81, 81));
    map.insert(std::pair<int, int>(65, 65));

    
    // print the tree
    tree.printTree();
    std::cout << (tree.isRBProper()? "\033[0;32mGOOD RBT":  "\033[0;31mNOT GOOD RDT") << RESET << std::endl;
    // tree.deleteNode("a");
    // std::cout << "after delete (a) \n" << (tree.isRBProper()? "\033[0;32mGOOD RBT":  "\033[0;31mNOT GOOD RDT")<< RESET << std::endl;
    // tree.deleteNode("b");
    // std::cout << "after delete (b) \n" << (tree.isRBProper()? "\033[0;32mGOOD RBT":  "\033[0;31mNOT GOOD RDT")<< RESET << std::endl;
    // // std::cout << tree.end() << std::endl;
    // //add a lot of values
    // std::cout << "after insert 100 values \n" << (tree.isRBProper()? "\033[0;32mGOOD RBT":  "\033[0;31mNOT GOOD RDT")<< RESET << std::endl;
    // tree.deleteNode("99");
    // std::cout << "after delete (99) \n" << (tree.isRBProper()? "\033[0;32mGOOD RBT":  "\033[0;31mNOT GOOD RDT")<< RESET << std::endl;
    // tree.deleteNode("98");
    // std::cout << "after delete (98) \n" << (tree.isRBProper()? "\033[0;32mGOOD RBT":  "\033[0;31mNOT GOOD RDT")<< RESET << std::endl;
    // tree.deleteNode("97");
    // std::cout << "after delete (97) \n" << (tree.isRBProper()? "\033[0;32mGOOD RBT":  "\033[0;31mNOT GOOD RDT")<< RESET << std::endl;
    // //print 
    // tree.printTree();
    // std::cout << (tree.isRBProper()? "\033[0;32mGOOD RBT":  "\033[0;31mNOT GOOD RDT")<< RESET << std::endl;
    //print the end
    tree.end();
    // get root of map
    return 0;
}
