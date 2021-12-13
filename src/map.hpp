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
              class Alloc = std::allocator<std::pair<const Key, T> > // map::allocator_type
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
        Node *begin()
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
            copy(x.begin(), x.end(), begin());
        }

        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
            : comp_(comp), alloc_(alloc)
        {
            copy(first, last, begin());
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
    };
}
#endif