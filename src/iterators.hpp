
#ifndef ITERATOS_HPP
#define ITERATOS_HPP

#include <iostream>
// #include <
#include <cmath>

namespace ft
{
    // create a iterator
    template <class Category,             // iterator::iterator_category
              class T,                    // iterator::value_type
              class Distance = ptrdiff_t, // iterator::difference_type
              class Pointer = T *,        // iterator::pointer
              class Reference = T &       // iterator::reference
              >
    class iterator
    {
    public:
        typedef Category iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
    };
    // create iterator_traits
    template <class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
    };
    // create iterator_traits for pointer
    template <class T>
    struct iterator_traits<T *>
    {
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
    };

    // create iterator_traits for const pointer
    template <class T>
    struct iterator_traits<const T *>
    {
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T *pointer;
        typedef const T &reference;
    };

    // create reverse_iterator
    template <class Iterator>
    class reverse_iterator
    {
    private:
        Iterator current;

    public:
        typedef Iterator iterator_type;
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<Iterator>::value_type value_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::pointer pointer;
        typedef typename iterator_traits<Iterator>::reference reference;
        // constructor default
        reverse_iterator() : current(0) {}
        // constructor initialisation
        reverse_iterator(Iterator current) : current(current) {}
        // constructor copy
        reverse_iterator(const reverse_iterator &it) : current(it.current) {}
        Iterator base() const { return current; }
        // member operator
        // Dereference iterator
        reference operator*() const
        {
            Iterator tmp = current;
            return *--tmp;
        }
        // Addition operator
        reverse_iterator &operator++()
        {
            --current;
            return *this;
        }
        // Subtraction operator
        reverse_iterator &operator--()
        {
            ++current;
            return *this;
        }
        // Increment iterator position
        reverse_iterator operator++(int)
        {
            reverse_iterator tmp = *this;
            --current;
            return tmp;
        }
        // Decrement iterator position
        reverse_iterator operator--(int)
        {
            reverse_iterator tmp = *this;
            ++current;
            return tmp;
        }
        // Advance iterator
        reverse_iterator &operator+=(difference_type n)
        {
            current -= n;
            return *this;
        }
        // Decrease iterator position
        reverse_iterator &operator-=(difference_type n)
        {
            current += n;
            return *this;
        }
        // Retrocede iterator
        reverse_iterator operator+(difference_type n) const
        {
            reverse_iterator tmp = *this;
            tmp += n;
            return tmp;
        }
        // Dereference iterator
        reverse_iterator operator-(difference_type n) const
        {
            reverse_iterator tmp = *this;
            tmp -= n;
            return tmp;
        }
        // Dereference iterator with offset
        reference operator[](difference_type n) const
        {
            return *(*this + n);
        }
    };
    // Non-member function overloads
    template <class Iterator>
    bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return lhs.base() == rhs.base();
    }
    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return !(lhs == rhs);
    }
    template <class Iterator>
    bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return rhs.base() < lhs.base();
    }
    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return rhs < lhs;
    }
    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return !(rhs < lhs);
    }
    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return !(lhs < rhs);
    }
    template <class Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rhs)
    {
        return reverse_iterator<Iterator>(rhs.base() - n);
    }
    template <class Iterator>
    reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rhs)
    {
        return reverse_iterator<Iterator>(rhs.base() + n);
    }
    // template <
    //     class T1,
    //     class T2>
    //  pair
    // {
    // }
}

#endif
