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
              class Alloc = std::allocator<ft::pair<const Key, T>>>
    class map
    {
    private:
        ft::RBT<Key, T, Compare, Alloc> _tree;
        ft::RBT<Key, T, Compare, Alloc> _root;
        Compare _comp;
        Alloc _alloc;

    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef std::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef typename ft::Node<key_type, mapped_type> node;
        typedef typename Alloc::template rebind<node>::other allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef ft::RBT<pointer, value_type> iterator;
        typedef ft::RBT<pointer, const value_type> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
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
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;

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
            _tree.insert(std::make_pair(first, last));
        }

        // insert
        void insert(const value_type &x)
        {
            _tree.insert(x);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            _tree.insert(first, last);
        }

        void print()
        {
            _tree.printTree();
        }
    };
};
#endif