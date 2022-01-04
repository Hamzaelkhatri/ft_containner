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
        pointer _data;
        size_type _size;
        size_type _capacity;
        allocator_type _alloc;

    public:
        vector(const allocator_type &_alloc = allocator_type()) : _data(nullptr), _size(0), _capacity(0), _alloc(_alloc)
        {
        }
        /* fill */
        vector(size_type _n, const value_type &_val = value_type(),
               const allocator_type &_alloc = allocator_type()) : _data(nullptr), _size(0), _capacity(0), _alloc(_alloc)
        {
            this->assign(_n, _val);
        }
        /* range */
        template <class InputIterator>
        vector(InputIterator first, InputIterator last,
               const allocator_type &_alloc = allocator_type(),
               typename enable_if<!is_integral<InputIterator>::value, bool>::type = true) : _data(nullptr), _size(0), _capacity(0), _alloc(_alloc)
        {
            this->assign(first, last);
        }
        /* copy */
        vector(const vector &v) : _data(nullptr), _size(0),
                                  _capacity(0), _alloc(v._alloc)
        {
            *this = v;
        }
        // destructor
        ~vector()
        {
            for (size_type i = 0; i < _size; ++i)
                _alloc.destroy(_data + i);
            _alloc.deallocate(_data, this->capacity());
            this->_capacity = 0;
        }
        // operator overloads
        vector &operator=(const vector &v)
        {
            if (this != &v)
            {
                this->clear();
                this->_alloc.deallocate(this->_data, this->capacity());
                this->_size = v._size;
                this->_capacity = v._capacity;
                this->_data = _alloc.allocate(this->capacity());
                for (size_type _i = 0; _i < _size; _i++)
                    this->_alloc.construct(&this->_data[_i], v._data[_i]);
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
                size_type oldCapacity = this->_capacity;
                if (this->_capacity * 2 >= n)
                    this->_capacity *= 2;
                else
                    this->_capacity = n;
                pointer tmp = _alloc.allocate(this->_capacity);
                for (size_type i = 0; i < _size; ++i)
                    _alloc.construct(tmp + i, _data[i]);
                for (size_type i = 0; i < _size; ++i)
                    _alloc.destroy(_data + i);
                _alloc.deallocate(_data, oldCapacity);
                _data = tmp;
            }
            else
                return;
        }

        // get_allocator
        allocator_type get_allocator() const { return _alloc; }
        // max_size
        size_type max_size() const
        {
            return (std::min(_alloc.max_size(), std::numeric_limits<size_type>::max()));
        }
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
            this->reserve(this->_size + 1);
            this->_alloc.construct(&this->_data[this->_size++], val);
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
            if (size() > 0)
            {
                for (size_type _i = 0; _i < this->size(); _i++)
                    this->_alloc.destroy(&this->_data[_i]);
                this->_size = 0;
            }
        };

        void resize(size_type n, value_type val = value_type())
        {
            size_type _sz = size();
            if (_sz > n)
            {
                for (size_type _i = n - 1; _i < _sz; _i++)
                    this->_alloc.destroy(&this->_data[_i]);
                this->_size = n;
            }
            else if (_sz < n)
            {
                this->reserve(n);
                this->_size = n;
                for (size_type _i = _sz; _i < n; _i++)
                    this->_alloc.construct(&this->_data[_i], val);
            }
        };
        // insert single element
        iterator insert(iterator position, const value_type &_val)
        {
            difference_type _idx = position - begin();
            if (_idx < 0)
                throw std::out_of_range("vector");
            this->reserve(this->_size + 1);
            this->_size += 1;
            difference_type diff = size();
            while (--diff >= 0)
            {
                if (diff == _idx)
                {
                    this->_alloc.construct(&this->_data[diff], _val);
                    break;
                }
                this->_alloc.construct(&this->_data[diff], this->_data[diff - 1]);
            }
            return (iterator(this->_data + _idx));
        }
        void insert(iterator position, size_type n, const value_type &_val)
        {
            if (n <= 0)
                return;
            difference_type _idx = position - begin();
            if (_idx < 0)
                return;
            this->reserve(size() + n);
            this->_size += n;
            difference_type diff = size();
            while (--diff >= 0)
            {
                if (diff == (_idx + (difference_type)n) - 1)
                {
                    _alloc.construct(&this->_data[diff], _val);
                    n--;
                }
                else
                    _alloc.construct(&this->_data[diff], this->_data[diff - n]);
                if (diff == _idx)
                    break;
            }
        }
        // insert range
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last,
                    typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
        {
            difference_type n = last - first;
            if (n <= 0)
                return;
            difference_type idx = position - begin();
            if (idx < 0)
                throw std::out_of_range("vector");
            this->reserve(this->_size + n);
            this->_size += n;
            for (difference_type i = _size; i > idx; i--)
            {
                _alloc.construct(&_data[i], _data[i - n]);
            }
            for (difference_type i = 0; i < n; i++)
            {
                _alloc.construct(&_data[idx + i], *(first + i));
            }
        };

        // erase single element
        iterator erase(iterator position)
        {
            difference_type idx = position - begin();
            if (idx < 0)
                throw std::out_of_range("vector");
            _alloc.destroy(_data + idx);
            for (size_type i = idx; i < _size; ++i)
                _alloc.construct(_data + i, _data[i + 1]);
            --_size;
            return (iterator(this->_data + idx));
        };

        // assign
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last,
                    typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
        {
            difference_type ranglen = last - first;
            if (ranglen <= 0)
                return;
            this->reserve(ranglen);
            this->_size = ranglen;
            for (size_type i = 0; i < this->_size; i++)
            {

                _alloc.construct(_data + i, *(first + i));
            }
        }

        void assign(size_type n, const T &val)
        {
            if (!n)
                return;
            this->reserve(n);
            this->_size = n;
            for (size_type i = 0; i < this->_size; i++)
            {
                this->_alloc.construct(_data + i, val);
            }
        }

        // erase range
        iterator erase(iterator first, iterator last)
        {
            if (last - first < 0)
                throw std::out_of_range("vector");
            for (size_type i = first - _data; i < _size - (last - first); ++i)
                _alloc.construct(_data + i, _data[i + (last - first)]);
            for (difference_type i = 0; i < last - first; ++i)
                _alloc.destroy(_data + _size - (last - first) + i);
            _size -= last - first;
            return iterator(this->_data + (last - first));
        };
        void swap(vector &v)
        {
            std::swap(_data, v._data);
            std::swap(_size, v._size);
            std::swap(_capacity, v._capacity);
        };
    };
    // relational operators
    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }
    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }
    template <class T, class Alloc>
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
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
        lhs.swap(rhs);
    }

}
#endif