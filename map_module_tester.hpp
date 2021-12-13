#ifndef MAP_MODULE_TESTER_HPP
#define MAP_MODULE_TESTER_HPP

#include <string>
#include <map>
#include <map.hpp>
#include <vector>
#include <vector.hpp>
#include <stdlib.h>

bool map_insert_big_size();
bool map_insert_value_method(int n, std::string str);
bool map_insert_iter_method(int n, std::string str);
bool map_insert_inputiter_method();
bool map_erase_method();
bool map_clear_method();
bool map_count_method();
bool map_find_method();
bool map_bound_method();
bool map_equal_method();
bool map_operator_method();

#endif
