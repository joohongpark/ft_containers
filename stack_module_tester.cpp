#include "stack_module_tester.hpp"

void stack_push_pop_repeat() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::stack<int> ft_stack;
    for (int i = 0; i < 50000; i++) {
        ft_stack.push(i);
    }
    std::cout << ft_stack.top() << std::endl;
    for (int i = 0; i < 1234; i++) {
        ft_stack.pop();
    }
    std::cout << ft_stack.top() << std::endl;
}

void stack_relational_operators() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::stack<int> foo;
    ft::stack<int> bar;

    for (int i = 0; i < 50000; i++) {
        foo.push(i);
        bar.push(i);
    }

    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}
