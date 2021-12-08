#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "type_traits.hpp"

namespace ft {
    template <class T>
    class map_iterator {
        public:
            typedef typename remove_const<T>::type                                                      tree;
            typedef typename tree::node_type::value_type                                                data;
            typedef typename tree::node_type*                                                           iterator_type;
            typedef bidirectional_iterator_tag                                                          iterator_category;
            typedef typename iterator_traits<data*>::value_type                                         value_type;
            typedef typename iterator_traits<data*>::difference_type                                    difference_type;
            typedef typename iterator_traits<data*>::pointer                                            pointer;
            typedef typename choose_type<is_const<T>::value, const value_type&, value_type&>::type      reference; // #NOTE map의 iterator / const_iterator 차이점이 이거밖에 없는듯
        private:
            iterator_type iter;
        public:
            map_iterator() : iter(NULL) {};
            map_iterator(const iterator_type& x) : iter(x) {}
            template <class Type> // #NOTE: 이게 있어야 const_iterator까지 커버됨. 왜그런지는 아직 잘 모름
            map_iterator(const map_iterator<Type>& i, typename enable_if<!is_const<Type>::value>::type* = 0) : iter(i.base()) {}

            reference operator*() const {
                return (iter->data);
            }
            pointer operator->() const {
                return (&(iter->data));
            }
            map_iterator& operator++() {
                iter = tree::getnext(iter);
                return *this;
            }
            map_iterator operator++(int) {
                map_iterator __t(*this);
                ++(*this);
                return __t;
            }
            map_iterator& operator--() {
                iter = tree::getprev(iter);
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
    };
    template <class T1, class T2>
    bool operator==(const map_iterator<T1>& x, const map_iterator<T2>& y) { return bool(x.base() == y.base()); }
    template <class T>
    bool operator!=(const map_iterator<T >& x, const map_iterator<T >& y) { return bool(x.base() != y.base()); }
    template <class T1, class T2>
    bool operator!=(const map_iterator<T1>& x, const map_iterator<T2>& y) { return bool(x.base() != y.base()); }
}
#endif
