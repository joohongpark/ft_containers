#include "map_module_tester.hpp"

bool map_insert_big_size() {
    int size = 1047552;
	srand(size);
    ft::map<int, int> ft_map;
    std::map<int, int> std_map;

    for (int i = 0; i < size; i++) {
        int rk = rand();
        int rv = rand();
		ft_map.insert(ft::make_pair(rk, rv));
		std_map.insert(std::make_pair(rk, rv));
        if ((ft_map.find(rk) == ft_map.end())
          || (std_map.find(rk) == std_map.end())) {
            return (false);
        }
    }
    if ((ft_map.size() != std_map.size())) {
        return (false);
    }
	int ft_sum = 0;
	int std_sum = 0;
	for (int i = 0; i < 10000; i++) {
		int access = rand();
		ft_sum += ft_map[access];
		std_sum += std_map[access];
	}
    if ((ft_sum != std_sum)) {
        return (false);
    }
    return (true);
}

bool map_insert_value_method(int n, std::string str) {
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
        return (false);
    }

    if ((*(ft_p.first)).first != (*(std_p.first)).first) {
        return (false);
    }

    if ((*(ft_p.first)).second != (*(std_p.first)).second) {
        return (false);
    }
    return (true);
}

bool map_insert_iter_method(int n, std::string str) {
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
            return (false);
        }
        ft_iter++;
        std_iter++;
    }

    return (true);
}

bool map_insert_inputiter_method() {
    typedef ft::pair<int, std::string> ftvalue;
    typedef std::pair<int, std::string> stdvalue;

    ft::vector<ftvalue> ft_vec;
    std::vector<stdvalue> std_vec;

    for (int i = 0; i < 5; i++) {
        ftvalue ft_v(i, "문자열");
        stdvalue std_v(i, "문자열");
        ft_vec.push_back(ft_v);
        std_vec.push_back(std_v);
    }

    ft::map<int, std::string> ft_map(ft_vec.begin(), ft_vec.end());
    std::map<int, std::string> std_map(std_vec.begin(), std_vec.end());

    ft::map<int, std::string>::iterator ft_iter = ft_map.begin();
    std::map<int, std::string>::iterator std_iter = std_map.begin();

    while (std_iter != std_map.end()) {
        if ((*(std_iter)).first != (*(ft_iter)).first
        || (*(std_iter)).second != (*(ft_iter)).second) {
            return (false);
        }
        ft_iter++;
        std_iter++;
    }

    if (ft_map.size() != std_map.size()) {
        return (false);
    }
    return (true);
}

bool map_erase_method() {
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
            return (false);
        }
        ft_iter++;
        std_iter++;
    }
    if (ft_map.size() != std_map.size()) {
        return (false);
    }
    return (true);
}

bool map_clear_method() {
    typedef ft::map<int, std::string>::iterator ftiter;
    typedef std::map<int, std::string>::iterator stditer;
    ft::map<int, std::string> ft_map;
    std::map<int, std::string> std_map;

    for (int i = 0; i < 15; i++) {
        ft_map[i] = "문자열";
        std_map[i] = "문자열";
    }
    if (ft_map.size() != std_map.size()) {
        return (false);
    }
    ft_map.clear();
    std_map.clear();
    if (ft_map.size() != std_map.size()) {
        return (false);
    }
    for (int i = 0; i < 15; i++) {
        ft_map[i] = "문자열";
        std_map[i] = "문자열";
    }
    if (ft_map.size() != std_map.size()) {
        return (false);
    }
    ftiter ft_iter = ft_map.begin();
    stditer std_iter = std_map.begin();
    while (ft_iter != ft_map.end()) {
        if ((*(std_iter)).first != (*(ft_iter)).first
        || (*(std_iter)).second != (*(ft_iter)).second) {
            return (false);
        }
        ft_iter++;
        std_iter++;
    }
    return (true);
}

bool map_count_method() {
    ft::map<int, std::string> ft_map;
    std::map<int, std::string> std_map;

    for (int i = 0; i < 15; i++) {
        ft_map[i] = "문자열";
        std_map[i] = "문자열";
    }
    if (ft_map.count(-1) != std_map.count(-1)) {
        return (false);
    }
    if (ft_map.count(1) != std_map.count(1)) {
        return (false);
    }
    if (ft_map.count(10) != std_map.count(10)) {
        return (false);
    }

    return (true);
}

bool map_find_method() {
    ft::map<int, std::string> ft_map;
    std::map<int, std::string> std_map;

    for (int i = 0; i < 15; i++) {
        ft_map[i] = "문자열";
        std_map[i] = "문자열";
    }

    if (ft_map.find(-1) != ft_map.end()) {
        return (false);
    }
    if ((*(ft_map.find(1))).first != (*(std_map.find(1))).first) {
        return (false);
    }
    if ((*(ft_map.find(1))).first != (*(std_map.find(1))).first) {
        return (false);
    }
    return (true);
}

bool map_bound_method() {
    ft::map<int, char> ft_map;
    std::map<int, char> std_map;
    typedef ft::map<int, char>::iterator ftiter;
    typedef std::map<int, char>::iterator stditer;

    for (int i = 0; i < 15; i++) {
        ft_map[i] = char('a' + i);
        std_map[i] = char('a' + i);
    }

    ftiter ft_iter_lower = ft_map.lower_bound(2);
    stditer std_iter_lower = std_map.lower_bound(2);

    if ((*(ft_iter_lower)).second != (*(std_iter_lower)).second) {
        return (false);
    }

    ftiter ft_iter_upper = ft_map.upper_bound(4);
    stditer std_iter_upper = std_map.upper_bound(4);

    if ((*(ft_iter_upper)).second != (*(std_iter_upper)).second) {
        return (false);
    }

    ftiter ft_iter_lower_small = ft_map.lower_bound(-1);
    stditer std_iter_upper_small = std_map.lower_bound(-1);

    if ((*(ft_iter_lower_small)).second != (*(std_iter_upper_small)).second) {
        return (false);
    }

    return (true);
}

bool map_equal_method() {
    ft::map<int, char> ft_map;
    std::map<int, char> std_map;
    typedef ft::map<int, char>::iterator ftiter;
    typedef std::map<int, char>::iterator stditer;
    typedef ft::pair<ftiter, ftiter> ftiterpair;
    typedef std::pair<stditer, stditer> stditerpair;

    for (int i = 0; i < 15; i++) {
        ft_map[i] = char('a' + i);
        std_map[i] = char('a' + i);
    }

    ftiterpair ft_iter_p = ft_map.equal_range(2);
    stditerpair std_iter_p = std_map.equal_range(2);

    if (((*(ft_iter_p.first)).second != (*(std_iter_p.first)).second)
      || (*(ft_iter_p.second)).second != (*(std_iter_p.second)).second) {
        return (false);
    }

    ftiterpair ft_iter_p_begin = ft_map.equal_range(-42);
    stditerpair std_iter_p_begin = std_map.equal_range(-42);
    if ((ft_iter_p_begin.first != ft_iter_p_begin.second)
      || (ft_iter_p_begin.first != ft_map.begin())
      || (std_iter_p_begin.first != std_iter_p_begin.second)
      || (std_iter_p_begin.first != std_map.begin())) {
        return (false);
    }

    ftiterpair ft_iter_p_end = ft_map.equal_range(42);
    stditerpair std_iter_p_end = std_map.equal_range(42);
    if ((ft_iter_p_end.first != ft_iter_p_end.second)
      || (ft_iter_p_end.first != ft_map.end())
      || (std_iter_p_end.first != std_iter_p_end.second)
      || (std_iter_p_end.first != std_map.end())) {
        return (false);
    }

    return (true);
}

bool map_operator_method() {
    ft::map<int, char> ft_map;
    ft::map<int, char> ft_map_1;
    std::map<int, char> std_map;
    std::map<int, char> std_map_1;

    for (int i = 0; i < 15; i++) {
        ft_map[i] = char('a' + i);
        std_map[i] = char('a' + i);
        ft_map_1[i] = char('a' + i);
        std_map_1[i] = char('a' + i);
    }

    if (!(ft_map == ft_map_1) || !(std_map == std_map_1)) {
        return (false);
    }

    ft_map_1[10] = 'a';
    std_map_1[10] = 'a';
    if ((ft_map == ft_map_1) != (std_map == std_map_1)) {
        return (false);
    }

    if ((ft_map < ft_map_1) != (std_map < std_map_1)) {
        return (false);
    }

    if ((ft_map > ft_map_1) != (std_map > std_map_1)) {
        return (false);
    }

    return (true);
}