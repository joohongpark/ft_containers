#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include <type_traits>
#include <iostream>

#include <enable_if.hpp>
#include <choose_type.hpp>
#include <iterator_traits.hpp>

namespace ft {
    template <class T>
    class map_iterator {
        public:
            typedef typename std::remove_const<T>::type                                                         tree;
            typedef typename tree::node_type::value_type                                                        data;
            typedef typename tree::node_type*                                                                   iterator_type;
            typedef std::bidirectional_iterator_tag                                                             iterator_category;
            typedef typename iterator_traits<data*>::value_type                                                 value_type;
            typedef typename iterator_traits<data*>::difference_type                                            difference_type;
            typedef typename iterator_traits<data*>::pointer                                                    pointer;
            typedef typename ft::choose_type<std::is_const<T>::value, const value_type&, value_type&>::type     reference; // #NOTE map의 iterator / const_iterator 차이점이 이거밖에 없는듯
        private:
            iterator_type iter;
            bool is_end; // #NOTE: 트리 구조에서 실제로 존재하지 않는 end() 이터레이터를 표현하기 위한 플래그
        public:
            map_iterator() : iter(NULL), is_end(true) {};
            map_iterator(const iterator_type& x) : iter(x), is_end(false) {};
            template <class Type> // #NOTE: 이게 있어야 const_iterator까지 커버됨. 왜그런지는 아직 잘 모름
            map_iterator(const map_iterator<Type>& i, typename ft::enable_if<!std::is_const<Type>::value>::type* = 0) : iter(i.base()) {}

            reference operator*() const {
                return (iter->data);
            }
            pointer operator->() const {
                return (&(iter->data));
            }
            map_iterator& operator++() {
                iterator_type iter_next = tree::getnext(iter);
                if (is_end == true) {
                    if (iter_next != NULL) {
                        is_end = false;
                    }
                } else {
                    if (iter_next == NULL) {
                        is_end = true;
                    } else {
                        iter = iter_next;
                    }
                }
                return *this;
            }
            map_iterator operator++(int) {
                map_iterator __t(*this);
                ++(*this);
                return __t;
            }
            map_iterator& operator--() {
                iterator_type iter_prev = tree::getprev(iter);
                if (is_end == true) {
                    if (iter_prev != NULL) {
                        is_end = false;
                    }
                } else {
                    if (iter_prev == NULL) {
                        is_end = true;
                    } else {
                        iter = iter_prev;
                    }
                }
                return *this;
            }
            map_iterator operator--(int) {
                map_iterator __t(*this);
                --(*this);
                return __t;
            }
            iterator_type base() const {
                return (iter);
            }
            bool end_check() const {
                return (is_end);
            }
    };
    template <class T1, class T2>
    bool operator==(const map_iterator<T1>& x, const map_iterator<T2>& y) { return bool((x.base() == y.base()) && (x.end_check() == y.end_check())); }
    template <class T>
    bool operator!=(const map_iterator<T >& x, const map_iterator<T >& y) { return bool((x.base() != y.base()) || (x.end_check() != y.end_check())); }
    template <class T1, class T2>
    bool operator!=(const map_iterator<T1>& x, const map_iterator<T2>& y) { return bool((x.base() != y.base()) || (x.end_check() != y.end_check())); }
}
#endif
