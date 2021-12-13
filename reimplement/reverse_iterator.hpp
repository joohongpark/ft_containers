#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iterator>

// from <iterator>

namespace ft {
    template <class Iterator>
    class reverse_iterator
        : public std::iterator<
            typename iterator_traits<Iterator>::iterator_category,
            typename iterator_traits<Iterator>::value_type,
            typename iterator_traits<Iterator>::difference_type,
            typename iterator_traits<Iterator>::pointer,
            typename iterator_traits<Iterator>::reference
        >
    {
        protected:
            Iterator current;
        public:
            typedef Iterator                                            iterator_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::reference       reference;
            typedef typename iterator_traits<Iterator>::pointer         pointer;

            // 생성자, 복사 생성자
            reverse_iterator() : current() {};
            explicit reverse_iterator(Iterator x) : current(x) {};
            template <class Iter>
                reverse_iterator(const reverse_iterator<Iter>& i) : current(i.base()) {};
            
            // 대입 연산자
            template <class Iter> reverse_iterator& operator=(const reverse_iterator<Iter>& u) {
                current = u.base();
                return (*this);
            }
        
            // getter
            Iterator            base() const {
                return (current);
            }

            // 연산자 오버로딩
            reference           operator*() const {
                Iterator tmp = current;
                return (*--tmp);
            }
            pointer             operator->() const {
                return (&operator*());
            }
            reverse_iterator&   operator++() {
                --current;
                return (*this);
            }
            reverse_iterator    operator++(int) {
                reverse_iterator tmp(*this);
                --current;
                return (tmp);
            }
            reverse_iterator&   operator--() {
                ++current;
                return (*this);
            }
            reverse_iterator    operator--(int) {
                reverse_iterator tmp(*this);
                ++current;
                return (tmp);
            }
            reverse_iterator    operator+ (difference_type n) const {
                return (reverse_iterator(current - n));
            }
            reverse_iterator&   operator+=(difference_type n) {
                current -= n;
                return (*this);
            }
            reverse_iterator    operator- (difference_type n) const {
                return (reverse_iterator(current + n));
            }
            reverse_iterator&   operator-=(difference_type n) {
                current += n;
                return (*this);
            }
            reference           operator[](difference_type n) const {
                return (*(*this + n));
            }
    };

    template <class Iterator1, class Iterator2>
    bool operator==(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
        return (x.base() == y.base());
    }

    template <class Iterator1, class Iterator2>
    bool operator<(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
        return (x.base() > y.base());
    }

    template <class Iterator1, class Iterator2>
    bool operator!=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
        return (x.base() != y.base());
    }

    template <class Iterator1, class Iterator2>
    bool operator>(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
        return (x.base() < y.base());
    }

    template <class Iterator1, class Iterator2>
    bool operator>=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
        return (x.base() <= y.base());
    }

    template <class Iterator1, class Iterator2>
    bool operator<=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
        return (x.base() >= y.base());
    }

    template <class Iterator1, class Iterator2>
    typename reverse_iterator<Iterator1>::difference_type
    operator-(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
        return (y.base() - x.base());
    }

    template <class Iterator>
    reverse_iterator<Iterator>
    operator+(
        typename reverse_iterator<Iterator>::difference_type n,
        const reverse_iterator<Iterator>& x) {
            return (reverse_iterator<Iterator>(x.base() - n));
    }
}
#endif