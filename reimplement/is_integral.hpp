#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include <type_traits>

// from <type_traits>

namespace ft {
    template <class T>   struct is_integral                                     : public std::false_type {};
    template <>          struct is_integral<bool>                               : public std::true_type  {};
    template <>          struct is_integral<char>                               : public std::true_type  {};
    template <>          struct is_integral<signed char>                        : public std::true_type  {};
    template <>          struct is_integral<unsigned char>                      : public std::true_type  {};
    template <>          struct is_integral<wchar_t>                            : public std::true_type  {};
    template <>          struct is_integral<short>                              : public std::true_type  {};
    template <>          struct is_integral<unsigned short>                     : public std::true_type  {};
    template <>          struct is_integral<int>                                : public std::true_type  {};
    template <>          struct is_integral<unsigned int>                       : public std::true_type  {};
    template <>          struct is_integral<long>                               : public std::true_type  {};
    template <>          struct is_integral<unsigned long>                      : public std::true_type  {};
    template <>          struct is_integral<long long>                          : public std::true_type  {};
    template <>          struct is_integral<unsigned long long>                 : public std::true_type  {};

    template <>          struct is_integral<const bool>                         : public std::true_type  {};
    template <>          struct is_integral<const char>                         : public std::true_type  {};
    template <>          struct is_integral<const signed char>                  : public std::true_type  {};
    template <>          struct is_integral<const unsigned char>                : public std::true_type  {};
    template <>          struct is_integral<const wchar_t>                      : public std::true_type  {};
    template <>          struct is_integral<const short>                        : public std::true_type  {};
    template <>          struct is_integral<const unsigned short>               : public std::true_type  {};
    template <>          struct is_integral<const int>                          : public std::true_type  {};
    template <>          struct is_integral<const unsigned int>                 : public std::true_type  {};
    template <>          struct is_integral<const long>                         : public std::true_type  {};
    template <>          struct is_integral<const unsigned long>                : public std::true_type  {};
    template <>          struct is_integral<const long long>                    : public std::true_type  {};
    template <>          struct is_integral<const unsigned long long>           : public std::true_type  {};

    template <>          struct is_integral<volatile const bool>                : public std::true_type  {};
    template <>          struct is_integral<volatile const char>                : public std::true_type  {};
    template <>          struct is_integral<volatile const signed char>         : public std::true_type  {};
    template <>          struct is_integral<volatile const unsigned char>       : public std::true_type  {};
    template <>          struct is_integral<volatile const wchar_t>             : public std::true_type  {};
    template <>          struct is_integral<volatile const short>               : public std::true_type  {};
    template <>          struct is_integral<volatile const unsigned short>      : public std::true_type  {};
    template <>          struct is_integral<volatile const int>                 : public std::true_type  {};
    template <>          struct is_integral<volatile const unsigned int>        : public std::true_type  {};
    template <>          struct is_integral<volatile const long>                : public std::true_type  {};
    template <>          struct is_integral<volatile const unsigned long>       : public std::true_type  {};
    template <>          struct is_integral<volatile const long long>           : public std::true_type  {};
    template <>          struct is_integral<volatile const unsigned long long>  : public std::true_type  {};
}

#endif