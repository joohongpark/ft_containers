#include <iostream>
#include <string>
#include "map.hpp"
#include <map>

int main(void) {
    ft::map<int, std::string> m;
    std::map<int, std::string> m1;

    for (int i = 0; i < 5; i++) {
        m[i] = "문자열";
        m1[i] = "문자열";
    }

    ft::map<int, std::string>::iterator eiter = m.end();
    eiter--;
    std::cout << "end-- : " << (*eiter).first << std::endl;


    ft::map<int, std::string>::iterator iter = m.begin();
    while (iter != m.end()) {
        std::cout << (*iter).first << std::endl;
        iter++;
    }
    std::cout << "============================" << std::endl;
    ft::map<int, std::string>::reverse_iterator riter = m.rbegin();
    while (riter != m.rend()) {
        std::cout << (*riter).first << std::endl;
        riter++;
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