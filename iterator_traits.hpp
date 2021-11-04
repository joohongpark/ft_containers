#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include "type_traits.hpp"

namespace ft {
    struct input_iterator_tag         {};
    struct output_iterator_tag        {};
    struct forward_iterator_tag       : public input_iterator_tag         {};
    struct bidirectional_iterator_tag : public forward_iterator_tag       {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template <class Iterator>
    struct iterator_traits {
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    template <class T>
    struct iterator_traits<T*> {
        typedef ptrdiff_t                  difference_type;
        typedef T                          value_type;
        typedef T*                         pointer;
        typedef T&                         reference;
        typedef random_access_iterator_tag iterator_category;
    };

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
                    typename void_or_none<typename Type::iterator_category>::type* = 0,
                    typename void_or_none<typename Type::difference_type>::type* = 0,
                    typename void_or_none<typename Type::value_type>::type* = 0,
                    typename void_or_none<typename Type::reference>::type* = 0,
                    typename void_or_none<typename Type::pointer>::type* = 0
                );
        public:
            static const bool value = sizeof(fun<T>(0,0,0,0,0)) == 1;
    };

    template<typename T, typename = void>   struct is_input_iterator { static const bool value = false; };
    template<typename T>                    struct is_input_iterator<
        T,
        typename enable_if<
            is_iterator<T>::value &&
            (
                is_same<typename T::iterator_category, input_iterator_tag>::value ||
                is_same<typename T::iterator_category, forward_iterator_tag>::value ||
                is_same<typename T::iterator_category, bidirectional_iterator_tag>::value ||
                is_same<typename T::iterator_category, random_access_iterator_tag>::value
            )
        >::type
    > { static const bool value = true; };

    template<typename T, typename = void>   struct is_forward_iterator { static const bool value = false; };
    template<typename T>                    struct is_forward_iterator<
        T,
        typename enable_if<
            is_iterator<T>::value &&
            (
                !is_same<typename T::iterator_category, input_iterator_tag>::value
            ) &&
            (
                is_same<typename T::iterator_category, forward_iterator_tag>::value ||
                is_same<typename T::iterator_category, bidirectional_iterator_tag>::value ||
                is_same<typename T::iterator_category, random_access_iterator_tag>::value
            )
        >::type
    > { static const bool value = true; };

    template<typename T, typename = void>   struct is_bidirectional_iterator { static const bool value = false; };
    template<typename T>                    struct is_bidirectional_iterator<
        T,
        typename enable_if<
            is_iterator<T>::value &&
            (
                !is_same<typename T::iterator_category, input_iterator_tag>::value &&
                !is_same<typename T::iterator_category, forward_iterator_tag>::value
            ) &&
            (
                is_same<typename T::iterator_category, bidirectional_iterator_tag>::value ||
                is_same<typename T::iterator_category, random_access_iterator_tag>::value
            )
        >::type
    > { static const bool value = true; };

    template<typename T, typename = void>   struct is_random_access_iterator { static const bool value = false; };
    template<typename T>                    struct is_random_access_iterator<
        T,
        typename enable_if<
            is_iterator<T>::value &&
            (
                !is_same<typename T::iterator_category, input_iterator_tag>::value &&
                !is_same<typename T::iterator_category, forward_iterator_tag>::value &&
                !is_same<typename T::iterator_category, bidirectional_iterator_tag>::value
            ) &&
            (
                is_same<typename T::iterator_category, random_access_iterator_tag>::value
            )
        >::type
    > { static const bool value = true; };

}
#endif