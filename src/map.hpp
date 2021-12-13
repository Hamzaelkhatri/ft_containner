// re-build a  map<T t, T t> containner like c++

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <cctype>
#include <locale>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cassert>
#include <climits>
#include <cfloat>
#include "map.hpp"

namespace ft
{
    template <class Key,                                             // map::key_type
              class T,                                               // map::mapped_type
              class Compare = std::less<Key>,                        // map::key_compare
              class Alloc = std::allocator<std::pair<const Key, T> > // map::allocator_type
              >
    class map
    {
        // member types
    private:
        // parametre of constructor

    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef std::pair<const Key, T> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename allocator_type::iterator iterator;
        typedef typename allocator_type::const_iterator const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        // member functions
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type())
            : comp_(comp), alloc_(alloc)
        {
        }
        map(const map &x)
            : comp_(x.comp_), alloc_(x.alloc_)
        {
            copy(x.begin(), x.end(), begin());
        }

        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
            : comp_(comp), alloc_(alloc)
        {
            copy(first, last, begin());
        }
    };
}
#endif