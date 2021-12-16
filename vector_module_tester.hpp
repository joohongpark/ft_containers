#ifndef VECTOR_MODULE_TESTER_HPP
#define VECTOR_MODULE_TESTER_HPP

#ifndef USING_STD
#define USING_STD 1
#endif
#if USING_STD //CREATE A REAL STL EXAMPLE
	#include <vector>
	namespace ft = std;
#else
	#include <vector.hpp>
#endif

#include <iostream>

template <typename T>
void print_vector(std::vector<T>& vec);

void vec_constructors();
void vec_assign_operator();
void vec_iterators();
void vec_capacity_functions();
void vec_element_access_functions();
void vec_assigns();
void vec_push_pop_check();
void vec_inserts();
#endif
