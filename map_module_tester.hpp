#ifndef MAP_MODULE_TESTER_HPP
#define MAP_MODULE_TESTER_HPP

#ifndef USING_STD
#define USING_STD 1
#endif
#if USING_STD //CREATE A REAL STL EXAMPLE
	#include <map>
	namespace ft = std;
#else
	#include <map.hpp>
#endif

#include <iostream>

template <typename K, typename V>
void print_map(ft::map<K, V>& map);

void map_constructors();
void map_assign_operator();
void map_iterators();
void map_capacity_functions();
void map_element_access_functions();
void map_inserts();
void map_erases();
void map_swap_clear();
void map_find();
void map_count();
void map_lower_bound();
void map_upper_bound();
void map_equal_range();
void map_relational_operators();

#endif
