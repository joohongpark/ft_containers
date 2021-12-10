#include <iostream>
#include <string>
#include "map_module_tester.hpp"

int main(void) {
    if((insert_value_method_tester(0, "문자열") != true)
    || insert_value_method_tester(1000, "문자열") != true) {
        std::cout << "Error" << std::endl;
    } else {
        std::cout << "insert_value_method_tester() OK" << std::endl;
    }
    if((insert_iter_method_tester(0, "문자열") != true)
    || insert_iter_method_tester(1000, "문자열") != true
    || insert_iter_method_tester(2, "문1자열") != true) {
        std::cout << "Error" << std::endl;
    } else {
        std::cout << "insert_iter_method_tester() OK" << std::endl;
    }
    if(insert_inputiter_method_tester() != true) {
        std::cout << "Error" << std::endl;
    } else {
        std::cout << "insert_inputiter_method_tester() OK" << std::endl;
    }
    if(erase_method_tester() != true) {
        std::cout << "Error" << std::endl;
    } else {
        std::cout << "erase_method_tester() OK" << std::endl;
    }
    if (clear_method_tester() != true) {
        std::cout << "Error" << std::endl;
    } else {
        std::cout << "clear_method_tester() OK" << std::endl;
    }
    if (count_method_tester() != true) {
        std::cout << "Error" << std::endl;
    } else {
        std::cout << "count_method_tester() OK" << std::endl;
    }
    if (find_method_tester() != true) {
        std::cout << "Error" << std::endl;
    } else {
        std::cout << "find_method_tester() OK" << std::endl;
    }
    if (bound_method_tester() != true) {
        std::cout << "Error" << std::endl;
    } else {
        std::cout << "bound_method_tester() OK" << std::endl;
    }
    if (equal_method_tester() != true) {
        std::cout << "Error" << std::endl;
    } else {
        std::cout << "bound_method_tester() OK" << std::endl;
    }
    return (0);
}