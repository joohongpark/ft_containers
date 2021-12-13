#ifndef CHOOSE_TYPE_HPP
#define CHOOSE_TYPE_HPP

namespace ft {
    template <bool, class T1, class T2>
    struct choose_type {};

    template <class T1, class T2>
    struct choose_type<true, T1, T2> {
        typedef T1 type;
    };

    template <class T1, class T2>
    struct choose_type<false, T1, T2> {
        typedef T2 type;
    };
}

#endif
