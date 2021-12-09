#include <iostream>
#include <string>
#include "map_module_tester.hpp"

int main(void) {
    if((insert_value_method_tester(0, "문자열") != true)
    || insert_value_method_tester(1000, "문자열") != true) {
        std::cout << "Error" << std::endl;
    } else {
        std::cout << "OK" << std::endl;
    }
    if((insert_iter_method_tester(0, "문자열") != true)
    || insert_iter_method_tester(1000, "문자열") != true
    || insert_iter_method_tester(2, "문1자열") != true) {
        std::cout << "Error" << std::endl;
    } else {
        std::cout << "OK" << std::endl;
    }
    if(insert_inputiter_method_tester() != true) {
        std::cout << "Error" << std::endl;
    } else {
        std::cout << "OK" << std::endl;
    }
    if(erase_method_tester() != true) {
        std::cout << "Error" << std::endl;
    } else {
        std::cout << "OK" << std::endl;
    }
    if (clear_method_tester() != true) {
        std::cout << "Error" << std::endl;
    } else {
        std::cout << "OK" << std::endl;
    }
    return (0);
}