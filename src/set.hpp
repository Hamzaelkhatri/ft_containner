#ifndef SET_HPP
#define SET_HPP

#include "iterators.hpp"
#include "iter_bool.hpp"
#include "rbt_set.hpp"


namespace ft
{
    template <class T,                        // set::key_type/value_type
              class Compare = std::less<T>,   // set::key_compare/value_compare
              class Alloc = std::allocator<T> // set::allocator_type
              >
    class set
    {
    public:
        typedef T key_type;
        typedef T value_type;
        typedef Compare key_compare;
        typedef Compare value_compare;
        typedef Alloc allocator_type;
        typedef typename Alloc::reference reference;
        typedef typename Alloc::const_reference const_reference;
        typedef typename Alloc::pointer pointer;
        typedef typename Alloc::const_pointer const_pointer;
        typedef ft::RBT<value_type, Compare, Alloc> tree;
        typedef typename tree::iterator iterator;
        typedef typename tree::const_iterator const_iterator;
        typedef typename tree::reverse_iterator reverse_iterator;
        typedef typename tree::const_reverse_iterator const_reverse_iterator;
        typedef typename tree::node_allocator allocator_types;
        typedef typename Alloc::size_type size_type;
        typedef typename tree::NodePtr NodePtr;

    private:
        tree _tree;
        allocator_types _alloc_;
        key_compare _comp;
        size_type _size;

    public:
        // constructors
        set() : _tree(), _alloc_(), _comp() { _size = 0; }
        explicit set(const key_compare &comp, const allocator_type &alloc = allocator_type()) : _alloc_(alloc), _comp(comp) { _size = 0; }
        template <class InputIterator>
        set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _alloc_(alloc), _comp(comp)
        {
            while (first != last)
            {
                _tree.insert_(*first);
                ++first;
            }
            _size = _tree.size;
        }
        set(const set &x) : _alloc_(x._alloc_), _comp(x._comp)
        {
            if (this != &x)
            {
                _tree.~RBT();
                _tree = x._tree;
                _size = x._size;
            }
        }

        // iterators
        iterator begin() { return _tree.begin(); }
        const_iterator begin() const { return _tree.begin(); }
        iterator end() { return _tree._end_(); }
        const_iterator end() const { return _tree.end(); }
        reverse_iterator rbegin() { return _tree.rbegin(); }
        const_reverse_iterator rbegin() const { return _tree.rbegin(); }
        reverse_iterator rend() { return _tree.rend(); }

        // // capacity
        bool empty() const { return _tree.empty(); }
        size_type size() const { return _tree.size; }
        size_t max_size() const
        {
            return _alloc_.max_size();
        }
        // insert
        iterator insert(iterator position, const value_type &x)
        {
            (void)position;
            _tree.insert_(x);
            _size = x._size;
            return _tree.find(x);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            while (first != last)
            {
                _tree.insert_(*first);
                ++first;
            }
            _size = _tree.size;
        }

        ft::pair<iterator, bool> insert(const value_type &val)
        {
            if (_tree.find(val) == end())
            {
                _tree.insert_(val);
                return ft::pair<iterator, bool>(_tree.find(val), true);
            }
            _size = _tree.size;
            return ft::pair<iterator, bool>(_tree.find(val), false);
        }

        void erase(iterator position)
        {
            _tree.erase(*position);
            _size = _tree.size;
        }

        size_type erase(const key_type &x)
        {

            _tree.erase(x);
            _size = _tree.size;
            return this->count(x) ? 0 : 1;
        }

        void erase(iterator first, iterator last)
        {
            while (first != last)
            {
                _tree.erase(*first);
                ++first;
            }
            _size = _tree.size;
        }

        void clear()
        {
            _tree.makeEmpty();
            _size = 0;
        }
        // lookup
        iterator find(const key_type &x) { return _tree.find(x); }
        const_iterator find(const key_type &x) const { return _tree.find(x); }
        size_type count(const key_type &x) const { return _tree.count(x); }
        iterator lower_bound(const key_type &x) { return _tree.lower_bound(x); }
        const_iterator lower_bound(const key_type &x) const { return _tree.lower_bound(x); }
        iterator upper_bound(const key_type &x) { return _tree.upper_bound(x); }
        const_iterator upper_bound(const key_type &x) const { return _tree.upper_bound(x); }
        pair<iterator, iterator> equal_range(const key_type &x) { return _tree.equal_range(x); }
        pair<const_iterator, const_iterator> equal_range(const key_type &x) const { return _tree.equal_range(x); }
        // comparison
        key_compare key_comp() const { return _comp; }
        value_compare value_comp() const { return _comp; }
        // operations
        void swap(set &x)
        {
            if (this != &x)
            {
                _tree.swap(x._tree);
                std::swap(_alloc_, x._alloc_);
                std::swap(_comp, x._comp);
                std::swap(_size, x._size);
            }
        }

        set &operator=(const set &x)
        {
            if (this != &x)
            {
                _tree.~RBT();
                _tree = x._tree;
                _alloc_ = x._alloc_;
                _comp = x._comp;
                _size = x._size;
            }
            return *this;
        }

        // get_allocator
        allocator_type get_allocator() const { return _alloc_; }
    };
}

#endif