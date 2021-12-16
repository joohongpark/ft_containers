#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include <integral_constant.hpp>

// from <type_traits>

namespace ft {
    template <class T>   struct is_integral                                     : public ft::false_type {};
    template <>          struct is_integral<bool>                               : public ft::true_type  {};
    template <>          struct is_integral<char>                               : public ft::true_type  {};
    template <>          struct is_integral<signed char>                        : public ft::true_type  {};
    template <>          struct is_integral<unsigned char>                      : public ft::true_type  {};
    template <>          struct is_integral<wchar_t>                            : public ft::true_type  {};
    template <>          struct is_integral<short>                              : public ft::true_type  {};
    template <>          struct is_integral<unsigned short>                     : public ft::true_type  {};
    template <>          struct is_integral<int>                                : public ft::true_type  {};
    template <>          struct is_integral<unsigned int>                       : public ft::true_type  {};
    template <>          struct is_integral<long>                               : public ft::true_type  {};
    template <>          struct is_integral<unsigned long>                      : public ft::true_type  {};
    template <>          struct is_integral<long long>                          : public ft::true_type  {};
    template <>          struct is_integral<unsigned long long>                 : public ft::true_type  {};

    template <>          struct is_integral<const bool>                         : public ft::true_type  {};
    template <>          struct is_integral<const char>                         : public ft::true_type  {};
    template <>          struct is_integral<const signed char>                  : public ft::true_type  {};
    template <>          struct is_integral<const unsigned char>                : public ft::true_type  {};
    template <>          struct is_integral<const wchar_t>                      : public ft::true_type  {};
    template <>          struct is_integral<const short>                        : public ft::true_type  {};
    template <>          struct is_integral<const unsigned short>               : public ft::true_type  {};
    template <>          struct is_integral<const int>                          : public ft::true_type  {};
    template <>          struct is_integral<const unsigned int>                 : public ft::true_type  {};
    template <>          struct is_integral<const long>                         : public ft::true_type  {};
    template <>          struct is_integral<const unsigned long>                : public ft::true_type  {};
    template <>          struct is_integral<const long long>                    : public ft::true_type  {};
    template <>          struct is_integral<const unsigned long long>           : public ft::true_type  {};

    template <>          struct is_integral<volatile const bool>                : public ft::true_type  {};
    template <>          struct is_integral<volatile const char>                : public ft::true_type  {};
    template <>          struct is_integral<volatile const signed char>         : public ft::true_type  {};
    template <>          struct is_integral<volatile const unsigned char>       : public ft::true_type  {};
    template <>          struct is_integral<volatile const wchar_t>             : public ft::true_type  {};
    template <>          struct is_integral<volatile const short>               : public ft::true_type  {};
    template <>          struct is_integral<volatile const unsigned short>      : public ft::true_type  {};
    template <>          struct is_integral<volatile const int>                 : public ft::true_type  {};
    template <>          struct is_integral<volatile const unsigned int>        : public ft::true_type  {};
    template <>          struct is_integral<volatile const long>                : public ft::true_type  {};
    template <>          struct is_integral<volatile const unsigned long>       : public ft::true_type  {};
    template <>          struct is_integral<volatile const long long>           : public ft::true_type  {};
    template <>          struct is_integral<volatile const unsigned long long>  : public ft::true_type  {};
}

#endif