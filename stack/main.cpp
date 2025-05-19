#include <iostream>
#include "linked_stack.hpp"

int main() {
    LStack<int> s;
    std::cout << s.isEmpty() << std::endl;
    s.push(10);
    std::cout << s.isEmpty() << std::endl;
    std::cout << s.peek() << std::endl;
    s.pop();
    std::cout << s.isEmpty() << std::endl;
    for (int i = 0; i < 100; i++)
        s.push(i);
    std::cout << s.peek() << std::endl;

    return 0;
}