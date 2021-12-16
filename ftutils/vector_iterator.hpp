#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <iterator_traits.hpp>
#include <enable_if.hpp>
#include <is_const.hpp>
#include <iostream>

namespace ft {
    template <class T>
    class vector_iterator {
        public:
            typedef T                                                           iterator_type;
            typedef typename iterator_traits<iterator_type>::iterator_category  iterator_category;
            typedef typename iterator_traits<iterator_type>::value_type         value_type;
            typedef typename iterator_traits<iterator_type>::difference_type    difference_type;
            typedef typename iterator_traits<iterator_type>::pointer            pointer;
            typedef typename iterator_traits<iterator_type>::reference          reference;
        private:
            iterator_type iter;
        public:
            vector_iterator();
            vector_iterator(const iterator_type& x) : iter(x) {}
            template <class Type>
            vector_iterator(const vector_iterator<Type>& i, typename ft::enable_if<!ft::is_const<Type>::value>::type* = 0) : iter(i.base()) {}

            reference           operator*() const {
                return (*iter);
            }
            pointer             operator->() const {
                return (iter);
            }
            vector_iterator&    operator++() {
                ++iter;
                return (*this);
            }
            vector_iterator     operator++(int) {
                vector_iterator tmp(*this);
                ++(*this);
                return (tmp);
            }
            vector_iterator&    operator--() {
                --iter;
                return (*this);
            }
            vector_iterator     operator--(int) {
                vector_iterator tmp(*this);
                --(*this);
                return (tmp);
            }
            vector_iterator     operator+ (difference_type n) const {
                vector_iterator tmp(*this);
                tmp += n;
                std::cout << "DEBUG IN " << __func__ << "] #2 : " << reinterpret_cast<difference_type>(this->base()) << ", " << reinterpret_cast<difference_type>(tmp.base()) << std::endl;
                return (tmp);
            }
            vector_iterator&    operator+=(difference_type n) {
                iter += n;
                return (*this);
            }
            vector_iterator     operator- (difference_type n) const {
                return (*this + (-n));
            }
            vector_iterator&    operator-=(difference_type n) {
                *this += -n;
                return (*this);
            }
            reference           operator[](difference_type n) const {
                return (iter[n]);
            }
            iterator_type       base() const {
                return (iter);
            }
    };
}

namespace ft {
    template <class T1, class T2>
    bool operator==(const vector_iterator<T1>& x, const vector_iterator<T2>& y) { return bool(x.base() == y.base()); }
    template <class T>
    bool operator!=(const vector_iterator<T >& x, const vector_iterator<T >& y) { return bool(x.base() != y.base()); }
    template <class T1, class T2>
    bool operator!=(const vector_iterator<T1>& x, const vector_iterator<T2>& y) { return bool(x.base() != y.base()); }
    template <class T>
    bool operator< (const vector_iterator<T >& x, const vector_iterator<T >& y) { return bool(x.base() <  y.base()); }
    template <class T1, class T2>
    bool operator< (const vector_iterator<T1>& x, const vector_iterator<T2>& y) { return bool(x.base() <  y.base()); }
    template <class T>
    bool operator> (const vector_iterator<T >& x, const vector_iterator<T >& y) { return bool(x.base() >  y.base()); }
    template <class T1, class T2>
    bool operator> (const vector_iterator<T1>& x, const vector_iterator<T2>& y) { return bool(x.base() >  y.base()); }
    template <class T>
    bool operator>=(const vector_iterator<T >& x, const vector_iterator<T >& y) { return bool(x.base() >= y.base()); }
    template <class T1, class T2>
    bool operator>=(const vector_iterator<T1>& x, const vector_iterator<T2>& y) { return bool(x.base() >= y.base()); }
    template <class T>
    bool operator<=(const vector_iterator<T >& x, const vector_iterator<T >& y) { return bool(x.base() <= y.base()); }
    template <class T1, class T2>
    bool operator<=(const vector_iterator<T1>& x, const vector_iterator<T2>& y) { return bool(x.base() <= y.base()); }
    template <class T1, class T2>
    typename vector_iterator<T1>::difference_type operator- (const vector_iterator<T1>& x, const vector_iterator<T2>& y) {
        std::cout << "DEBUG IN " << __func__ << "] : " << reinterpret_cast<typename vector_iterator<T1>::difference_type>(x.base()) << " - " << reinterpret_cast<typename vector_iterator<T1>::difference_type>(y.base()) << std::endl;
        std::cout << "DEBUG IN " << __func__ << "] #1 : " << reinterpret_cast<typename vector_iterator<T1>::difference_type>(x.base() - y.base()) << std::endl;
        return static_cast<typename vector_iterator<T1>::difference_type>(x.base() - y.base());
    }
    template <class T1, class T2>
    typename vector_iterator<T1>::difference_type operator+ (const vector_iterator<T1>& x, const vector_iterator<T2>& y) {
        return static_cast<typename vector_iterator<T1>::difference_type>(x.base() + y.base());
    }
}
#endif