#include <iostream>
#include <string>
#include <map>
#include <vector>

int main(void) {
    std::vector<std::pair<int, std::string> > v;
    std::map<int, std::string> std_map;
    std::pair<std::map<int, std::string>::iterator, bool> rtn;

    v.push_back(std::pair<int, std::string>(10, "ten"));
    v.push_back(std::pair<int, std::string>(9, "nine"));

    std_map[1] = "one";
    std_map[2] = "two";
    rtn = std_map.insert(std::pair<int, std::string>(3, "three"));

    std::map<int, std::string>::iterator std_map_iter = std_map.begin();

    while (std_map_iter != std_map.end()) {
        std::cout << std_map_iter->first << " -> " << std_map_iter->second << std::endl;
        std_map_iter++;
    }

    return (0);
}