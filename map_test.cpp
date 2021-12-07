#include <iostream>
#include <string>
#include "map.hpp"

int main(void) {
    ft::map<int, std::string> m;

    for (int i = 0; i < 33; i++) {
        m[i] = "문자열";
    }

    for (int i = 0; i < 10; i++) {
        std::cout << m[i] << std::endl;
    }
    m.debug();

    return (0);
}