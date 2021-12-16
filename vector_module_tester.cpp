#include "vector_module_tester.hpp"

template <typename T>
void print_vector(ft::vector<T>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << "]" << std::endl;
}

void vec_constructors() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::vector<int> default_construct;
    ft::vector<int> fill_construct((size_t)10, 42);
    ft::vector<int> range_construct(fill_construct.begin(), fill_construct.end());
    ft::vector<int> copy_construct(range_construct);

    print_vector(default_construct);
    print_vector(fill_construct);
    print_vector(range_construct);
    print_vector(copy_construct);
}

void vec_assign_operator() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::vector<int> fill_construct((size_t)10, 42);
    ft::vector<int> assign_op_target;

    assign_op_target = fill_construct;

    print_vector(assign_op_target);
    print_vector(fill_construct);
}

void vec_iterators() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::vector<char> vec;

    for (char c = 'a'; c < 'z'; c++) {
        vec.push_back(c);
    }
    
    // begin() / end() / * operator
    for (ft::vector<char>::iterator iter = vec.begin(); iter != vec.end(); iter++) {
        std::cout << *iter;
    }
    std::cout << std::endl;
    
    // const operator check / +, - operator
    for (ft::vector<char>::const_iterator iter = vec.begin() + 1; iter != vec.end() - 1; iter++) {
        std::cout << *iter;
    }
    std::cout << std::endl;

    // ++, --, operation between iterator and iterator
    ft::vector<char>::iterator a = vec.begin();
    ft::vector<char>::iterator b = vec.end();
    a++;
    b--;
    ft::vector<char>::difference_type diff = b - a;
    ft::vector<char>::difference_type diff1 = a - b;
    std::cout << "diff : " << diff << ", " << diff1 << std::endl;

    // reverse operator test
    for (ft::vector<char>::reverse_iterator iter = vec.rbegin(); iter != vec.rend(); iter++) {
        std::cout << *iter;
    }
    std::cout << std::endl;
}

void vec_capacity_functions() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::vector<char> vec;

    // size(), capacity(), empty() test
    std::cout << "1 : " << vec.size() << ", " << vec.capacity() << ", " <<  vec.empty() << std::endl;

    vec.reserve(5); // reserve() test
    // size(), capacity(), empty() for reserve()
    std::cout << "2 : " << vec.size() << ", " << vec.capacity() << ", " <<  vec.empty() << std::endl;

    for (char c = 'a'; c < 'z'; c++) {
        vec.push_back(c);
    }
    // size(), capacity(), empty() for size change
    std::cout << "3 : " << vec.size() << ", " << vec.capacity() << ", " <<  vec.empty() << std::endl;

    vec.resize(10); // resize() test
    // size(), capacity(), empty() for resize()
    std::cout << "3 : " << vec.size() << ", " << vec.capacity() << ", " <<  vec.empty() << std::endl;

    print_vector(vec); // print vec
}

void vec_element_access_functions() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::vector<char> vec;
    for (char c = 'a'; c < 'z'; c++) {
        vec.push_back(c);
    }

    // [] test
    std::cout << vec[0];
    std::cout << vec[21];
    std::cout << vec[9];
    std::cout << vec[8];
    std::cout << vec[7];
    std::cout << vec[10];
    std::cout<< std::endl;

    // at() test
    std::cout << vec.at(0);
    std::cout << vec.at(21);
    std::cout << vec.at(9);
    std::cout << vec.at(8);
    std::cout << vec.at(7);
    std::cout << vec.at(10);
    std::cout<< std::endl;

    // front test
    std::cout << vec.front();
    std::cout<< std::endl;

    // back test
    std::cout << vec.back();
    std::cout<< std::endl;
}

void vec_assigns() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::vector<char> vec_origin;
    for (char c = 'a'; c < 'z'; c++) {
        vec_origin.push_back(c);
    }

    ft::vector<char> vec_range;
    ft::vector<char> vec_fill;
    for (char c = 'a'; c < 'z'; c++) {
        vec_range.push_back(c);
        vec_fill.push_back(c);
    }
    vec_range.assign(vec_origin.begin() + 10, vec_origin.end() - 5);
    vec_fill.assign(12, 'X');

    print_vector(vec_range); // print vec_range
    print_vector(vec_fill); // print vec_fill
}

void vec_push_pop_check() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::vector<char> vec;
    for (char c = 'a'; c < 'z'; c++) {
        vec.push_back(c);
    }
    // size(), capacity(), empty() test
    std::cout << "1 : " << vec.size() << ", " << vec.capacity() << ", " <<  vec.empty() << std::endl;
    for (char c = 'a'; c < 'g'; c++) {
        vec.pop_back();
    }
    // size(), capacity(), empty() test
    std::cout << "1 : " << vec.size() << ", " << vec.capacity() << ", " <<  vec.empty() << std::endl;
}

void vec_inserts() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::vector<char> vec_origin;
    for (char c = 'a'; c < 'z'; c++) {
        vec_origin.push_back(c);
    }

    ft::vector<char> vec_single_element;
    ft::vector<char> vec_fill;
    ft::vector<char> vec_range;
    for (char c = 'a'; c < 'z'; c++) {
        vec_single_element.push_back(c);
        vec_fill.push_back(c);
        vec_range.push_back(c);
    }

    vec_single_element.insert(vec_single_element.begin() + 10, 'X');
    vec_fill.insert(vec_fill.begin() + 10, 10, 'X');
    vec_range.insert(vec_range.begin() + 10, vec_origin.begin(), vec_origin.end());
    print_vector(vec_single_element); // print vec_single_element
    print_vector(vec_fill); // print vec_fill
    print_vector(vec_range); // print vec_range
}

void vec_erases() {
    std::cout << "[" << __func__ << "]" << std::endl;
    ft::vector<char> vec_pos;
    ft::vector<char> vec_range;
    for (char c = 'a'; c < 'z'; c++) {
        vec_pos.push_back(c);
        vec_range.push_back(c);
    }

    // iterator erase (iterator position); test
    std::cout << *(vec_pos.erase(vec_pos.begin())) << std::endl;
    std::cout << *(vec_pos.erase(vec_pos.begin() + 1)) << std::endl;
    std::cout << *(vec_pos.erase(vec_pos.begin() + 3)) << std::endl;

    // iterator erase (iterator first, iterator last); test
    std::cout << *(vec_range.erase(vec_range.begin() + 10, vec_range.end() - 5)) << std::endl;
    std::cout << *(vec_range.erase(vec_range.begin(), vec_range.begin() + 2)) << std::endl;

    print_vector(vec_pos); // print vec_pos
    print_vector(vec_range); // print vec_range
}

void vec_swap_clear() {
    ft::vector<int> v1((size_t)10, 42);
    ft::vector<int> v2;
    ft::vector<int> v3((size_t)10, 42);

    v2.swap(v1);
    print_vector(v1); // print v1
    print_vector(v2); // print v2
    print_vector(v3); // print v3
    v2.clear();
    ft::vector<int>().swap(v3);
    print_vector(v1); // print v1
    print_vector(v2); // print v2
    print_vector(v3); // print v3

}

void vec_relational_operators() {
    ft::vector<int> foo (3,100);   // three ints with a value of 100
    ft::vector<int> bar (2,200);   // two ints with a value of 200

    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}