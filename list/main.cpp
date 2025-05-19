#include <iostream>
#include "DLL.hpp"

int main() {
    int data[] = {1,2, 3, 4, 5, 6};
    DLList<int> list(data, 0);

    // list.pushFront(1);
    // list.pushFront(2);
    // list.popLast();
    // list.popFirst();
    // list.pushBack(3);
    // list.pushBack(5);
    for (int i = 0; i < 6; i++)
        list.pushFront(data[i]);
    
    
    list.print();
}   