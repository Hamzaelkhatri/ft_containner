#ifndef ITER_BOOL_HPP
#define ITER_BOOL_HPP
#include <iostream>
#include "iterators.hpp"
namespace ft
{
    // create my own std::enable_if cpp98

    template <bool B, class T = void>
    struct enable_if
    {
    };

    template <class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    // create my own std::is_integral
    template <class T>
    struct is_integral
    {
        static const bool value = false;
    };

    template <>
    struct is_integral<bool>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<char>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<signed char>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned char>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<wchar_t>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<char16_t>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<char32_t>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<short>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned short>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<int>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned int>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<long>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned long>
    {
        static const bool value = true;
    };
    // create my own equal function

    template <class InputIt1, class InputIt2>
    bool equal(InputIt1 first1, InputIt1 last1,
               InputIt2 first2)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            if (!(*first1 == *first2))
            {
                return false;
            }
        }
        return true;
    }

    //
    template <class InputIt1, class InputIt2, class BinaryPredicate>
    bool equal(InputIt1 first1, InputIt1 last1,
               InputIt2 first2, BinaryPredicate p)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            if (!p(*first1, *first2))
            {
                return false;
            }
        }
        return true;
    }
    template <class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    template <class InputIt1, class InputIt2, class Compare>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2,
                                 Compare comp)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
        {
            if (comp(*first1, *first2))
                return true;
            if (comp(*first2, *first1))
                return false;
        }
        return (first1 == last1) && (first2 != last2);
    }
    // create my own std::pair
    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        T1 first;
        T2 second;
        pair()
            : first(), second()
        {
        }

        template <class U, class V>
        pair(const pair<U, V> &pr) : first(pr.first), second(pr.second)
        {
        }
        pair(const first_type &a, const second_type &b) : first(a), second(b)
        {
        }
        // implicit declaration of copy constructor
        pair &operator=(const pair &pr)
        {
            first = pr.first;
            second = pr.second;
            return *this;
        }
    };
    // create my own std::make_pair
    template <class T1, class T2>
    pair<T1, T2> make_pair(const T1 &a, const T2 &b)
    {
        return pair<T1, T2>(a, b);
    }
    // create my own std::swap
    template <class T>
    void swap(T &a, T &b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }
    // create my own std::copy
    template <class InputIt, class OutputIt>
    OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
    {
        for (; first != last; ++first, ++d_first)
        {
            *d_first = *first;
        }
        return d_first;
    }
    // create my own std::clear
    template <class ForwardIt>
    void clear(ForwardIt first, ForwardIt last)
    {
        for (; first != last; ++first)
        {
            *first = typename ft::iterator_traits<ForwardIt>::value_type();
        }
    }
}
#endif
