#ifndef STACK_MODULE_TESTER_HPP
#define STACK_MODULE_TESTER_HPP

#ifndef USING_STD
#define USING_STD 1
#endif
#if USING_STD //CREATE A REAL STL EXAMPLE
	#include <stack>
	namespace ft = std;
#else
	#include <stack.hpp>
#endif

#include <iostream>

void stack_push_pop_repeat();
void stack_relational_operators();

#endif
