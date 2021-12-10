// create our own stack class to use in the main function
#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <string>
#include "vector.hpp"
#include <algorithm>
#include <deque>

namespace ft
{

    template <class T, class Container = ft::vector<T> >
    class stack
    {
    private:
        Container c;

    public:
        // member type
        typedef T value_type;
        typedef Container container_type;
        typedef typename Container::size_type size_type;

        // contructor
        explicit stack(const container_type &ctnr = container_type())
        {
            c = ctnr;
        }

        // empty
        bool empty() const
        {
            return c.empty();
        }

        // size
        size_type size() const
        {
            return c.size();
        }

        // top
        const value_type &top() const
        {
            return c.back();
        }

        // push
        void push(const value_type &val)
        {
            c.push_back(val);
        }

        // pop
        void pop()
        {
            c.pop_back();
        }

        // swap
        void swap(stack &other)
        {
            c.swap(other.ctnr_);
        }
    };
    // operator <<
    template <class T, class Container>
    bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return lhs.ctnr_ == rhs.ctnr_;
    }

    template <class T, class Container>
    bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Container>
    bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return lhs.ctnr_ < rhs.ctnr_;
    }

    template <class T, class Container>
    bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return rhs < lhs;
    }

    template <class T, class Container>
    bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Container>
    bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return !(lhs < rhs);
    }

} // namespace ft

#endif