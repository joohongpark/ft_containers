#ifndef INTEGRAL_CONSTANT_HPP
#define INTEGRAL_CONSTANT_HPP

// from <type_traits>

namespace ft {
    template <class T, T val>
    struct integral_constant {
        typedef T                   value_type;
        static const T              value = val;
        typedef integral_constant   type;
        operator value_type() {
            return (value);
        }
        value_type operator ()() const {
            return (value);
        }
    };

    typedef integral_constant<bool, true>  true_type;
    typedef integral_constant<bool, false> false_type;
}
#endif
