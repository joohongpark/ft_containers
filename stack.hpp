#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {

    template <class T, class Container = ft::vector<T> >
    class stack {
        public:
            typedef Container                               container_type;
            typedef typename container_type::value_type     value_type;
            typedef typename container_type::size_type      size_type;

        protected:
            container_type c;

        public:
            explicit stack(const container_type& cont = container_type());
            stack(const stack& q);
            ~stack();

            stack&                                          operator=(const stack& q);

            bool                                            empty() const;
            size_type                                       size() const;
            value_type                                      top();
            const value_type                                top() const;
            void                                            push(const value_type& x);
            void                                            pop();
    };

    template <class T, class Container>
    stack<T, Container>::stack(const container_type& cont) : c(cont) {}

    template <class T, class Container>
    stack<T, Container>::stack(const stack& q) : c(q.c) {}

    template <class T, class Container>
    stack<T, Container>::~stack() {}

    template <class T, class Container>
    stack<T, Container>& stack<T, Container>::operator=(const stack& q) {
        if (this != &q) {
            this->c = q.c;
        }
    }

    template <class T, class Container>
    bool stack<T, Container>::empty() const {
        return (c.empty());
    }

    template <class T, class Container>
    typename stack<T, Container>::size_type stack<T, Container>::size() const {
        return (c.size());
    }

    template <class T, class Container>
    typename stack<T, Container>::value_type stack<T, Container>::top() {
        return (c.back());
    }

    template <class T, class Container>
    const typename stack<T, Container>::value_type stack<T, Container>::top() const {
        return (c.back());
    }

    template <class T, class Container>
    void stack<T, Container>::push(const value_type& x) {
        return (c.push_back(x));
    }

    template <class T, class Container>
    void stack<T, Container>::pop() {
        return (c.pop_back());
    }

    template <class T, class Container>
    bool operator==(const stack<T, Container>& x, const stack<T, Container>& y) {
        return (x.c == y.c);
    }

    template <class T, class Container>
    bool operator< (const stack<T, Container>& x, const stack<T, Container>& y) {
        return (x.c < y.c);
    }

    template <class T, class Container>
    bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y) {
        return (!(x.c == y.c));
    }

    template <class T, class Container>
    bool operator> (const stack<T, Container>& x, const stack<T, Container>& y) {
        return (y < x);
    }

    template <class T, class Container>
    bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y) {
        return (!(x < y));
    }

    template <class T, class Container>
    bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y) {
        return (!(y < x));
    }
}
#endif
