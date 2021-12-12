#include <iostream>
#include "stack.hpp"
#include <stack>

int main()
{
    ft::stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    stack.push(6);
    stack.push(7);
    stack.push(8);
    stack.push(9);
    stack.push(10);

    std::cout << stack.top() << std::endl;
    std::cout << stack.size() << std::endl;
    std::cout << stack.empty() << std::endl;
    stack.pop();
    for (size_t i = 0; i < stack.size(); i++)
    {
        std::cout << stack.top() << std::endl;
        stack.pop();
    }
}