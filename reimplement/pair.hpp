#ifndef PAIR_HPP
#define PAIR_HPP

// from <utility>

namespace ft {
    template <class T1, class T2>
    struct pair {
        typedef T1  first_type;
        typedef T2  second_type;

        first_type  first;
        second_type second;

        //constructor
        pair() : first(), second() {};
        explicit pair(const first_type& a, const second_type& b) : first(a), second(b) {}
        template<class U, class V>
        pair (const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

        //operator=
        pair& operator=(const pair& pr) {
            if (this != &pr) {
                this->first = pr.first;
                this->second = pr.second;
            }
            return (*this);
        }
    };
}

namespace ft {
    template <class T1, class T2>
    bool operator== (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
        return ((lhs.first == rhs.first) && (lhs.second == rhs.second));
    }

    template <class T1, class T2>
    bool operator!= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
        return (!(lhs == rhs));
    }

    template <class T1, class T2>
    bool operator<  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
        return ((lhs.first < rhs.first) || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
    }

    template <class T1, class T2>
    bool operator<= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
        return (!(rhs < lhs));
    }

    template <class T1, class T2>
    bool operator>  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
        return (rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
        return (!(lhs < rhs));
    }
}

#endif
