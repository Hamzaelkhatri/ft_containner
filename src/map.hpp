// re-build a  map<T t, T t> containner like c++

#ifndef MAP_HPP
#define MAP_HPP

#include "iterators.hpp"
#include "iter_bool.hpp"
#include "RBT.hpp"

namespace ft
{

    template <class Key,
              class T,
              class Compare = std::less<Key>,
              class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map
    {
    private:
        ft::RBT<Key, T, Compare, Alloc> _tree;
    };
};
#endif