#include "RBT.hpp"

int main()
{

    // add values to the tree
    ft::RBT<int, std::less<int> > tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);

    // print the tree
    tree.printTree();
    // tree.insert(2);
    // tree.insert(3);
    // tree.insert(4);
    return 0;
}
