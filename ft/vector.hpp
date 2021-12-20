#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>

#include <vector_iterator.hpp>
#include <reverse_iterator.hpp>
#include <equal.hpp>
#include <lexicographical_compare.hpp>
#include <is_input_iterator.hpp>

namespace ft {
    template <class T, class Allocator = std::allocator<T> >
    class vector {
        public:
            typedef T                                               value_type;
            typedef Allocator                                       allocator_type;
            typedef typename allocator_type::reference              reference;
            typedef typename allocator_type::const_reference        const_reference;
            typedef typename allocator_type::size_type              size_type;
            typedef typename allocator_type::difference_type        difference_type;
            typedef typename allocator_type::pointer                pointer;
            typedef typename allocator_type::const_pointer          const_pointer;
            typedef ft::vector_iterator<pointer>                    iterator;
            typedef ft::vector_iterator<const_pointer>              const_iterator;
            typedef ft::reverse_iterator<iterator>                  reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;
        private:
            pointer                                                 _data;
            size_type                                               _size;
            size_type                                               _capacity;
            allocator_type                                          _alloc;

        public:
            // construct/copy/destroy:
            vector(const allocator_type& alloc = allocator_type());
            vector(size_type n, const value_type& val = value_type());
            template <class InputIterator>
            vector(InputIterator first, typename enable_if<is_input_iterator<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc = allocator_type());
            vector(const vector& x);
            ~vector();

            // Operator
            vector&         operator=(const vector& x);
            reference       operator[] (size_type n);
            const_reference operator[] (size_type n) const;

            // Methods (capacity)
            size_type       size() const;
            size_type       max_size() const;
            size_type       capacity() const;
            bool            empty() const;
            void            reserve(size_type n);
            void            resize(size_type sz, value_type val = value_type());

            // Methods (access)
            reference       at(size_type n);
            const_reference at(size_type n) const;
            reference       front();
            const_reference front() const;
            reference       back();
            const_reference back() const;
            void            push_back(const value_type& x);
            void            pop_back();
            void            swap(vector& x);
            void            clear();

            // Methods (other)
            template <class InputIterator>
            void            assign(InputIterator first, typename enable_if<is_input_iterator<InputIterator>::value, InputIterator>::type last);
            void            assign(size_type n, const value_type& u);
            allocator_type  get_allocator() const;

            // Methods (Iterater)
            iterator                begin();
            const_iterator          begin() const;
            iterator                end();
            const_iterator          end() const;
            reverse_iterator        rbegin();
            const_reverse_iterator  rbegin() const;
            reverse_iterator        rend();
            const_reverse_iterator  rend() const;
            iterator                erase(const_iterator position);
            iterator                erase(const_iterator first, const_iterator last);
            iterator                insert(const_iterator position, const value_type& x);
            iterator                insert(const_iterator position, size_type n, const value_type& x);
            template <class InputIterator>
            iterator                insert(const_iterator position, InputIterator first, typename enable_if<is_input_iterator<InputIterator>::value, InputIterator>::type last);

        private:
            // Methods (Private)
            size_type _recommend_size(size_type new_size) const;
    };
}

namespace ft {

    // constructors
    template <class T, class Allocator>
    vector<T, Allocator>::vector(const allocator_type& alloc) : _data(NULL), _size(0), _capacity(0), _alloc(alloc) {}

    template <class T, class Allocator>
    vector<T, Allocator>::vector(size_type n, const value_type& val) : _size(n), _capacity(n) {
        if (n > 0) {
            _data = _alloc.allocate(_size);
            for (size_type i = 0; i < n; i++) {
                _data[i] = val;
            }
        } else {
            _data = NULL;
        }
    }

    template <class T, class Allocator>
    template <class InputIterator>
    vector<T, Allocator>::vector(InputIterator first, typename enable_if<is_input_iterator<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc) : _alloc(alloc) {
        _size = 0;
        _capacity = 0;
        _data = NULL;
        for (; first != last; ++first) {
            push_back(*first);
        }
        pointer _new_data = _alloc.allocate(_size);
        for (size_type i = 0; i < _size; i++) {
            _new_data[i] = _data[i];
        }
        _alloc.deallocate(_data, _capacity);
        _data = _new_data;
        _capacity = _size;
    }

    template <class T, class Allocator>
    vector<T, Allocator>::vector(const vector& x) {
        if (this != &x) {
            *this = x;
        }
    }

    // destructor
    template <class T, class Allocator>
    vector<T, Allocator>::~vector() {
        if (_capacity > 0) {
            _alloc.deallocate(_data, _capacity);
        }
    }

    // Operator
    template <class T, class Allocator>
    vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& x) {
        if (this != &x) {
            this->_size = x._size;
            this->_capacity = x._capacity;
            this->_data = _alloc.allocate(_size);
            for (size_type i = 0; i < _size; i++) {
                this->_data[i] = x._data[i];
            }
        }
        return (*this);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](size_type __n) {
        if (_size <= __n) {
            throw std::out_of_range("ft::vector::at()");
        }
        return (_data[__n]);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](size_type __n) const {
        if (_size <= __n) {
            throw std::out_of_range("ft::vector::at()");
        }
        return (_data[__n]);
    }

    // Methods (capacity)
    template <class T, class Allocator>
    typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const {
        return (_size);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size() const {
        return (_alloc.max_size());
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity() const {
        return (_capacity);
    }

    template <class T, class Allocator>
    bool vector<T, Allocator>::empty() const {
        return (_size == 0);
    }

    template <class T, class Allocator>
    void vector<T, Allocator>::reserve(size_type n) {
        if (n > _capacity) {
            pointer _new_data = _alloc.allocate(n);
            for (size_type i = 0; i < _size; i++) {
                _new_data[i] = _data[i];
            }
            _alloc.deallocate(_data, _capacity);
            _data = _new_data;
            _capacity = n;
        }
    }

    template <class T, class Allocator>
    void vector<T, Allocator>::resize(size_type sz, value_type val) {
        if (_size < sz) {
            size_type append_size = sz - _size;
            if (sz > _capacity) {
                reserve(_recommend_size(_size + append_size));
            }
            for (size_type i = _size; i < sz; i++) {
                _data[i] = val;
            }
        }
        _size = sz;
    }

    // Methods (access)
    template <class T, class Allocator>
    typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type n) {
        if (_size <= n) {
            throw std::out_of_range("ft::vector::at()");
        }
        return (_data[n]);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(size_type n) const {
        if (_size <= n) {
            throw std::out_of_range("ft::vector::at()");
        }
        return (_data[n]);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::reference vector<T, Allocator>::front() {
        return (_data[0]);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() const {
        return (_data[0]);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::reference vector<T, Allocator>::back() {
        return (_data[_size - 1]);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() const {
        return (_data[_size - 1]);
    }

    template <class T, class Allocator>
    void vector<T, Allocator>::push_back(const value_type& x) {
        if (_size == _capacity) {
            reserve(_recommend_size(_size + 1));
        }
        _size++;
        back() = x;
    }

    template <class T, class Allocator>
    void vector<T, Allocator>::pop_back() {
        if (_size != 0) {
            _size--;
        }
    }

    template <class T, class Allocator>
    void vector<T, Allocator>::swap(vector& x) {
        pointer _data_tmp = x._data;
        size_type _size_tmp = x._size;
        size_type _capacity_tmp = x._capacity;
        allocator_type _alloc_tmp = x._alloc;
        x._data = this->_data;
        x._size = this->_size;
        x._capacity = this->_capacity;
        x._alloc = this->_alloc;
        this->_data = _data_tmp;
        this->_size = _size_tmp;
        this->_capacity = _capacity_tmp;
        this->_alloc = _alloc_tmp;
    }

    template <class T, class Allocator>
    void vector<T, Allocator>::clear() {
        this->_size = 0;
    }

    // Methods (other)
    template <class T, class Allocator>
    void vector<T, Allocator>::assign(size_type n, const value_type& u) {
        clear();
        resize(n, u);
    }

    template <class T, class Allocator>
    template <class InputIterator>
    void vector<T, Allocator>::assign(InputIterator first, typename enable_if<is_input_iterator<InputIterator>::value, InputIterator>::type last) {
        clear();
        for (; first != last; ++first) {
            push_back(*first);
        }
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::allocator_type vector<T, Allocator>::get_allocator() const {
        return (_alloc);
    }

    // Methods (Iterater)
    template <class T, class Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::begin() {
        return (iterator(_data));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_iterator vector<T, Allocator>::begin() const {
        return (const_iterator(_data));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::end(){
        return (iterator(&_data[_size]));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end() const{
        return (const_iterator(&_data[_size]));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rbegin() {
        return (reverse_iterator(end()));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rbegin() const{
        return (const_reverse_iterator(end()));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rend(){
        return (reverse_iterator(begin()));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rend() const{
        return (const_reverse_iterator(begin()));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(const_iterator position) {
        difference_type start = position - begin();
        for (difference_type i = start; i < static_cast<difference_type>(_size) - 1; i++) {
            _data[i] = _data[i + 1];
        }
        _size--;
        return (iterator(&_data[start]));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(const_iterator first, const_iterator last) {
        difference_type start = first - begin();
        difference_type fin = last - begin();
        difference_type size = fin - start;
        for (difference_type i = fin; i < static_cast<difference_type>(_size); i++) {
            _data[i - size] = _data[i];
        }
        _size -= size;
        return (iterator(&_data[start]));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator position, const value_type& x) {
        difference_type start = position - begin();
        if (_size == _capacity) {
            reserve(_recommend_size(_size + 1));
        }
        for (difference_type i = _size; i > start; i--) {
            _data[i] = _data[i - 1];
        }
        _data[start] = x;
        _size++;
        return (iterator(&_data[start]));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator position, size_type n, const value_type& x) {
        difference_type start = position - begin();
        if ((_size + n) > _capacity) {
            reserve(_recommend_size(_size + n));
        }
        for (difference_type i = _size; i > start; i--) {
            _data[i + n - 1] = _data[i - 1];
        }
        for (size_type i = 0; i < n; i++) {
            _data[start + i] = x;
        }
        _size += n;
        return (iterator(&_data[start]));
    }

    template <class T, class Allocator>
    template <class InputIterator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator position, InputIterator first, typename enable_if<is_input_iterator<InputIterator>::value, InputIterator>::type last) {
        vector new_data(first, last);
        size_type new_data_len = new_data.size();
        difference_type start = position - begin();
        if ((_size + new_data_len) > _capacity) {
            reserve(_recommend_size(_size + new_data_len));
        }
        for (difference_type i = _size; i > start; i--) {
            _data[i + new_data_len - 1] = _data[i - 1];
        }
        for (size_type i = 0; i < new_data_len; i++) {
            _data[start + i] = new_data[i];
        }
        _size += new_data_len;
        return (iterator(&_data[start]));
    }

    // Methods (Private)
    template <class T, class Allocator>
    typename vector<T, Allocator>::size_type vector<T, Allocator>::_recommend_size(size_type new_size) const {
        const size_type _ms = max_size();
        const size_type _cap = capacity();
        if (_cap >= _ms / 2) {
            return (_ms);
        }
        return ((2 * _cap > new_size) ? (2 * _cap) : new_size);
    }

    template <class T, class Allocator>
    bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
        return (x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()));
    }

    template <class T, class Allocator>
    bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
        return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
    }

    template <class T, class Allocator>
    bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
        return !(x == y);
    }

    template <class T, class Allocator>
    bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
        return y < x;
    }

    template <class T, class Allocator>
    bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
        return !(x < y);
    }

    template <class T, class Allocator>
    bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
        return !(y < x);
    }

    template <class T, class Allocator>
    void swap(vector<T,Allocator>& x, vector<T,Allocator>& y) {
        x.swap(y);
    }

}

#endif
