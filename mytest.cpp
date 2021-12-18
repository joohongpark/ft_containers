#include <iostream>
#include "vector_module_tester.hpp"
#include "map_module_tester.hpp"
#include "stack_module_tester.hpp"

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
    vec_erases();
    vec_swap_clear();
    vec_relational_operators();

    // map test
    map_constructors();
    map_assign_operator();
    map_iterators();
    map_capacity_functions();
    map_element_access_functions();
    map_inserts();
    map_erases();
    map_swap_clear();
    map_find();
    map_count();
    map_lower_bound();
    map_upper_bound();
    map_equal_range();
    map_relational_operators();

    // stack test
    stack_push_pop_repeat();
    stack_relational_operators();
    return (0);
}