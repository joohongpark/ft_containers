#ifndef MAP_HPP
#define MAP_HPP

#include <memory>

#include "pair.hpp"
#include "functional.hpp"

namespace ft {
    template <
        class Key, class T,
        class Compare = ft::less<Key>,
        class Allocator = std::allocator< ft::pair<const Key, T> > >
    class map {
        public:
            typedef Key                                      key_type;
            typedef T                                        mapped_type;
            typedef pair<const key_type, mapped_type>        value_type;
            typedef Compare                                  key_compare;
            typedef Allocator                                allocator_type;
            typedef typename allocator_type::reference       reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer         pointer;
            typedef typename allocator_type::const_pointer   const_pointer;
            typedef typename allocator_type::size_type       size_type;
            typedef typename allocator_type::difference_type difference_type;
/*
            typedef implementation-defined                   iterator;
            typedef implementation-defined                   const_iterator;
            typedef std::reverse_iterator<iterator>          reverse_iterator;
            typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;
*/
            class value_compare : public binary_function<value_type, value_type, bool> {
                //friend class map;
                protected:
                    Compare comp;
                    value_compare(Compare c);
                public:
                    bool operator()(const value_type& x, const value_type& y) const {
                        return (comp(a.first, b.first));
                    }
            };

            // construct/copy/destroy:
            explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
            template <class InputIterator>
            map(InputIterator first, InputIterator last,
                const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
            map(const map& m);
            ~map();

            // element access:
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
            void                                insert(InputIterator first, InputIterator last);
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

            void                    swap(map& m);
            allocator_type          get_allocator() const;
    };

    template <class Key, class T, class Compare, class Allocator>
    bool
    operator==(const map<Key, T, Compare, Allocator>& x,
            const map<Key, T, Compare, Allocator>& y);

    template <class Key, class T, class Compare, class Allocator>
    bool
    operator< (const map<Key, T, Compare, Allocator>& x,
            const map<Key, T, Compare, Allocator>& y);

    template <class Key, class T, class Compare, class Allocator>
    bool
    operator!=(const map<Key, T, Compare, Allocator>& x,
            const map<Key, T, Compare, Allocator>& y);

    template <class Key, class T, class Compare, class Allocator>
    bool
    operator> (const map<Key, T, Compare, Allocator>& x,
            const map<Key, T, Compare, Allocator>& y);

    template <class Key, class T, class Compare, class Allocator>
    bool
    operator>=(const map<Key, T, Compare, Allocator>& x,
            const map<Key, T, Compare, Allocator>& y);

    template <class Key, class T, class Compare, class Allocator>
    bool
    operator<=(const map<Key, T, Compare, Allocator>& x,
            const map<Key, T, Compare, Allocator>& y);

    // specialized algorithms:
    template <class Key, class T, class Compare, class Allocator>
    void
    swap(map<Key, T, Compare, Allocator>& x, map<Key, T, Compare, Allocator>& y) {
        x.swap(y);
    }
}

#endif
