#ifndef MAP_HPP
#define MAP_HPP

#include <memory>

#include "pair.hpp"

namespace ft {
    template <
            class Key, class T,
            class Compare = std::less<Key>, // FIXME
            class Allocator = std::allocator<ft::pair<const Key, T>>>
    class map {}
}

#endif
