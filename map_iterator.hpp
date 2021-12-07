#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "iterator_traits.hpp"

/**
 * Iter::_NodeTypes
 * Iter::__pointer_traits
 **/

namespace ft {
    template <class Iter>
    class map_iterator {
            typedef typename Iter::_NodeTypes                   _NodeTypes;
            typedef typename Iter::__pointer_traits             __pointer_traits;
            Iter iter;

        public:
            typedef bidirectional_iterator_tag                           iterator_category;
            typedef typename _NodeTypes::__map_value_type                value_type;
            typedef typename Iter::difference_type                       difference_type;
            typedef value_type&                                          reference;
            typedef typename _NodeTypes::__map_value_type_pointer        pointer;

            map_iterator() {}
            map_iterator(Iter i) : iter(i) {}

            reference operator*() const {
                return iter->__get_value();
            }
            pointer operator->() const {
                //return pointer_traits<pointer>::pointer_to(iter->__get_value());
                return &(iter->__get_value());
            }
            map_iterator& operator++() {
                ++iter;
                return *this;
            }
            map_iterator operator++(int) {
                map_iterator __t(*this);
                ++(*this);
                return __t;
            }
            map_iterator& operator--() {
                --iter;
                return *this;
            }
            map_iterator operator--(int) {
                map_iterator __t(*this);
                --(*this);
                return __t;
            }

            friend bool operator==(const map_iterator& __x, const map_iterator& __y) {
                return __x.iter == __y.iter;
            }
            friend bool operator!=(const map_iterator& __x, const map_iterator& __y) {
                return __x.iter != __y.iter;
            }

            template <class, class, class, class> friend class map;
            template <class, class, class, class> friend class multimap;
            template <class> friend class map_const_iterator;
    };

    template <class Iter>
    class map_const_iterator {
            typedef typename Iter::_NodeTypes                   _NodeTypes;
            typedef typename Iter::__pointer_traits             __pointer_traits;
            Iter iter;

        public:
            typedef bidirectional_iterator_tag                           iterator_category;
            typedef typename _NodeTypes::__map_value_type                value_type;
            typedef typename Iter::difference_type                       difference_type;
            typedef const value_type&                                    reference;
            typedef typename _NodeTypes::__const_map_value_type_pointer  pointer;

            
            map_const_iterator() {}
            map_const_iterator(Iter __i) : iter(__i) {}
            map_const_iterator(__map_iterator<typename Iter::__non_const_iterator> __i) : iter(__i.iter) {}

            reference operator*() const {return iter->__get_value();}
            pointer operator->() const {return pointer_traits<pointer>::pointer_to(iter->__get_value());}
            map_const_iterator& operator++() {++iter; return *this;}
            map_const_iterator operator++(int) {
                map_const_iterator __t(*this);
                ++(*this);
                return __t;
            }

            
            map_const_iterator& operator--() {--iter; return *this;}
            map_const_iterator operator--(int) {
                map_const_iterator __t(*this);
                --(*this);
                return __t;
            }

            friend 
            bool operator==(const map_const_iterator& __x, const map_const_iterator& __y)
                {return __x.iter == __y.iter;}
            friend 
            bool operator!=(const map_const_iterator& __x, const map_const_iterator& __y)
                {return __x.iter != __y.iter;}

            template <class, class, class, class> friend class map;
            template <class, class, class, class> friend class multimap;
            template <class, class, class> friend class __tree_const_iterator;
    };
}

#endif
