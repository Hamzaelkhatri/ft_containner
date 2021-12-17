// re-build a  map<T t, T t> containner like c++

#ifndef MAP_HPP
#define MAP_HPP

#include "iterators.hpp"
#include "iter_bool.hpp"

enum Color
{
    RED,
    BLACK
};
// structs for RED-BLACK tree
struct Node
{
    int key;
    Node *left, *right;
    int color;
    std::string value;
    // constructor
    Node(int k, std::string v)
    {
        key = k;
        value = v;
        left = right = NULL;
        color = RED;
    }
};

namespace ft
{

    template <class Key,                                             // map::key_type
              class T,                                               // map::mapped_type
              class Compare = std::less<Key>,                        // map::key_compare
              class Alloc = std::allocator<ft::pair<const Key, T> > // map::allocator_type
              >
    class map
    {
        // member types
    private:
        // create   comp_,alloc_ c++98
        Compare comp_;
        Alloc alloc_;
        // create   root_ c++98
        Node *root_;
        // create   size_ c++98
        size_t size_;

        void clear()
        {
            if (root_ == NULL)
                return;
            clear(root_->left);
            clear(root_->right);
            delete root_;
            root_ = NULL;
        }

        // begin
        Node *Nodebegin()
        {
            Node *tmp = root_;
            while (tmp->left != NULL)
                tmp = tmp->left;
            return tmp;
        }

    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef pair<const Key, T> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename allocator_type::iterator iterator;
        typedef typename allocator_type::const_iterator const_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        // member functions
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type())
            : comp_(comp), alloc_(alloc)
        {
        }
        map(const map &x)
            : comp_(x.comp_), alloc_(x.alloc_)
        {
            copy(x.begin(), x.end(), Nodebegin());
        }

        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
            : comp_(comp), alloc_(alloc)
        {
            copy(first, last, Nodebegin());
        }

        // destructor
        ~map()
        {
            clear();
        }

        map &operator=(const map &x)
        {
            if (this != &x)
            {
                // clear the tree
                clear();
                copy(x.begin(), x.end(), begin());
            }
            return *this;
        }

        // Iterators:
        iterator begin()
        {
            return iterator(begin(root_));
        }

        const_iterator begin() const
        {
            return const_iterator(begin(root_));
        }

        iterator end()
        {
            return iterator(NULL);
        }

        const_iterator end() const
        {
            return const_iterator(NULL);
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }

        // Capacity :
        bool empty() const
        {
            return size_ == 0;
        }

        size_type size() const
        {
            return size_;
        }

        // max_size()
        size_type max_size() const
        {
            return size_type(-1);
        }

        // Element access:
        mapped_type &operator[](const key_type &k)
        {
            return insert(value_type(k, mapped_type())).first->second;
        }

        // insert
        // ft::pair<ft::iterator, bool> insert(const value_type &x)
        // {
        //     return insert_unique(x);
        // }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
                insert(*first);
        }

        iterator insert(iterator position, const value_type &val)
        {
            return insert_unique(position, val);
        }

        // insert_unique

        // erase
        size_type erase(const key_type &k)
        {
            return erase_unique(k);
        }

        void erase(iterator position)
        {
            erase_unique(position.node_);
        }

        void erase(iterator first, iterator last)
        {
            for (; first != last; ++first)
                erase_unique(first.node_);
        }

        void swap(map &x)
        {
            ft::swap(root_, x.root_);
            ft::swap(size_, x.size_);
            ft::swap(comp_, x.comp_);
            ft::swap(alloc_, x.alloc_);
        }

        // find
        iterator find(const key_type &k)
        {
            return iterator(find_unique(k));
        }

        const_iterator find(const key_type &k) const
        {
            return const_iterator(find_unique(k));
        }

        // count
        size_type count(const key_type &k) const
        {
            return find_unique(k) == NULL ? 0 : 1;
        }

        // lower_bound
        iterator lower_bound(const key_type &k)
        {
            return iterator(lower_bound_unique(k));
        }

        const_iterator lower_bound(const key_type &k) const
        {
            return const_iterator(lower_bound_unique(k));
        }

        // upper_bound
        iterator upper_bound(const key_type &k)
        {
            return iterator(upper_bound_unique(k));
        }

        const_iterator upper_bound(const key_type &k) const
        {
            return const_iterator(upper_bound_unique(k));
        }

        // equal_range
        ft::pair<iterator, iterator> equal_range(const key_type &k)
        {
            return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
        }

        ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
        }

        // get_allocator
        allocator_type get_allocator() const
        {
            return alloc_;
        }
    };
}
#endif