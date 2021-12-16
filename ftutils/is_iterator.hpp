#ifndef IS_ITERATOR_HPP
#define IS_ITERATOR_HPP

#include <void_or_none.hpp>
#include <enable_if.hpp>
#include <is_integral.hpp>

// from <type_traits>

namespace ft {
    template <class T>
    struct is_iterator {
        private:
            typedef struct {
                char dummy[2];
            } big;
            typedef char small;
            template <class Type>
            static big fun(...);
            template <class Type>
            static small fun(
                    typename enable_if<!is_integral<Type>::value>::type* = 0,
                    typename void_or_none<typename Type::iterator_category>::type* = 0,
                    typename void_or_none<typename Type::difference_type>::type* = 0,
                    typename void_or_none<typename Type::value_type>::type* = 0,
                    typename void_or_none<typename Type::reference>::type* = 0,
                    typename void_or_none<typename Type::pointer>::type* = 0
                );
        public:
            static const bool value = sizeof(fun<T>(0,0,0,0,0,0)) == 1;
    };
}
#endif
