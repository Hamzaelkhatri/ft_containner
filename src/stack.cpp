
#include <stack>
#include <iostream>
#include "stack.hpp"

int main()
{
    // Create a stack of ints
    ft::stack<int> intStack;
    std::stack<int> stdStack;

    // Push some values onto the stack
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);
    intStack.push(4);

    // push some values onto the std::stack
    stdStack.push(1);
    stdStack.push(2);
    stdStack.push(3);
    stdStack.push(4);

    // Print the values on the stack
    std::cout << "intStack: ";
    while (!intStack.empty())
    {
        std::cout << intStack.top() << " ";
        intStack.pop();
    }

    std::cout << std::endl;

    // Print the values on the std::stack
    std::cout << "stdStack: ";
    while (!stdStack.empty())
    {
        std::cout << stdStack.top() << " ";
        stdStack.pop();
    }
    std::cout << std::endl;

    return 0;
}