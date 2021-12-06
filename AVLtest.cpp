#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>
#include <map>

#include "AVLTree.hpp"

int main() {
    AVLTree<int, std::less<int>, std::allocator<int> > t;
    for (int i = 0; i < 29; i++) {
        t.insert(i);
    }
    std::cout << "min : " << t.getmin() << std::endl;
    std::cout << "max : " << t.getmax() << std::endl;
    t.__debug();
    return (0);
}