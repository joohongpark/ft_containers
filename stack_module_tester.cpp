#include "stack_module_tester.hpp"

bool stack_push_pop_repeat() {
    std::stack<int> std_stack;
    ft::stack<int> ft_stack;
    for (int i = 0; i < 50000; i++) {
        std_stack.push(i);
        ft_stack.push(i);
    }
    while (!std_stack.empty() && ft_stack.empty()) {
        if (std_stack.top() != ft_stack.top()) {
            return (false);
        }
    }
    return (true);
}
