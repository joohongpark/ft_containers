#include <vector>
#include <vector.hpp>
#include "vector_module_tester.hpp"

bool copy_constructor() {
    std::vector<int> std_v;
    ft::vector<int> ft_v;

    for (int i = 0; i < 10; i++) {
        std_v.push_back(i);
        ft_v.push_back(i);
    }
    ft::vector<int> ft_cp_v(ft_v);
    std::vector<int> std_cp_v(std_v);
    if ((ft_v[9] != ft_cp_v[9]) || (std_v[9] != std_cp_v[9])
     || (ft_v.size() != ft_cp_v.size()) || (std_v.size() != std_cp_v.size())) {
        return (false);
    }

    return (true);
}

bool assign_operator() {
    std::vector<int> std_v;
    ft::vector<int> ft_v;

    for (int i = 0; i < 10; i++) {
        std_v.push_back(i);
        ft_v.push_back(i);
    }
    ft::vector<int> ft_cp_v = ft_v;
    std::vector<int> std_cp_v = std_v;
    if ((ft_v[9] != ft_cp_v[9]) || (std_v[9] != std_cp_v[9])
     || (ft_v.size() != ft_cp_v.size()) || (std_v.size() != std_cp_v.size())) {
        return (false);
    }
    return (true);
}

bool size() {
    ft::vector<int> ft_v;
    std::vector<int> std_v;

    for (int i = 0; i < 10; i++) {
        ft_v.push_back(i);
        std_v.push_back(i);
    }

    if (ft_v.size() != std_v.size()) { return (false); }
    if (ft_v.capacity() != std_v.capacity()) { return (false); }

    ft_v.resize(5);
    std_v.resize(5);

    if (ft_v.size() != std_v.size()) { return (false); }
    if (ft_v.capacity() != std_v.capacity()) { return (false); }

    for (size_t i = 0; i < ft_v.size(); i++) {
        if (ft_v[i] != std_v[i]) {
            return (false);
        }
    }

    ft_v.resize(25);
    std_v.resize(25);

    if (ft_v.size() != std_v.size()) { return (false); }
    if (ft_v.capacity() != std_v.capacity()) { return (false); }

    for (size_t i = 0; i < ft_v.size(); i++) {
        if (ft_v[i] != std_v[i]) {
            return (false);
        }
    }

    return (true);
}

bool element_access() {
    std::vector<int> std_v;
    ft::vector<int> ft_v;

    for (int i = 0; i < 10; i++) {
        std_v.push_back(i);
        ft_v.push_back(i);
    }
    if ((ft_v[9] != std_v[9])
     || (ft_v.at(1) != std_v.at(1))
     || (ft_v.front() != std_v.front())
     || (ft_v.back() != std_v.back())) {
        return (false);
    }
    std_v.clear();
    ft_v.clear();
    if (!ft_v.empty() || !std_v.empty()) {
        return (false);
    }
    try {
        int i = ft_v[9];
        (void)i;
        return (false);
    } catch(const std::exception& e) { }
    
    return (true);
}

bool push_pop_access() {
    std::vector<int> std_v;
    ft::vector<int> ft_v;

    for (int i = 0; i < 10; i++) {
        std_v.push_back(i);
        ft_v.push_back(i);
    }

    for (int i = 0; i < 10; i++) {
        if (ft_v.back() != std_v.back()) {
            return (false);
        }
        std_v.pop_back();
        ft_v.pop_back();
    }
    return (true);
}

bool swap() {
    std::vector<int> std_v;
    ft::vector<int> ft_v;
    std::vector<int> std_v_empty;
    ft::vector<int> ft_v_empty;

    for (int i = 0; i < 10; i++) {
        std_v.push_back(i);
        ft_v.push_back(i);
    }
    std_v_empty.swap(std_v);
    ft_v_empty.swap(ft_v);
    if (!ft_v.empty() || !std_v.empty()) { return (false); }
    if (ft_v.size() != std_v.size()) { return (false); }
    if (ft_v.capacity() != std_v.capacity()) { return (false); }
    return (true);
}

bool iterator() {
    std::vector<int> std_v;
    ft::vector<int> ft_v;

    for (int i = 0; i < 10; i++) {
        std_v.push_back(i);
        ft_v.push_back(i);
    }

    ft::vector<int> ft_cp_v(ft_v);
    std::vector<int> std_cp_v(std_v);

    // vector 컨테이너끼리의 논리연산은 내부적으로 이터레이터를 통해 비교한다.
    if ((ft_v != ft_cp_v) || (std_v != std_cp_v)) {
        return (false);
    }

    ft::vector<int> ft_cp_iter(ft_v.begin() + 1, ft_v.end() - 1);
    std::vector<int> std_cp_iter(std_v.begin() + 1, std_v.end() - 1);

    if (ft_cp_iter.size() != std_cp_iter.size()) { return (false); }
    if (ft_cp_iter.capacity() != std_cp_iter.capacity()) { return (false); }

    for (size_t i = 0; i < ft_cp_iter.size(); i++) {
        if (ft_cp_iter[i] != std_cp_iter[i]) {
            return (false);
        }
    }
    
    return (true);
}

bool const_iterator() {
    std::vector<int> std_v;
    ft::vector<int> ft_v;

    for (int i = 0; i < 10; i++) {
        std_v.push_back(i);
        ft_v.push_back(i);
    }
    std::vector<int>::const_iterator std_v_citer = std_v.begin();
    ft::vector<int>::const_iterator ft_v_citer = ft_v.begin();
    while (std_v_citer != std_v.end()) {
        if (*std_v_citer != *ft_v_citer) {
            return (false);
        }
        std_v_citer++;
        ft_v_citer++;
    }
    return (true);
}

