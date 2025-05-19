#include <iostream>
#include "search_tree.hpp"

int main() {
    SearchTree<int> t;
    t.add(0);    
    t.add(1);
    t.add(4);
    t.add(2);
    t.add(3);
    t.print(std::cout);
    std::cout<< std::endl << t.contains(4) << " " << t.contains(-1);
    return 0;
}