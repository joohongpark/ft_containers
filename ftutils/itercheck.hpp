#ifndef ITERCHECK_HPP
#define ITERCHECK_HPP

#include <enable_if.hpp>
#include <is_integral.hpp>

#include <type_traits>

namespace ft {
    template <class Iter, class T>
    struct itercheck {
        typedef typename enable_if<
            !is_integral<Iter>::value
            && std::is_convertible<typename Iter::iterator_category, T>::value, Iter>::type type;
    };
}
#endif
