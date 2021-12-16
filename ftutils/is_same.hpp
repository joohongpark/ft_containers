#ifndef IS_SAME_HPP
#define IS_SAME_HPP

#include <integral_constant.hpp>

// from <type_traits>

namespace ft {
    template <class X, class Y> struct is_same       : public ft::false_type {};
    template <class X>          struct is_same<X, X> : public ft::true_type  {};
}
#endif
