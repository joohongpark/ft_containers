#include <iostream>
#include <string>
#include "map.hpp"
#include <map>

int main(void) {
    ft::map<int, std::string> m;
    std::map<int, std::string> m1;

    for (int i = 0; i < 33; i++) {
        m[i] = "문자열";
        m1[i] = "문자열";
    }

    std::map<int, std::string>::reverse_iterator iter = m1.rbegin();
    std::cout << (*iter).first << std::endl;
    while (iter != m1.rend()) {
        std::cout << (*iter).first << std::endl;
        iter++;
    }

    ft::map<int, std::string>::const_iterator citer = m.begin();
    while (citer != m.end()) {
        std::cout << (*citer).second << std::endl;
        citer++;
    }

    /*
    for (int i = 0; i < 10; i++) {
        std::cout << m[i] << std::endl;
    }
    m.debug();
    std::cout << "map size : " << m.size() << std::endl;
    std::cout << "map max size : " << m.max_size() << std::endl;
    */
    return (0);
}