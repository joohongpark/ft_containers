#include <iostream>
#include <string>
#include <map>

int main(void) {
    std::map<int, std::string> std_map;

    std_map[1] = "one";
    std_map[2] = "two";

    std::map<int, std::string>::iterator std_map_iter = std_map.begin();

    while (std_map_iter != std_map.end()) {
        std::cout << std_map_iter->first << " -> " << std_map_iter->second << std::endl;
        std_map_iter++;
    }

    return (0);
}