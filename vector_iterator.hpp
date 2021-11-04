#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "type_traits.hpp"

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
            template <class Type> // NOTE: 이터레이터 클래스에는 복사 생성자가 들어가야 하며 인수는 상수형 타입이 들어가면 안됨 (왜 그런지 아직 모름)
            vector_iterator(const vector_iterator<Type>& i, typename enable_if<!is_const<Type>::value>::type* = 0) : iter(i.base()) {}
            //vector_iterator(const vector_iterator<Type>& i, typename enable_if<std::is_convertible<_Up, iterator_type>::value>::type* = 0) : iter(i.base()) {}

            reference           operator*() const {
                return (*iter);
            }
            pointer             operator->() const {
                //return (pointer)_VSTD::addressof(*__i);
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

            // TODO: 누락된 연산자 및 함수 추가 (조치 필요)
            template <class T1, class T2> friend
            bool operator==(const vector_iterator<T1>&, const vector_iterator<T2>&);
            template <class T1, class T2> friend
            bool operator<(const vector_iterator<T1>&, const vector_iterator<T2>&);
            template <class T1, class T2> friend
            bool operator!=(const vector_iterator<T1>&, const vector_iterator<T2>&);
            template <class T1, class T2> friend
            bool operator>(const vector_iterator<T1>&, const vector_iterator<T2>&);
            template <class T1, class T2> friend
            bool operator>=(const vector_iterator<T1>&, const vector_iterator<T2>&);
            template <class T1, class T2> friend
            bool operator<=(const vector_iterator<T1>&, const vector_iterator<T2>&);

            template <class T1, class T2> friend
            typename vector_iterator<T1>::difference_type operator-(const vector_iterator<T1>& x, const vector_iterator<T2>& y) {
                return (x.base() - y.base());
            }
            template <class T1> friend
            vector_iterator<T1> operator+(typename vector_iterator<T1>::difference_type x, vector_iterator<T1> y) {
                x += y;
                return (x);
            }
/*
            template <class _Up> friend class vector_iterator;
            template <class _CharT, class _Traits, class _Alloc> friend class basic_string;
            template <class _Tp, class _Alloc> friend class vector;
            template <class _Tp, size_t> friend class span;
            template <class _Ip, class _Op> friend _Op copy(_Ip, _Ip, _Op);
            template <class _B1, class _B2> friend _B2 copy_backward(_B1, _B1, _B2);
            template <class _Ip, class _Op> friend _Op move(_Ip, _Ip, _Op);
            template <class _B1, class _B2> friend _B2 move_backward(_B1, _B1, _B2);
*/
    };
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
}
#endif