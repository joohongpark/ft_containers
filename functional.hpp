#ifndef FUNCTIONAL_HPP
#define FUNCTIONAL_HPP

namespace ft {

    // binary_function은 입력 인수를 두개 가지는 함수를 가지고 있는 클래스를 정의하는데 사용한다.
    // 보통 멤버 함수 operator()에 함수를 정의한다.
    template <class Arg1, class Arg2, class Result>
    struct binary_function {
        typedef Arg1   first_argument_type;
        typedef Arg2   second_argument_type;
        typedef Result result_type;
    };

    // 크기 비교를 하는 함수 객체를 제공하는 클래스이다.
    // T는 연산자 <를 지원하여야 하며 binary_function로부터 상속받아 사용한다.
    template <class Type>
    struct less : binary_function<Type, Type, bool> {
        bool operator()(const Type& __x, const Type& __y) const {
            return (__x < __y);
        }
    };

}

#endif
