#include <iostream>
#include <string>
#include <vector>
#include "vector.hpp"
#include "iterator_traits.hpp"

int main(void) {
    ft::vector<int> ft_v;
    std::vector<int> std_v;

    for (int i = 0; i < 10; i++) {
        ft_v.push_back(i);
        std_v.push_back(i);
    }

    std::cout << "[insert int 0~9]" << std::endl;
    std::cout << std::endl;

    std::cout << "[ft::vector.size()]      : " << ft_v.size() << std::endl;
    std::cout << "[std::vector.size()]     : " << std_v.size() << std::endl;
    std::cout << "[ft::vector.capacity()]  : " << ft_v.capacity() << std::endl;
    std::cout << "[std::vector.capacity()] : " << std_v.capacity() << std::endl;

    std::cout << std::endl;

    std::cout << "resize(5)" << std::endl;

    ft_v.resize(5);
    std_v.resize(5);

    std::cout << "[ft::vector.size()]      : " << ft_v.size() << std::endl;
    std::cout << "[std::vector.size()]     : " << std_v.size() << std::endl;
    std::cout << "[ft::vector.capacity()]  : " << ft_v.capacity() << std::endl;
    std::cout << "[std::vector.capacity()] : " << std_v.capacity() << std::endl;

    std::cout << std::endl;

    std::cout << "[ft::vector]             : ";
    for (size_t i = 0; i < ft_v.size(); i++) {
        std::cout << ft_v[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "[std::vector]            : ";
    for (size_t i = 0; i < std_v.size(); i++) {
        std::cout << std_v[i] << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl;

    std::cout << "resize(25)" << std::endl;

    std::cout << std::endl;

    ft_v.resize(25);
    std_v.resize(25);

    std::cout << "[ft::vector.size()]      : " << ft_v.size() << std::endl;
    std::cout << "[std::vector.size()]     : " << std_v.size() << std::endl;
    std::cout << "[ft::vector.capacity()]  : " << ft_v.capacity() << std::endl;
    std::cout << "[std::vector.capacity()] : " << std_v.capacity() << std::endl;

    std::cout << std::endl;

    std::cout << "[ft::vector]             : ";
    for (size_t i = 0; i < ft_v.size(); i++) {
        std::cout << ft_v[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "[std::vector]            : ";
    for (size_t i = 0; i < std_v.size(); i++) {
        std::cout << std_v[i] << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl;
    
    return (0);
}