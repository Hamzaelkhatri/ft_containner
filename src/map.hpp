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
              class Alloc = std::allocator<ft::pair<Key, T> > >
    class map
    {

    public:
        typedef Key key;
        typedef T mapped_type;
        typedef ft::pair<key, mapped_type> value_type;
        typedef Compare key_compare;
        // typedef Alloc allocator_type;
        // typedef typename allocator_type::reference reference;
        // typedef typename allocator_type::const_reference const_reference;
        // typedef typename allocator_type::pointer pointer;
        // typedef typename allocator_type::const_pointer const_pointer;
        // typedef RBT<key, mapped_type, Compare, Alloc> tree_type;
        // typedef typename tree_type::iterator iterator;
        // typedef typename tree_type::const_iterator const_iterator;
        // typedef typename tree_type::reverse_iterator reverse_iterator;
        // typedef typename tree_type::const_reverse_iterator const_reverse_iterator;
        // typedef typename tree_type::difference_type difference_type;
        // typedef typename ft::Node<key, mapped_type> Node;
        // typedef ft::Node<key, mapped_type> *NodePtr;
        typedef ft::RBT<value_type, Compare, Alloc> tree;
        typedef typename tree::iterator iterator;
        typedef typename tree::const_iterator const_iterator;
        typedef typename tree::reverse_iterator reverse_iterator;
        typedef typename tree::const_reverse_iterator const_reverse_iterator;
        typedef typename tree::difference_type difference_type;
        typedef typename tree::node_allocator allocator_type;
        


        typedef size_t size_type;

    private:
        tree _tree;
        allocator_type _alloc;
        key_compare _comp;

    public:
        class value_compare
        {
        protected:
            Compare _comp;

        public:
            value_compare(Compare c) : _comp(c) {}
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            result_type operator()(const first_argument_type &x, const second_argument_type &y) const
            {
                return _comp(x.first, y.first);
            }
        };

        // constructors
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type()) : _comp(comp), _alloc(alloc)
        {
        }
        map(const map &other)
        {
            _comp = other._comp;
            _alloc = other._alloc;
            _tree = other._tree;
        }
        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
            : _tree(comp, alloc)
        {
            _tree.insert_(ft::make_pair(first, last));
        }

        // insert
        void insert(const value_type &x)
        {
            _tree.insert_(x);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            _tree.insert_(ft::make_pair(first, last));
        }

        void print()
        {
            _tree.printTree();
        }

        // erase
        void erase(iterator position)
        {
             _tree.erase(position);
        }

        size_type erase(const key &x)
        {
            return _tree.erase(ft::pair<key, mapped_type>(x, mapped_type()));
        }

        void erase(iterator first, iterator last)
        {
            _tree.erase(first, last);
        }

        // find
        iterator find(const key &x)
        {
            return _tree.find(ft::pair<key, mapped_type>(x, mapped_type()));
        }


        // size
        size_type size() const
        {
            return _tree.size();
        }

        // empty
        bool empty() const
        {
            return _tree.empty();
        }

        // swap
        void swap(map &other)
        {
            _tree.swap(other._tree);
        }

        // clear
        void clear()
        {
            _tree.clear();
        }

        // key_comp
        key_compare key_comp() const
        {
            return _comp;
        }

        // value_comp
        value_compare value_comp() const
        {
            return value_compare(_comp);
        }

        // operator[]
        mapped_type &operator[](const key &x)
        {
            return _tree.find(ft::pair<key, mapped_type>(x, mapped_type()))->second;
        }

        // at
        mapped_type &at(const key &x)
        {
            return _tree.find(ft::pair<key, mapped_type>(x, mapped_type()))->second;
        }

        // begin
        iterator begin()
        {
            return _tree.begin();
        }

        // end
        iterator end()
        {
            return _tree._end_();
        }

        // rbegin
        reverse_iterator rbegin()
        {
            return _tree.rbegin();
        }

        // rend
        reverse_iterator rend()
        {
            return _tree.rend();
        }

        // const_begin
        const_iterator begin() const
        {
            return _tree.begin();
        }

        // const_end
        const_iterator end() const
        {
            return _tree.end();
        }

        // const_rbegin
        const_reverse_iterator rbegin() const
        {
            return _tree.rbegin();
        }

        // const_rend
        const_reverse_iterator rend() const
        {
            return _tree.rend();
        }

        // count
        size_type count(const key &x) const
        {
            return _tree.count(ft::pair<key, mapped_type>(x, mapped_type()));
        }

        // lower_bound
        iterator lower_bound(const key &x)
        {
            return _tree.lower_bound(ft::pair<key, mapped_type>(x, mapped_type()));
        }

        // upper_bound
        iterator upper_bound(const key &x)
        {
            return _tree.upper_bound(ft::pair<key, mapped_type>(x, mapped_type()));
        }

        // equal_range
        ft::pair<iterator, iterator> equal_range(const key &x)
        {
            return _tree.equal_range(ft::pair<key, mapped_type>(x, mapped_type()));
        }

        // const_lower_bound
        const_iterator lower_bound(const key &x) const
        {
            return _tree.lower_bound(ft::pair<key, mapped_type>(x, mapped_type()));
        }

        // const_upper_bound
        const_iterator upper_bound(const key &x) const
        {
            return _tree.upper_bound(ft::pair<key, mapped_type>(x, mapped_type()));
        }

        // const_equal_range
        ft::pair<const_iterator, const_iterator> equal_range(const key &x) const
        {
            return _tree.equal_range(ft::pair<key, mapped_type>(x, mapped_type()));
        }

        // allocator
        allocator_type get_allocator() const
        {
            return _alloc;
        }
        
        
        // operator=
        map &operator=(const map &other)
        {
            _comp = other._comp;
            _alloc = other._alloc;
            _tree = other._tree;
            return *this;
        }

    };
};
#endif