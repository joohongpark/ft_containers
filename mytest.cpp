#include <iostream>
#include "vector_module_tester.hpp"

int main(void) {
    if (USING_STD) {
        std::cout << "USING std" << std::endl;
    } else {
        std::cout << "USING ft" << std::endl;
    }
    // vector test
    vec_constructors();
    vec_assign_operator();
    vec_iterators();
    vec_capacity_functions();
    vec_element_access_functions();
    vec_assigns();
    vec_push_pop_check();
    vec_inserts();
    return (0);
}