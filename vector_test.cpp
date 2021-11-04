#include <iostream>
#include <string>
#include "vector.hpp"
#include "iterator_traits.hpp"

int main(void) {
    ft::vector<int> v;

    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }

    std::cout << "size : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;

    ft::vector<int> copy1(v.begin() + 1, v.end() - 1);

    ft::vector<int> copy = v;

    ft::vector<int>::const_iterator iter = copy.begin();
    while (iter != copy.end()) {
        std::cout << *iter << std::endl;
        iter++;
    }
    
    return (0);
}