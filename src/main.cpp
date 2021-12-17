#include "RBT.hpp"

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

    // add values to the tree
    ft::RBT<std::string, std::less<std::string> > tree;
    tree.insert("a");
    tree.insert("b");
    tree.insert("c");
    tree.insert("d");
    tree.insert("e");
    tree.insert("f");
    tree.insert("g");
    tree.insert("h");

    // print the tree
    tree.printTree();
    std::cout << (tree.isRBProper()? "\033[0;32mGOOD RBT":  "\033[0;31mNOT GOOD RDT") << RESET << std::endl;
    tree.deleteNode("a");
    std::cout << "after delete (a) \n" << (tree.isRBProper()? "\033[0;32mGOOD RBT":  "\033[0;31mNOT GOOD RDT")<< RESET << std::endl;
    tree.deleteNode("b");
    std::cout << "after delete (b) \n" << (tree.isRBProper()? "\033[0;32mGOOD RBT":  "\033[0;31mNOT GOOD RDT")<< RESET << std::endl;
    std::cout << tree.end() << std::endl;
    return 0;
}
