#ifndef MAP_MODULE_TESTER_HPP
#define MAP_MODULE_TESTER_HPP

#include <iostream>
#include <string>
#include "map.hpp"
#include <map>
#include "vector.hpp"
#include <vector>

bool insert_value_method_tester(int n, std::string str) {
    typedef ft::map<int, std::string>::iterator ftiter;
    typedef std::map<int, std::string>::iterator stditer;
    typedef ft::map<int, std::string>::value_type ftvalue;
    typedef std::map<int, std::string>::value_type stdvalue;
    ft::map<int, std::string> ft_map;
    std::map<int, std::string> std_map;

    for (int i = 0; i < 5; i++) {
        ft_map[i] = "문자열";
        std_map[i] = "문자열";
    }

    ftvalue ft_v(n, str);
    stdvalue std_v(n, str);

    ft::pair<ftiter, bool> ft_p = ft_map.insert(ft_v);
    std::pair<stditer, bool> std_p = std_map.insert(std_v);

    if (ft_p.second != std_p.second) {
        std::cout << "[" << __func__ << "]" << std::endl;
        std::cout << "ft_p.second : " << ft_p.second << std::endl;
        std::cout << "std_p.second : " << std_p.second << std::endl;
        return (false);
    }

    if ((*(ft_p.first)).first != (*(std_p.first)).first) {
        std::cout << "[" << __func__ << "]" << std::endl;
        std::cout << "(*(ft_p.first)).first : " << (*(ft_p.first)).first << std::endl;
        std::cout << "(*(std_p.first)).first : " << (*(std_p.first)).first << std::endl;
        return (false);
    }

    if ((*(ft_p.first)).second != (*(std_p.first)).second) {
        std::cout << "[" << __func__ << "]" << std::endl;
        std::cout << "(*(ft_p.first)).second : " << (*(ft_p.first)).second << std::endl;
        std::cout << "(*(std_p.first)).second : " << (*(std_p.first)).second << std::endl;
        return (false);
    }
    return (true);
}

bool insert_iter_method_tester(int n, std::string str) {
    typedef ft::map<int, std::string>::iterator ftiter;
    typedef std::map<int, std::string>::iterator stditer;
    typedef ft::map<int, std::string>::value_type ftvalue;
    typedef std::map<int, std::string>::value_type stdvalue;
    ft::map<int, std::string> ft_map;
    std::map<int, std::string> std_map;

    for (int i = 0; i < 5; i++) {
        ft_map[i] = "문자열";
        std_map[i] = "문자열";
    }

    ftvalue ft_v(n, str);
    stdvalue std_v(n, str);

    ftiter ft_iter = ft_map.begin();
    stditer std_iter = std_map.begin();

    ft_iter = ft_map.insert(ft_iter, ft_v);
    std_iter = std_map.insert(std_iter, std_v);

    while (std_iter != std_map.end()) {
        if ((*(std_iter)).first != (*(ft_iter)).first
        || (*(std_iter)).second != (*(ft_iter)).second) {
            std::cout << "[" << __func__ << "]" << std::endl;
            std::cout << "ft_iter : " << (*(ft_iter)).first << ", " << (*(ft_iter)).second << std::endl;
            std::cout << "std_iter : " << (*(std_iter)).first << ", " << (*(std_iter)).second << std::endl;
            return (false);
        }
        ft_iter++;
        std_iter++;
    }

    return (true);
}

bool insert_inputiter_method_tester() {
    // 벡터에서 push_back으로 값을 삽입할 때 복사 생성자로 삽입되어야 하는지 검토
    typedef ft::map<int, std::string>::iterator ftiter;
    typedef std::map<int, std::string>::iterator stditer;
    typedef ft::pair<int, std::string> ftvalue;
    typedef std::pair<int, std::string> stdvalue;
    ft::map<int, std::string> ft_map;
    std::map<int, std::string> std_map;

    ft::vector<ftvalue> ft_vec;
    std::vector<stdvalue> std_vec;

    for (int i = 0; i < 5; i++) {
        ftvalue ft_v(i, "문자열");
        stdvalue std_v(i, "문자열");
        ft_vec.push_back(ft_v);
        std_vec.push_back(std_v);
    }

    ft_map.insert(ft_vec.begin(), ft_vec.end());
    std_map.insert(std_vec.begin(), std_vec.end());

    ftiter ft_iter = ft_map.begin();
    stditer std_iter = std_map.begin();

    while (std_iter != std_map.end()) {
        if ((*(std_iter)).first != (*(ft_iter)).first
        || (*(std_iter)).second != (*(ft_iter)).second) {
            std::cout << "[" << __func__ << "]" << std::endl;
            std::cout << "ft_iter : " << (*(ft_iter)).first << ", " << (*(ft_iter)).second << std::endl;
            std::cout << "std_iter : " << (*(std_iter)).first << ", " << (*(std_iter)).second << std::endl;
            return (false);
        }
        ft_iter++;
        std_iter++;
    }
    if (ft_map.size() != std_map.size()) {
        std::cout << "[" << __func__ << "]" << std::endl;
        std::cout << "ft_map.size() : " << ft_map.size() << std::endl;
        std::cout << "std_map.size() : " << std_map.size() << std::endl;
        return (false);
    }
    return (true);
}

bool erase_method_tester() {
    typedef ft::map<int, std::string>::iterator ftiter;
    typedef std::map<int, std::string>::iterator stditer;
    ft::map<int, std::string> ft_map;
    std::map<int, std::string> std_map;

    for (int i = 0; i < 15; i++) {
        ft_map[i] = "문자열";
        std_map[i] = "문자열";
    }

    ft_map.erase(3);
    std_map.erase(3);

    return (true);

    ftiter ft_iter = ft_map.begin();
    stditer std_iter = std_map.begin();
    ft_iter = ft_map.erase(ft_iter);
    std_iter = std_map.erase(std_iter);

    while (ft_iter != ft_map.end()) {
        if ((*(std_iter)).first != (*(ft_iter)).first
        || (*(std_iter)).second != (*(ft_iter)).second) {
            std::cout << "[" << __func__ << "]" << std::endl;
            std::cout << "ft_iter : " << (*(ft_iter)).first << ", " << (*(ft_iter)).second << std::endl;
            std::cout << "std_iter : " << (*(std_iter)).first << ", " << (*(std_iter)).second << std::endl;
            return (false);
        }
        ft_iter++;
        std_iter++;
    }
    if (ft_map.size() != std_map.size()) {
        std::cout << "[" << __func__ << "]" << std::endl;
        std::cout << "ft_map.size() : " << ft_map.size() << std::endl;
        std::cout << "std_map.size() : " << std_map.size() << std::endl;
        return (false);
    }
    return (true);
}

bool clear_method_tester() {
    typedef ft::map<int, std::string>::iterator ftiter;
    typedef std::map<int, std::string>::iterator stditer;
    ft::map<int, std::string> ft_map;
    std::map<int, std::string> std_map;

    for (int i = 0; i < 15; i++) {
        ft_map[i] = "문자열";
        std_map[i] = "문자열";
    }
    if (ft_map.size() != std_map.size()) {
        std::cout << "[" << __func__ << "]" << std::endl;
        std::cout << "ft_map.size() : " << ft_map.size() << std::endl;
        std::cout << "std_map.size() : " << std_map.size() << std::endl;
        return (false);
    }
    ft_map.clear();
    std_map.clear();
    if (ft_map.size() != std_map.size()) {
        std::cout << "[" << __func__ << "]" << std::endl;
        std::cout << "ft_map.size() : " << ft_map.size() << std::endl;
        std::cout << "std_map.size() : " << std_map.size() << std::endl;
        return (false);
    }
    for (int i = 0; i < 15; i++) {
        ft_map[i] = "문자열";
        std_map[i] = "문자열";
    }
    if (ft_map.size() != std_map.size()) {
        std::cout << "[" << __func__ << "]" << std::endl;
        std::cout << "ft_map.size() : " << ft_map.size() << std::endl;
        std::cout << "std_map.size() : " << std_map.size() << std::endl;
        return (false);
    }
    ftiter ft_iter = ft_map.begin();
    stditer std_iter = std_map.begin();
    while (ft_iter != ft_map.end()) {
        if ((*(std_iter)).first != (*(ft_iter)).first
        || (*(std_iter)).second != (*(ft_iter)).second) {
            std::cout << "[" << __func__ << "]" << std::endl;
            std::cout << "ft_iter : " << (*(ft_iter)).first << ", " << (*(ft_iter)).second << std::endl;
            std::cout << "std_iter : " << (*(std_iter)).first << ", " << (*(std_iter)).second << std::endl;
            return (false);
        }
        ft_iter++;
        std_iter++;
    }
    return (true);
}

#endif
