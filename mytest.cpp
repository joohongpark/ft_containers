#include <iostream>
#include "vector_module_tester.hpp"
#include "map_module_tester.hpp"
#include "stack_module_tester.hpp"

int main(void) {
    // vector test
    if (copy_constructor() != true)     { std::cout << "Error" << std::endl; } else { std::cout << "copy_constructor() OK" << std::endl; }
    if (assign_operator() != true)      { std::cout << "Error" << std::endl; } else { std::cout << "assign_operator() OK" << std::endl; }
    if (size() != true)                 { std::cout << "Error" << std::endl; } else { std::cout << "size() OK" << std::endl; }
    if (element_access() != true)       { std::cout << "Error" << std::endl; } else { std::cout << "element_access() OK" << std::endl; }
    if (push_pop_access() != true)      { std::cout << "Error" << std::endl; } else { std::cout << "push_pop_access() OK" << std::endl; }
    if (swap() != true)                 { std::cout << "Error" << std::endl; } else { std::cout << "swap() OK" << std::endl; }
    if (iterator() != true)             { std::cout << "Error" << std::endl; } else { std::cout << "iterator() OK" << std::endl; }
    if (const_iterator() != true)       { std::cout << "Error" << std::endl; } else { std::cout << "const_iterator() OK" << std::endl; }

    // map test
    if (map_insert_big_size() != true)                      { std::cout << "Error" << std::endl; } else { std::cout << "map_insert_big_size() OK" << std::endl; }
    if((map_insert_value_method(0, "문자열") != true)
        || map_insert_value_method(1000, "문자열") != true)   { std::cout << "Error" << std::endl; } else { std::cout << "map_insert_value_method() OK" << std::endl; }
    if((map_insert_iter_method(0, "문자열") != true)
        || map_insert_iter_method(1000, "문자열") != true
        || map_insert_iter_method(2, "문1자열") != true)      { std::cout << "Error" << std::endl; } else { std::cout << "map_insert_iter_method() OK" << std::endl; }

    if (map_insert_inputiter_method() != true)              { std::cout << "Error" << std::endl; } else { std::cout << "map_insert_inputiter_method() OK" << std::endl; }
    if (map_erase_method() != true)                         { std::cout << "Error" << std::endl; } else { std::cout << "map_erase_method() OK" << std::endl; }
    if (map_clear_method() != true)                         { std::cout << "Error" << std::endl; } else { std::cout << "map_clear_method() OK" << std::endl; }
    if (map_count_method() != true)                         { std::cout << "Error" << std::endl; } else { std::cout << "map_count_method() OK" << std::endl; }
    if (map_find_method() != true)                          { std::cout << "Error" << std::endl; } else { std::cout << "map_find_method() OK" << std::endl; }
    if (map_bound_method() != true)                         { std::cout << "Error" << std::endl; } else { std::cout << "map_bound_method() OK" << std::endl; }
    if (map_equal_method() != true)                         { std::cout << "Error" << std::endl; } else { std::cout << "map_equal_method() OK" << std::endl; }
    if (map_operator_method() != true)                      { std::cout << "Error" << std::endl; } else { std::cout << "map_operator_method() OK" << std::endl; }

    // stack test
    if (stack_push_pop_repeat() != true)                    { std::cout << "Error" << std::endl; } else { std::cout << "stack_push_pop_repeat() OK" << std::endl; }
    return (0);
}