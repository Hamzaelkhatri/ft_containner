// re-build a vector like c++

#ifndef ITERATOS_HPP
#define ITERATOS_HPP

#include <iostream>
#include <cmath>

namespace ft
{
    //create a iterator
    template <class Category,              // iterator::iterator_category
          class T,                     // iterator::value_type
          class Distance = ptrdiff_t,  // iterator::difference_type
          class Pointer = T*,          // iterator::pointer
          class Reference = T&         // iterator::reference
          > class iterator
    {
        public:
            typedef Category iterator_category;
            typedef T value_type;
            typedef Distance difference_type;
            typedef Pointer pointer;
            typedef Reference reference;
    };
}

#endif