#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

// from <type_traits>

namespace ft {
    template <bool, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T> {
        typedef T type;
    };
}

#endif
