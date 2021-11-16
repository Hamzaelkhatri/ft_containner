// re-build a vector like c++

#ifndef ITERATOS_HPP
#define ITERATOS_HPP

#include <iostream>
#include <cmath>

namespace ft
{
    //create a iterator class

    template <typename T>
    class iterator
    {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef std::ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;
    };

    // create own iterators_traits
    // to be able to use them in the class
    template <typename T>
    class iterators_traits
    {
    public:
        typedef T *iterator;
        typedef const T *const_iterator;
        // create iterator_category
        typedef std::random_access_iterator_tag iterator_category;
        // create difference_type
        typedef std::ptrdiff_t difference_type;
        // create value_type
        typedef T value_type;
        // create referenceÎ
        typedef T &reference;
        // create pointer
        typedef T *pointer;
    };

    // create own reverse_iterator to be able to use it in the class
    template <typename T>
    class reverse_iterator
    {
    private:
        ft::iterator _iter;

    public:
        // create iterator_traits
        typedef iterators_traits<T> iterator_traits;

        // create iterator
        typedef typename iterator_traits::iterator iterator;
        // create const_iterator
        typedef typename iterator_traits::const_iterator const_iterator;
        // create reverse_iterator
        typedef reverse_iterator<T> self;
        // create reference
        typedef typename iterator_traits::reference reference;
        // create pointer
        typedef typename iterator_traits::pointer pointer;
        // create difference_type
        typedef typename iterator_traits::difference_type difference_type;
        // create value_type
        typedef typename iterator_traits::value_type value_type;
        // create iterator_category
        typedef typename iterator_traits::iterator_category iterator_category;
        // create reverse_iterator
        reverse_iterator(iterator iter) : _iter(iter) {}
        // create reverse_iterator
        reverse_iterator(const reverse_iterator &other) : _iter(other._iter) {}
        // create reverse_iterator
        reverse_iterator &operator=(const reverse_iterator &other)
        {
            _iter = other._iter;
            return *this;
        }
        // create reverse_iterator
        reverse_iterator &operator++()
        {
            --_iter;
            return *this;
        }
        // create reverse_iterator
        reverse_iterator operator++(int)
        {
            reverse_iterator tmp(*this);
            --_iter;
            return tmp;
        }
        // create reverse_iterator
        reverse_iterator &operator--()
        {
            ++_iter;
            return *this;
        }
        // create reverse_iterator
        reverse_iterator operator--(int)
        {
            reverse_iterator tmp(*this);
            ++_iter;
            return tmp;
        }
        // create reverse_iterator
        reverse_iterator operator+(difference_type n) const
        {
            return reverse_iterator(_iter - n);
        }
        // create reverse_iterator
        reverse_iterator operator-(difference_type n) const
        {
            return reverse_iterator(_iter + n);
        }
        // create reverse_iterator
        reverse_iterator &operator+=(difference_type n)
        {
            _iter -= n;
            return *this;
        }
        // create reverse_iterator
        reverse_iterator &operator-=(difference_type n)
        {
            _iter += n;
            return *this;
        }
        // create reverse_iterator
        reference operator[](difference_type n) const
        {
            return *(_iter - n);
        }
        // create reverse_iterator
        bool operator==(const self &other) const
        {
            return _iter == other._iter;
        }
        // create reverse_iterator
        bool operator!=(const self &other) const
        {
            return _iter != other._iter;
        }
        // create reverse_iterator
        bool operator<(const self &other) const
        {
            return _iter > other._iter;
        }
        // create reverse_iterator
        bool operator>(const self &other) const
        {
            return _iter < other._iter;
        }
        // create reverse_iterator
        bool operator<=(const self &other) const
        {
            return _iter >= other._iter;
        }
        // create reverse_iterator
        bool operator>=(const self &other) const
        {
            return _iter <= other._iter;
        }
        // create reverse_iterator
        reference operator*() const
        {
            return *(_iter - 1);
        }
        // create reverse_iterator
        pointer operator->() const
        {
            return &(operator*());
        }
        // create reverse_iterator
        iterator base() const
        {
            return _iter;
        }
    };
}

#endif