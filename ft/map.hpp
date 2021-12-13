#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <functional>

#include <pair.hpp>
#include <AVLTree.hpp>
#include <map_iterator.hpp>
#include <reverse_iterator.hpp>
#include <equal.hpp>
#include <lexicographical_compare.hpp>

namespace ft {
    template <
        class Key, class T,
        class Compare = std::less<Key>,
        class Allocator = std::allocator< ft::pair<const Key, T> > >
    class map {
        public:
            typedef Key                                             key_type;
            typedef T                                               mapped_type;
            typedef ft::pair<const key_type, mapped_type>           value_type;
            typedef Compare                                         key_compare;
            typedef Allocator                                       allocator_type;
            typedef typename allocator_type::reference              reference;
            typedef typename allocator_type::const_reference        const_reference;
            typedef typename allocator_type::pointer                pointer;
            typedef typename allocator_type::const_pointer          const_pointer;
            typedef typename allocator_type::size_type              size_type;
            typedef typename allocator_type::difference_type        difference_type;
            class value_compare : public std::binary_function<value_type, value_type, bool> {
                protected:
                    key_compare comp;
                public:
                    value_compare() : comp() {};
                    bool operator()(const value_type& x, const value_type& y) const {
                        return (comp(x.first, y.first));
                    }
            };
            typedef AVLTree<value_type, value_compare, Allocator>   tree_type;
            typedef ft::map_iterator<tree_type>                     iterator;
            typedef ft::map_iterator<const tree_type>               const_iterator;
            typedef ft::reverse_iterator<iterator>                  reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;
        private:
            tree_type                                               _tree;
            size_type                                               _size;
            allocator_type                                          _alloc;
            key_compare                                             _comp;

        public:
            void debug() {
                _tree.__debug();
            }
            // construct/copy/destroy:
            explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
            template <class InputIterator>
            map(InputIterator first, InputIterator last,
                const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
            map(const map& m);
            ~map();
            // operator overloading:
            map&                                operator=(const map& m);
            mapped_type&                        operator[](const key_type& k);

            // capacity:
            size_type                           size() const;
            size_type                           max_size() const;
            bool                                empty() const;

            // modifiers:
            pair<iterator, bool>                insert(const value_type& v);
            iterator                            insert(const_iterator position, const value_type& v);
            template <class InputIterator>
            void                                insert(InputIterator first, typename enable_if<std::is_convertible<typename InputIterator::iterator_category, std::input_iterator_tag>::value, InputIterator>::type last);
            iterator                            erase(const_iterator position);
            size_type                           erase(const key_type& k);
            iterator                            erase(const_iterator first, const_iterator last);
            void                                clear();

            // map operations:
            size_type                           count(const key_type& k) const;
            iterator                            find(const key_type& k);
            const_iterator                      find(const key_type& k) const;
            iterator                            lower_bound(const key_type& k);
            const_iterator                      lower_bound(const key_type& k) const;
            iterator                            upper_bound(const key_type& k);
            const_iterator                      upper_bound(const key_type& k) const;
            pair<iterator,iterator>             equal_range(const key_type& k);
            pair<const_iterator,const_iterator> equal_range(const key_type& k) const;

            // iterators:
            iterator                begin();
            const_iterator          begin() const;
            iterator                end();
            const_iterator          end() const;
            reverse_iterator        rbegin();
            const_reverse_iterator  rbegin() const;
            reverse_iterator        rend();
            const_reverse_iterator  rend() const;

            // observers:
            key_compare             key_comp()      const;
            value_compare           value_comp()    const;
            allocator_type          get_allocator() const;
            void                    swap(map& m);

    };
    template <class Key, class T, class Compare, class Allocator>
    bool operator==(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y) {
        if (x.size() != y.size()) {
            return (false);
        }
        return (ft::equal(x.begin(), x.end(), y.begin()));
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator< (const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y) {
        return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator!=(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y) {
        return (!(x == y));
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator> (const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y) {
        return (y < x);
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator>=(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y) {
        return (!(x < y));
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator<=(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y) {
        return (!(y < x));
    }

    template <class Key, class T, class Compare, class Allocator>
    void swap(map<Key, T, Compare, Allocator>& x, map<Key, T, Compare, Allocator>& y) {
        x.swap(y);
    }
}

namespace ft {

    // construct/copy/destroy:
    template <class Key, class T, class Compare, class Allocator>
    map<Key, T, Compare, Allocator>::map(const key_compare& comp, const allocator_type& alloc) : _size(0), _alloc(alloc), _comp(comp) {}

    template <class Key, class T, class Compare, class Allocator>
    template <class InputIterator>
    map<Key, T, Compare, Allocator>::map(InputIterator first, InputIterator last, const key_compare& comp, const allocator_type& alloc) : _size(0), _alloc(alloc), _comp(comp) {
        while (first != last) {
            _size++;
            _tree.insert(*first);
            first++;
        }
    }

    template <class Key, class T, class Compare, class Allocator>
    map<Key, T, Compare, Allocator>::map(const map& m) {
        if (this != &m) {
            *this = m;
        }
    }

    template <class Key, class T, class Compare, class Allocator>
    map<Key, T, Compare, Allocator>::~map() {}

    // operator overloading:
    template <class Key, class T, class Compare, class Allocator>
    map<Key, T, Compare, Allocator>& map<Key, T, Compare, Allocator>::operator=(const map& m) {
        if (this != &m) {
            this->_tree = m._tree;
            this->_size = m._size;
            this->_alloc = m._alloc;
            this->_comp = m._comp;
        }
        return (*this);
    }

    template <class Key, class T, class Compare, class Allocator>
    T& map<Key, T, Compare, Allocator>::operator[](const key_type& k) {
        value_type target(k, mapped_type());
        value_type *find = _tree.find(target);
        if (find == NULL) {
            _size++;
            find = _tree.insert(target);
        }
        return (find->second);
    }

    // capacity:
    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::size_type map<Key, T, Compare, Allocator>::size() const {
        return (_size);
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::size_type map<Key, T, Compare, Allocator>::max_size() const {
        return (_tree.max_size());
    }

    template <class Key, class T, class Compare, class Allocator>
    bool map<Key, T, Compare, Allocator>::empty() const {
        return (_size == 0);
    }

    // modifiers:
    template <class Key, class T, class Compare, class Allocator>
    pair<typename map<Key, T, Compare, Allocator>::iterator, bool> map<Key, T, Compare, Allocator>::insert(const value_type& v) {
        pair<iterator, bool> rtn;
        if (_tree.have(v)) {
            rtn.second = false;
        } else {
            _tree.insert(v);
            _size++;
            rtn.second = true;
        }
        rtn.first = iterator(_tree.getnode(v));
        return (rtn);
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::insert(const_iterator position, const value_type& v) {
        (void) position;
        value_type* new_val = _tree.insert(v);
        if (new_val != NULL) {
            _size++;
        }
        return (iterator(_tree.getnode(v)));
    }

    template <class Key, class T, class Compare, class Allocator>
    template <class InputIterator>
    void map<Key, T, Compare, Allocator>::insert(InputIterator first, typename enable_if<std::is_convertible<typename InputIterator::iterator_category, std::input_iterator_tag>::value, InputIterator>::type last) {
        while (first != last) {
            _size++;
            _tree.insert(*first);
            first++;
        }
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::erase(const_iterator position) {
        value_type v(*position);
        iterator rtn(_tree.getnode(v));
        rtn++;
        if (_tree.delval(v) == true) {
            _size--;
        }
        return (rtn);
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::size_type map<Key, T, Compare, Allocator>::erase(const key_type& k) {
        value_type target(k, mapped_type());
        if (_tree.delval(target) == true) {
            _size--;
        }
        return (_size);
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::erase(const_iterator first, const_iterator last) {
        while (first != last) {
            if (_tree.delval(*first) == true) {
                _size--;
            }
            first++;
        }
    }

    template <class Key, class T, class Compare, class Allocator>
    void map<Key, T, Compare, Allocator>::clear() {
        _size = 0;
        _tree.clear();
    }

    // map operations:
    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::size_type map<Key, T, Compare, Allocator>::count(const key_type& k) const {
        value_type target(k, mapped_type());
        return (size_type(_tree.have(target)));
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::find(const key_type& k) {
        value_type target(k, mapped_type());
        if (_tree.have(target)) {
            return (iterator(_tree.getnode(target)));
        } else {
            return (++iterator(_tree.end()));
        }
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::find(const key_type& k) const {
        value_type target(k, mapped_type());
        if (_tree.have(target)) {
            return (const_iterator(_tree.getnode(target)));
        } else {
            return (++const_iterator(_tree.end()));
        }
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::lower_bound(const key_type& k) {
        typename tree_type::node_type* node = _tree.begin();
        typename tree_type::node_type* node_end = _tree.end();
        while (true) {
            if (_comp(node->data.first, k) == false) {
                return (iterator(node));
            }
            if (node == node_end) {
                break;
            } else {
                node = tree_type::getnext(node);
            }
        }

        return (++iterator(node));
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::lower_bound(const key_type& k) const {
        typename tree_type::node_type* node = _tree.begin();
        typename tree_type::node_type* node_end = _tree.end();
        while (true) {
            if (_comp(node->data.first, k) == false) {
                return (const_iterator(node));
            }
            if (node == node_end) {
                break;
            } else {
                node = tree_type::getnext(node);
            }
        }
        return (++const_iterator(node));
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::upper_bound(const key_type& k) {
        typename tree_type::node_type* node = _tree.begin();
        typename tree_type::node_type* node_end = _tree.end();
        while (true) {
            if (_comp(k, node->data.first) == true) {
                return (iterator(node));
            }
            if (node == node_end) {
                break;
            } else {
                node = tree_type::getnext(node);
            }
        }
        return (++iterator(node));
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::upper_bound(const key_type& k) const {
        typename tree_type::node_type* node = _tree.begin();
        typename tree_type::node_type* node_end = _tree.end();
        while (true) {
            if (_comp(k, node->data.first) == true) {
                return (iterator(node));
            }
            if (node == node_end) {
                break;
            } else {
                node = tree_type::getnext(node);
            }
        }
        return (++iterator(node));
    }

    template <class Key, class T, class Compare, class Allocator>
    pair<
        typename map<Key, T, Compare, Allocator>::iterator,
        typename map<Key, T, Compare, Allocator>::iterator
    > map<Key, T, Compare, Allocator>::equal_range(const key_type& k) {
        value_type target(k, mapped_type());
        if (_tree.have(target)) {
            typename tree_type::node_type* node = _tree.getnode(target);
            return (pair<iterator, iterator>(iterator(node), ++iterator(node)));
        } else {
            typename tree_type::node_type* node = _tree.end();
            if ((node == NULL) || _comp(node->data.first, k) == true) {
                return (pair<iterator, iterator>(++iterator(node), ++iterator(node)));
            } else {
                return (pair<iterator, iterator>(iterator(_tree.begin()), iterator(_tree.begin())));
            }
        }
    }

    template <class Key, class T, class Compare, class Allocator>
    pair<
        typename map<Key, T, Compare, Allocator>::const_iterator,
        typename map<Key, T, Compare, Allocator>::const_iterator
    > map<Key, T, Compare, Allocator>::equal_range(const key_type& k) const {
        value_type target(k, mapped_type());
        if (_tree.have(target)) {
            typename tree_type::node_type* node = _tree.getnode(target);
            return (pair<const_iterator, const_iterator>(iterator(node), ++iterator(node)));
        } else {
            typename tree_type::node_type* node = _tree.end();
            if ((node == NULL) || _comp(node->data.first, k) == true) {
                return (pair<const_iterator, const_iterator>(++const_iterator(node), ++const_iterator(node)));
            } else {
                return (pair<const_iterator, const_iterator>(const_iterator(_tree.begin()), const_iterator(_tree.begin())));
            }
        }
    }

    // iterators:
    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::begin() {
        return (iterator(_tree.begin()));
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::begin() const {
        return (const_iterator(_tree.cbegin()));
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::end() {
        return (++iterator(_tree.end()));
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::end() const {
        return (++const_iterator(_tree.cend()));
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::reverse_iterator map<Key, T, Compare, Allocator>::rbegin() {
        return (reverse_iterator(end()));
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::const_reverse_iterator map<Key, T, Compare, Allocator>::rbegin() const {
        return (const_reverse_iterator(end()));
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::reverse_iterator map<Key, T, Compare, Allocator>::rend() {
        return (reverse_iterator(begin()));
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::const_reverse_iterator map<Key, T, Compare, Allocator>::rend() const {
        return (const_reverse_iterator(begin()));
    }

    // observers:
    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::key_compare map<Key, T, Compare, Allocator>::key_comp() const {
        return (this->_comp);
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::value_compare map<Key, T, Compare, Allocator>::value_comp() const {
        return (value_compare());
    }

    template <class Key, class T, class Compare, class Allocator>
    typename map<Key, T, Compare, Allocator>::allocator_type map<Key, T, Compare, Allocator>::get_allocator() const {
        return (this->_alloc);
    }

    template <class Key, class T, class Compare, class Allocator>
    void map<Key, T, Compare, Allocator>::swap(map& m) {
        tree_type       tmp_tree = m._tree;
        size_type       tmp_size = m._size;
        allocator_type  tmp_alloc = m._alloc;
        key_compare     tmp_comp = m._comp;
        m._tree = this->_tree;
        m._size = this->_size;
        m._alloc = this->_alloc;
        m._comp = this->_comp;
        this->_tree = tmp_tree;
        this->_size = tmp_size;
        this->_alloc = tmp_alloc;
        this->_comp = tmp_comp;
    }
}
#endif
