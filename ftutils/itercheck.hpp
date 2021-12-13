#ifndef ITERCHECK_HPP
#define ITERCHECK_HPP

#include <enable_if.hpp>

#include <type_traits>

namespace ft {
    template <class Iter, class T2>
    struct itercheck {
        typedef typename enable_if<std::is_convertible<typename Iter::iterator_category, T2>::value, Iter>::type type;
    };
}
#endif
