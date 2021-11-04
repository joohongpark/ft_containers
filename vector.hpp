#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"
#include "type_traits.hpp"

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
            // constructors
            vector();
            vector(size_type n, const value_type& val);
            // 라이브러리엔 입력 반복자이고 정방향 반복자가 아닐때에 대한 오버로딩도 존재함.
            template <class InputIterator>
            vector(InputIterator first, typename enable_if<is_input_iterator<InputIterator>::value, InputIterator>::type last);
            vector(const vector& x);

            // destructor
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
            void            resize(size_type sz, const value_type val = value_type()); // 구현 필요

            // Methods (access)
            reference       at(size_type n);
            const_reference at(size_type n) const;
            reference       front();
            const_reference front() const;
            reference       back();
            const_reference back() const;
            void            push_back(const value_type& x);
            void            pop_back();
            void            swap(vector& x); // 구현 필요
            void            clear(); // 구현 필요

            // Methods (other)
            allocator_type  get_allocator() const; // 구현 필요

            template <class InputIterator>
            void            assign(InputIterator first, InputIterator last); // 구현 필요
            void            assign(size_type n, const value_type& u); // 구현 필요

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
            iterator                insert(const_iterator position, InputIterator first, InputIterator last); // 구현 필요

            // Methods (Private)
        private:
            size_type _recommend_size(size_type new_size) const;
    };
    template <class T, class Allocator>
    bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y); // 구현 필요
    template <class T, class Allocator>
    bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y); // 구현 필요
    template <class T, class Allocator>
    bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y); // 구현 필요
    template <class T, class Allocator>
    bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y); // 구현 필요
    template <class T, class Allocator>
    bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y); // 구현 필요
    template <class T, class Allocator>
    bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y); // 구현 필요
    template <class T, class Allocator>
    void swap(vector<T,Allocator>& x, vector<T,Allocator>& y); // 구현 필요
}

namespace ft {

    // constructors
    template <class T, class Allocator>
    vector<T, Allocator>::vector() : _data(NULL), _size(0), _capacity(0) {}

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
    // TODO: 이터레이터 상태에 따라 검증 해야 할 듯
    vector<T, Allocator>::vector(InputIterator first, typename enable_if<is_input_iterator<InputIterator>::value, InputIterator>::type last) {
        difference_type len = last - first;
        _size = len;
        _capacity = len;
        _data = _alloc.allocate(_size);
        for (size_type i = 0; i < _size; i++) {
            _data[i] = *first;
            first++;
        }
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
        return (_data[__n]);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](size_type __n) const {
        return (_data[__n]);
    }

    // Methods (capacity)
    template <class T, class Allocator>
    typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const {
        return (_size);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size() const {
        // FIXME: 조건 추가 필요할 듯 2021-10-06
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
        // 인수가 메모리 할당된 크기보다 크면 구문 실행
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
    void vector<T, Allocator>::resize(size_type sz, const value_type val = value_type()) {
        if (_size < sz) {
            iterator __r;
            size_type append_size = sz - _size;
            if (append_size <= _capacity && _size <= _capacity - append_size)
            {
                __r = end();
                _size += append_size;
            }
            else
            {
                vector __v(__alloc());
                __v.reserve(__recommend(_size + append_size));
                __v._size = _size + append_size;
                __r = _VSTD::copy(cbegin(), cend(), __v.begin());
                swap(__v);
            }
            _VSTD::fill_n(__r, append_size, val);
        } else {
            _size = sz;
        }
    }

    // Methods (access)
    template <class T, class Allocator>
    typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type n) {
        // FIXME: 에러 핸들링 필요한지 확인 필요 2021-10-06
        return (_data[n]);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(size_type n) const {
        // FIXME: 에러 핸들링 필요한지 확인 필요 2021-10-06
        return (_data[n]);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::reference vector<T, Allocator>::front() {
        // FIXME: 에러 핸들링 필요한지 확인 필요 2021-10-06
        return (_data[0]);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() const {
        // FIXME: 에러 핸들링 필요한지 확인 필요 2021-10-06
        return (_data[0]);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::reference vector<T, Allocator>::back() {
        // FIXME: 에러 핸들링 필요한지 확인 필요 2021-10-06
        return (_data[_size - 1]);
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() const {
        // FIXME: 에러 핸들링 필요한지 확인 필요 2021-10-06
        return (_data[_size - 1]);
    }

    template <class T, class Allocator>
    void vector<T, Allocator>::push_back(const value_type& x) {
        // 현재 사이즈가 메모리 할당된 크기와 동일하다면
        if (_size == _capacity) {
            // 현재 사이즈 + 1 또는 현재 사이즈의 두배를 할당함
            reserve(_recommend_size(_size + 1));
        }
        // 사이즈 + 1 한 뒤에
        _size++;
        // 마지막 공간에 값 삽입
        back() = x;
    }

    template <class T, class Allocator>
    void vector<T, Allocator>::pop_back() {
        if (_size != 0) {
            _size--;
        }
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
        return (reverse_iterator(_data));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rbegin() const{
        return (const_reverse_iterator(_data));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rend(){
        return (reverse_iterator(&_data[_size]));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rend() const{
        return (const_reverse_iterator(&_data[_size]));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(const_iterator position) {
        difference_type start = position - begin();
        for (difference_type i = start; i < _size - 1; i++) {
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
        if (size > 0) {
            for (difference_type i = 0; i < size; i++) {
                _data[start + i] = _data[fin + i];
            }
            _size -= size;
        }
        return (iterator(&_data[start]));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator position, const value_type& x) {
        // 현재 사이즈가 메모리 할당된 크기와 동일하다면
        if (_size == _capacity) {
            // 현재 사이즈 + 1 또는 현재 사이즈의 두배를 할당함
            reserve(_recommend_size(_size + 1));
        }
        difference_type start = position - begin();
        for (difference_type i = _size; i > start; i--) {
            _data[i] = _data[i - 1];
        }
        _data[start] = x;
        _size++;
        return (iterator(&_data[start]));
    }

    template <class T, class Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator position, size_type n, const value_type& x) {
        if ((_size + n) > _capacity) {
            reserve(_recommend_size(_size + n));
        }
        difference_type start = position - begin();
        for (difference_type i = _size; i > start; i--) {
            _data[i + n - 1] = _data[i - 1];
        }
        for (size_type i = 0; i < n; i++) {
            _data[start + i] = x;
        }
        _size += n;
        return (iterator(&_data[start]));
    }

    // Methods (Private)
    template <class T, class Allocator>
    typename vector<T, Allocator>::size_type vector<T, Allocator>::_recommend_size(size_type new_size) const {
        const size_type _ms = max_size(); // 컨테이너가 최대로 할당 가능한 크기
        // FIXME: 에러 핸들링 삽입해야 할 듯 2021-10-06
        //if (_new_size > _ms) // 인수가 더 크면
        //    this->__throw_length_error(); // 에러 스로잉
        const size_type _cap = capacity(); // 현재 컨테이너의 수용할 수 있는 공간
        if (_cap >= _ms / 2) // 그 공간이 최대 크기와 같거나 넘으면
            return (_ms); // 그 공간을 리턴
        return ((2 * _cap > new_size) ? (2 * _cap) : new_size); // 주어진 사이즈 또는 현재 공간의 두배 리턴
    }

}

#endif
