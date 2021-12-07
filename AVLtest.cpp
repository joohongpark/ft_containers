#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>

#include "AVLTree.hpp"

//typedef __map_value_compare<key_type, __value_type, key_compare> __vc;

/*
template <class Key, class Value>
struct pair_type {
    typedef Key                                     key_type;
    typedef Value                                   mapped_type;
    typedef std::pair<key_type, mapped_type>  value_type;
    value_type                                      val;
};
*/

template <class Key, class Value>
std::ostream &operator<<(std::ostream &out, const std::pair<int, std::string> &pair) {
    out << "[key : " << pair.first << ", value : " << pair.second << "]";
    return (out);
}

// 비교 연산자를 확장하여 새로운 연산자를 만듬
template <class Pair, class Compare>
struct pair_compare : public Compare {
    bool operator()(const Pair& a, const Pair& b) const {
        return (static_cast<const Compare&>(*this)(a.first, b.first));
    }
};

int main() {
    typedef std::pair<int, std::string>                         Type;
    typedef pair_compare<Type, std::less<int> >                 Comp;
    
    AVLTree<Type, Comp> t;
    for (int i = 0; i < 1000; i++) {
        Type p;
        p.first = i;
        p.second = "문자열";
        t.insert(p);
    }
    Type* min = t.getmin();
    std::cout << "min : " << min->first << " (" << min->second << ")" << std::endl;
    Type* max = t.getmax();
    std::cout << "max : " << max->first << " (" << min->second << ")" << std::endl;
    Type target;
    target.first = 10;
    Type *f = t.find(target);
    std::cout << "find : " << f->first << " (" << f->second << ")" << std::endl;
    for (int i = 0; i < 998; i++) {
        Type p;
        p.first = i;
        t.delval(p);
    }
    t.__debug();
    return (0);
}