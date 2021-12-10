#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <cmath>
#include "iterators.hpp"
#include "iter_bool.hpp"

namespace ft
{
    // Vector class
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {

    public:
        typedef T *iterator;
        typedef const T *const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        // constructors
    private:
        size_type _size;
        size_type _capacity;
        pointer _data;
        allocator_type _alloc;

    public:
        vector() : _size(0), _capacity(0), _data(nullptr), _alloc() {}
        explicit vector(size_type n) : _size(n), _capacity(n), _data(nullptr), _alloc() { _data = _alloc.allocate(n); }
        vector(size_type n, const T &val) : _size(n), _capacity(n), _data(nullptr), _alloc()
        {
            _data = _alloc.allocate(n);
            for (size_type i = 0; i < n; ++i)
                _alloc.construct(_data + i, val);
        }
        vector(const vector &v) : _size(v._size), _capacity(v._capacity), _data(_alloc.allocate(v._capacity))
        {
            for (size_type i = 0; i < _size; ++i)
                _alloc.construct(_data + i, v[i]);
        }
        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
            : _size(0), _capacity(0), _data(nullptr), _alloc(alloc)
        {
            for (; first != last; ++first)
                push_back(*first);
        }

        // destructor
        ~vector()
        {
            for (size_type i = 0; i < _size; ++i)
                _alloc.destroy(_data + i);
            _alloc.deallocate(_data, _capacity);
        }
        // operator overloads
        vector &operator=(const vector &v)
        {
            if (this != &v)
            {
                for (size_type i = 0; i < _size; ++i)
                    _alloc.destroy(_data + i);
                _alloc.deallocate(_data, _capacity);
                _size = v._size;
                _capacity = v._capacity;
                _data = _alloc.allocate(_capacity);
                for (size_type i = 0; i < _size; ++i)
                    _alloc.construct(_data + i, v[i]);
            }
            return *this;
        }
        // iterators
        iterator begin() { return _data; }
        const_iterator begin() const { return _data; }
        iterator end() { return _data + _size; }
        const_iterator end() const { return _data + _size; }
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
        // capacity
        bool empty() const { return _size == 0; }
        size_type size() const { return _size; }
        size_type capacity() const { return _capacity; }
        void reserve(size_type n)
        {
            if (n > _capacity)
            {
                pointer tmp = _alloc.allocate(n);
                for (size_type i = 0; i < _size; ++i)
                    _alloc.construct(tmp + i, _data[i]);
                for (size_type i = 0; i < _size; ++i)
                    _alloc.destroy(_data + i);
                _alloc.deallocate(_data, _capacity);
                _data = tmp;
                _capacity = n;
            }
        }

        // get_allocator
        allocator_type get_allocator() const { return _alloc; }
        // max_size
        size_type max_size() const { return _alloc.max_size(); }
        // element access
        reference operator[](size_type n) { return _data[n]; }
        const_reference operator[](size_type n) const { return _data[n]; }
        reference at(size_type n)
        {
            if (n >= _size)
                throw std::out_of_range("out of range");
            return _data[n];
        }
        const_reference at(size_type n) const
        {
            if (n >= _size)
                throw std::out_of_range("out of range");
            return _data[n];
        }
        reference front() { return _data[0]; }
        const_reference front() const { return _data[0]; }
        reference back() { return _data[_size - 1]; }
        const_reference back() const { return _data[_size - 1]; }
        // modifiers
        void push_back(const T &val)
        {
            if (_size == _capacity)
                reserve(_capacity + 1);
            _alloc.construct(_data + _size, val);
            ++_size;
        };

        void pop_back()
        {
            if (_size == 0)
                throw std::out_of_range("out of range");
            _alloc.destroy(_data + _size - 1);
            --_size;
        };

        void clear()
        {
            for (size_type i = 0; i < _size; ++i)
                _alloc.destroy(_data + i);
            _size = 0;
        };

        void resize(size_type n, value_type val = value_type())
        {
            if (n > _capacity)
                reserve(n);
            if (n > _size)
            {
                for (size_type i = _size; i < n; ++i)
                    _alloc.construct(_data + i, val);
            }
            else if (n < _size)
            {
                for (size_type i = n; i < _size; ++i)
                    _alloc.destroy(_data + i);
            }
            _size = n;
        };
        // insert single element
        iterator insert(const_iterator position, const T &val)
        {

            for (size_type i = _size; i > position - begin(); i--)
            {
                // std::cout << "here \n";
                _alloc.construct(&_data[i], _data[i - 1]);
            }
            _alloc.construct(&_data[position - begin()], val);
            _size++;
            return iterator(position);
        };

        //  insert Inserts a new element at position n in the vector, shifting the element at position n and those after it to the right.
        void insert(iterator position, size_type n, const T &val)
        {
            _capacity += n;
            _size += n;
            for (size_type i = _size; i > position - begin(); i--)
            {
                _alloc.construct(&_data[i], _data[i - n]);
            }
            for (size_type i = 0; i < n; i++)
            {
                _alloc.construct(&_data[position - begin() + i], val);
            }
        };

        // insert range
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last,
                    typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
        {
            size_type n = last - first;
            _capacity += n;
            _size += n;
            for (size_type i = _size; i > position - begin(); i--)
            {
                _alloc.construct(&_data[i], _data[i - n]);
            }
            for (size_type i = 0; i < n; i++)
            {
                _alloc.construct(&_data[position - begin() + i], *(first + i));
            }
        };

        // erase single element
        iterator erase(iterator position)
        {
            for (size_type i = position - _data; i < _size - 1; ++i)
                _alloc.construct(_data + i, _data[i + 1]);
            _alloc.destroy(_data + _size - 1);
            --_size;
            return position;
        };

        // assign
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            clear();
            for (; first != last; ++first)
                push_back(*first);
        }

        void assign(size_type n, const T &val)
        {
            clear();
            for (size_type i = 0; i < n; ++i)
                push_back(val);
        }

        // erase range
        iterator erase(iterator first, iterator last)
        {
            for (size_type i = first - _data; i < _size - (last - first); ++i)
                _alloc.construct(_data + i, _data[i + (last - first)]);
            for (size_type i = 0; i < last - first; ++i)
                _alloc.destroy(_data + _size - (last - first) + i);
            _size -= last - first;
            return first;
        };
        void swap(vector &v)
        {
            ft::swap(_data, v._data);
            ft::swap(_size, v._size);
            ft::swap(_capacity, v._capacity);
        };

        // flip
        void flip()
        {
            for (size_type i = 0; i < _size; ++i)
            {
                _data[i] = !_data[i];
            }
        };
    };
    // relational operators
    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        for (size_t i = 0; i < lhs.size(); ++i)
            if (lhs[i] != rhs[i])
                return false;
        return true;
    }
    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }
    template <class T, class Alloc>
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        if (lhs.size() < rhs.size())
            return true;
        else if (lhs.size() > rhs.size())
            return false;
        for (size_t i = 0; i < lhs.size(); ++i)
            if (lhs[i] < rhs[i])
                return true;
            else if (lhs[i] > rhs[i])
                return false;
        return false;
    }
    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return rhs < lhs;
    }
    template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return !(lhs > rhs);
    }
    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }
    // swap

    template <class T, class Alloc>
    void swap(vector<T, Alloc> &lhs, vector<T, Alloc> &rhs)
    {
        vector<T, Alloc> tmp(lhs);
        lhs = rhs;
        rhs = tmp;
    }

}
#endif
