#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include <iostream>

#include <enable_if.hpp>
#include <choose_type.hpp>
#include <iterator_traits.hpp>
#include <is_const.hpp>
#include <remove_const.hpp>

namespace ft {
    template <class T>
    class map_iterator {
        public:
            typedef typename ft::remove_const<T>::type                                                          tree;
            typedef typename tree::node_type::value_type                                                        data;
            typedef typename tree::node_type*                                                                   iterator_type;
            typedef std::bidirectional_iterator_tag                                                             iterator_category;
            typedef typename ft::choose_type<ft::is_const<T>::value, const data, data>::type                    value_type;
            typedef typename iterator_traits<data*>::difference_type                                            difference_type;
            typedef typename ft::choose_type<ft::is_const<T>::value, const data*, data*>::type                  pointer;
            typedef typename ft::choose_type<ft::is_const<T>::value, const value_type&, value_type&>::type      reference;
        private:
            iterator_type iter;
            bool is_end;
        public:
            map_iterator() : iter(NULL), is_end(true) {};
            map_iterator(const iterator_type& x) : iter(x), is_end(false) {
                if (x == NULL) {
                    is_end = true;
                }
            };
            template <class Type>
            map_iterator(const map_iterator<Type>& i, typename ft::enable_if<!ft::is_const<Type>::value>::type* = 0) : iter(i.base()), is_end(i.end_check()) {}

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
}

namespace ft {
    template <class T1, class T2>
    bool operator==(const map_iterator<T1>& x, const map_iterator<T2>& y) {
        if (x.end_check() == true && y.end_check() == true) {
            return (true);
        }
        return bool((x.base() == y.base()) && (x.end_check() == y.end_check()));
    }
    template <class T>
    bool operator!=(const map_iterator<T >& x, const map_iterator<T >& y) {
        if (x.end_check() == true && y.end_check() == true) {
            return (false);
        }
        return bool((x.base() != y.base()) || (x.end_check() != y.end_check()));
    }
    template <class T1, class T2>
    bool operator!=(const map_iterator<T1>& x, const map_iterator<T2>& y) {
        if (x.end_check() == true && y.end_check() == true) {
            return (false);
        }
        return bool((x.base() != y.base()) || (x.end_check() != y.end_check()));
    }
}
#endif
