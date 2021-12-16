#ifndef IS_CONST_HPP
#define IS_CONST_HPP

#include <integral_constant.hpp>

// from <type_traits>

namespace ft {
    template <class T>   struct is_const                               : public ft::false_type {};
    template <class T>   struct is_const<T const>                      : public ft::true_type {};
}
#endif
