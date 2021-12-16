#ifndef IS_BIDIRECTIONAL_ITERATOR_HPP
#define IS_BIDIRECTIONAL_ITERATOR_HPP

#include <iterator>

#include <void_or_none.hpp>
#include <enable_if.hpp>
#include <is_iterator.hpp>
#include <is_same.hpp>

namespace ft {
    template<typename T, typename = void>   struct is_bidirectional_iterator { static const bool value = false; };
    template<typename T>                    struct is_bidirectional_iterator<
        T,
        typename enable_if<
            is_iterator<T>::value &&
            (
                !is_same<typename T::iterator_category, std::input_iterator_tag>::value &&
                !is_same<typename T::iterator_category, std::forward_iterator_tag>::value
            ) &&
            (
                is_same<typename T::iterator_category, std::bidirectional_iterator_tag>::value ||
                is_same<typename T::iterator_category, std::random_access_iterator_tag>::value
            )
        >::type
    > { static const bool value = true; };
}
#endif
