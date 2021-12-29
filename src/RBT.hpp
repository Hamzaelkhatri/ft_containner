#ifndef RBT_HPP
#define RBT_HPP

#include <iostream>
#include <fstream>
#include <utility>
#include "iterators.hpp"
#include "iter_bool.hpp"
#include <limits>
// Red-Black Tree class
//
// CONSTRUCTION: with (a) no parameters
//
//  ******************PUBLIC OPERATIONS*********************
//  void insert( x )       --> Insert x
//  void remove( x )       --> Remove x (unimplemented)
//  bool contains( x )     --> Return true if x is present
//  Compare findMin( )  --> Return smallest item
//  Comparable findMax( )  --> Return largest item
//  boolean isEmpty( )     --> Return true if empty; else false
//  void makeEmpty( )      --> Remove all items
//  void printTree( )      --> Print tree in sorted order
//
//  ******************ERRORS********************************
//  Throws UnderflowException as warranted

// Class template
namespace ft
{

    enum Color
    {
        RED,
        BLACK
    };

    template <class T>
    struct Node
    {
        T _data;
        Node *left;   // Left child
        Node *right;  // Right child
        Node *parent; // Parent
        int height;   // Height
        int color;    //

        // default constructor
        Node()
        {
            left = right = parent = NULL;
            height = 1;
            color = BLACK;
        }

        // constructor
        Node(T data)
        {
            _data = data;
            left = right = parent = NULL;
            height = 1;
            color = BLACK;
        }
    };

    // create a iteratorClass for RBT
    template <class RBT, class Iter, class T>
    class RBT_iter : public std::iterator<std::bidirectional_iterator_tag,
                                          typename iterator_traits<T>::value_type>
    {
    public:
        typedef Iter iterator_type;
        typedef RBT rbt;
        typedef typename iterator_traits<T>::pointer pointer;
        typedef typename iterator_traits<T>::reference reference;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
        iterator_type *it;
        rbt rbt_;

    public:
        RBT_iter() : it(), rbt_()
        {
        }

        RBT_iter(iterator_type *_x, rbt _tr) : it(_x), rbt_(_tr)
        {
        }

        template <class OthTree, class OthIter, class U>
        RBT_iter(const RBT_iter<OthTree, OthIter, U> &_other) : it(_other.it), rbt_(_other.rbt_)
        {
        }

        template <class OthTree, class OthIter, class U>
        RBT_iter &operator=(const RBT_iter<OthTree, OthIter, U> &_other)
        {
            this->it = _other.base();
            this->rbt_ = _other.get_rbt();
            return (*this);
        }

        reference operator*() const
        {
            return it->_data;
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        RBT_iter &operator++()
        {
            it = rbt_->successor(it);
            return *this;
        }

        RBT_iter operator++(int)
        {
            RBT_iter tmp(*this);
            it = rbt_->successor(it);
            return tmp;
        }

        // <<
        // template <class OthTree, class OthIter, class U>
        // friend std::ostream &operator<<(std::ostream &_os, const RBT_iter<OthTree, OthIter, U> &_other)
        // {
        //     _os << _other.it->_data;
        //     return _os;
        // }

        RBT_iter &operator--()
        {
            it = rbt_->predecessor(it);
            return *this;
        }

        RBT_iter operator--(int)
        {
            RBT_iter tmp(*this);
            it = rbt_->predecessor(it);
            return tmp;
        }

        bool operator==(const RBT_iter &rbt_iter) const
        {
            return it == rbt_iter.it;
        }

        bool operator!=(const RBT_iter &rbt_iter) const
        {
            return it != rbt_iter.it;
        }

        iterator_type get_iterator() const
        {
            return it;
        }

        rbt get_rbt() const
        {
            return rbt_;
        }
    };

    template <class T,                         // map::mapped_type
              class Compare,                   // map::key_compare
              class Alloc = std::allocator<T>> // map::allocator_type
    class RBT
    {

    public:
        typedef T value_type;
        typedef struct Node<value_type> Node_;
        typedef typename Alloc::template rebind<Node_>::other node_allocator;
        typedef typename Alloc::pointer pointer;
        typedef typename Alloc::const_pointer const_node_pointer;
        typedef typename Alloc::reference node_reference;
        typedef typename Alloc::const_reference const_node_reference;
        size_t size_type;
        typedef typename Alloc::difference_type difference_type;
        typedef struct Node<value_type> *NodePtr;
        typedef RBT *self;
        typedef ft::RBT_iter<self, Node_, pointer> iterator;
        typedef ft::RBT_iter<self, Node_, pointer> const_iterator;
        typedef typename ft::reverse_iterator<iterator> reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

    public:
        Node_ *root;
        Node_ *end;
        Node_ *nil;
        int size;
        node_allocator alloc;
        int height;
        Compare comp;

        Node_ *grandparent(Node_ *n)
        {
            if (n == NULL || n->parent == NULL || n == nil || n->parent == end)
                return nil;
            return n->parent->parent;
        }

        Node_ *
        uncle(Node_ *n)
        {
            Node_ *g = grandparent(n);
            if (g == nil)
                return nil;
            if (n->parent == g->left)
                return g->right;
            else
                return g->left;
        }

        void
        updateHeight(Node_ *n)
        {
            int hl = (n->left == nil) ? 0 : n->left->height;
            int hr = (n->right == nil) ? 0 : n->right->height;
            n->height = (hl > hr ? hl : hr) + 1;
        }

        void rotateLeft(Node_ *n)
        {
            Node_ *r = n->right;
            n->right = r->left;
            if (r->left != nil)
                r->left->parent = n;
            r->parent = n->parent;
            if (n->parent == end)
                root = r;
            else if (n == n->parent->left)
                n->parent->left = r;
            else
                n->parent->right = r;
            r->left = n;
            n->parent = r;
            updateHeight(n);
            updateHeight(r);
        }

        void rotateRight(Node_ *n)
        {
            Node_ *l = n->left;
            n->left = l->right;
            if (l->right != nil)
                l->right->parent = n;
            l->parent = n->parent;
            if (n->parent == NULL)
                root = l;
            else if (n == n->parent->left)
                n->parent->left = l;
            else
                n->parent->right = l;
            l->right = n;
            n->parent = l;
            updateHeight(n);
            updateHeight(l);
        }

        void doublerotateLeft(Node_ *n)
        {
            rotateRight(n->right);
            rotateLeft(n);
        }

        void doublerotateRight(Node_ *n)
        {
            rotateLeft(n->left);
            rotateRight(n);
        }

        void makeEmpty(Node_ *n)
        {
            if (n == nil || n == end || n == NULL)
                return;
            // makeEmpty(n->left);
            // makeEmpty(n->right);
            //  if (n == nil || n == end || n == NULL)
            //     return;
            // alloc.destroy(n);
            alloc.destroy(n);
        }

        Node_ *getRootOfTree()
        {
            return root;
        }

        // insertFixup
        void
        insertFixup(Node_ *n)
        {
            while (n && n != root && n->parent->color == RED)
            {
                if (n->parent == n->parent->parent->left)
                {
                    Node_ *u = n->parent->parent->right;
                    if (u && u->color == RED)
                    {
                        n->parent->color = BLACK;
                        u->color = RED;
                        n->parent->parent->color = RED;
                        n = n->parent->parent;
                    }
                    else
                    {
                        if (n == n->parent->right)
                        {
                            n = n->parent;
                            rotateLeft(n);
                        }
                        n->parent->color = BLACK;
                        n->parent->parent->color = RED;
                        rotateRight(n->parent->parent);
                    }
                }
                else
                {
                    Node_ *u = n->parent->parent->left; // uncle
                    // check if Node_ is not empty
                    if (u && u->color == RED)
                    {
                        n->parent->color = BLACK;
                        u->color = BLACK;
                        n->parent->parent->color = RED;
                        n = n->parent->parent;
                    }
                    else
                    {
                        if (n == n->parent->left)
                        {
                            n = n->parent;
                            rotateRight(n);
                        }
                        n->parent->color = BLACK;
                        n->parent->parent->color = RED;
                        rotateLeft(n->parent->parent);
                    }
                }
            }
            root->color = BLACK;
        }

        int cout_left_height()
        {
            int count = 0;
            Node_ *temp = root;
            while (temp->left != nil)
            {
                temp = temp->left;
                if (temp->color == BLACK)
                    count++;
                count++;
            }
            return count + 1;
        }


        int cout_right_height()
        {
            int count = 0;
            Node_ *temp = root;
            while (temp->right != nil)
            {
                temp = temp->right;
                if (temp->color == BLACK)
                    count++;
            }
            return count + 1;
        }

        void insert(Node_ *n) // 1 ---->
        {
            Node_ *y = nil;
            Node_ *x = root;

            while (x != nil)
            {
                y = x;
                if (comp(n->_data.first, x->_data.first))
                    x = x->left;
                else
                    x = x->right;
            }
            n->parent = y;
            if (y == nil)
            {
                root = n;
                n->color = BLACK;
            }
            else
            {
                if (comp(n->_data.first, x->_data.first) == true)
                    y->left = n;
                else
                    y->right = n;
                n->color = RED;
            }
            n->height = 1;
            n->left = n->right = nil;
            insertFixup(n);
            root->parent = end;
            end->left = root;
        }

        void printTree(Node_ *n)
        {
            // print tree with details
            if (n == nil || !n)
                return;
            printTree(n->left);
            std::cout << "adrs of node " << n << " Key: " << n->_data.first << " Color: " << (n->color == 0 ? "RED" : "BLACK") << " Height: " << n->height << " Parent: " << (n->parent == NULL ? "\033[0;31mROOT " : "CHILD ") << "\033[0mLeft: " << (n->left != nil ? std::to_string(n->left->_data.first) : "nil") << " Right: " << (n->right != nil ? std::to_string(n->right->_data.first) : "nil") << std::endl;
            printTree(n->right);
        }

        int isRBProper(Node_ *n)
        {
            if (n == nil)
                return 1;
            if (n->color == RED && ((n->left != nil && n->left->color == RED) || (n->right != nil && n->right->color == RED)))
            {
                // print details
                std::cout << "adrs of node " << n << " Node_: " << n->_data.first << " Color: " << (n->color == 0 ? "RED" : "BLACK") << " Height: " << n->height << " Parent: " << (n->parent == NULL ? "\033[0;31mROOT\033[0m" : "CHILD ") << " Left: " << (n->left != nil ? std::to_string(n->left->_data.first) : "nil") << " Right: " << (n->right != nil ? std::to_string(n->right->_data.first) : "nil") << std::endl;
                return 0;
            }
            return isRBProper(n->left) && isRBProper(n->right);
        }

        //  deleteFixup
        // void deleteFixup(Node_ *n)
        // {
        //     insertFixup(n);
        // }

        // transplant
        void transplant(Node_ *u, Node_ *v)
        {
            if (!u->parent || u->parent == end)
                root = v;
            else if (u == u->parent->left)
                u->parent->left = v;
            else
                u->parent->right = v;
            if (v)
                v->parent = u->parent;
        }

        // treeMinimum
        Node_ *treeMinimum(Node_ *n)
        {
            while (n && n->left != nil && n->left != NULL)
                n = n->left;
            return n;
        }

        void
        deleteFixup(Node_ *x)
        {
            Node_ *tmp;

            while (x && x != root && x->color == BLACK)
            {
                if (x == x->parent->left)
                {
                    tmp = x->parent->right;
                    if (tmp->color == RED)
                    {
                        tmp->color = BLACK;
                        x->parent->color = RED;
                        rotateLeft(x->parent);
                        tmp = x->parent->right;
                    }
                    if ((tmp && (tmp->left->color == BLACK && tmp->right->color == BLACK)) || (tmp->left == NULL && tmp->right == NULL))
                    {
                        tmp->color = RED;
                        x = x->parent;
                    }
                    else
                    {
                        if (tmp->right->color == BLACK)
                        {
                            tmp->left->color = BLACK;
                            tmp->color = RED;
                            rotateRight(tmp);
                            tmp = x->parent->right;
                        }
                        tmp->color = x->parent->color;
                        x->parent->color = BLACK;
                        tmp->right->color = BLACK;
                        rotateLeft(x->parent);
                        x = root;
                    }
                }
                else
                {
                    tmp = x->parent->left;
                    if (tmp->color == RED)
                    {
                        tmp->color = BLACK;
                        x->parent->color = RED;
                        rotateRight(x->parent);
                        tmp = x->parent->left;
                    }
                    if ((tmp && (tmp->left->color == BLACK && tmp->right->color == BLACK)) || (tmp->left == NULL && tmp->right == NULL))
                    {
                        tmp->color = RED;
                        x = x->parent;
                    }
                    else
                    {
                        if (tmp->left->color == BLACK)
                        {
                            tmp->right->color = BLACK;
                            tmp->color = RED;
                            rotateLeft(tmp);
                            tmp = x->parent->left;
                        }
                        tmp->color = x->parent->color;
                        x->parent->color = BLACK;
                        tmp->left->color = BLACK;

                        rotateRight(x->parent);
                        x = root;
                    }
                }
            }
            x->color = BLACK;
        }

    public:
        RBT()
        {
            // use alloc to allocate memory for the root node
            nil = alloc.allocate(1);
            nil->color = BLACK;
            nil->right = NULL;
            root = nil;
            height = 1;
            end = alloc.allocate(1);
            end->left = root;
            end->right = end;
            end->parent = end;
            end->color = BLACK;
            size = 0;
            end->height = 1;
            root->parent = end;
            end->left = root;
            nil->left = root;
        }
        RBT(const RBT<value_type, Compare> &rhs)
        {
            nil = alloc.allocate(1);
            root = nil;
            root->color = BLACK;
            root->left = nil;
            root->right = nil;
            size = 0;
            end = alloc.allocate(1);
            end->left = nil;
            end->right = nil;
            end->parent = NULL;
            end->color = RED;
            end->height = 1;
            root->parent = end;
            end->left = root;
            end->_data.first = std::numeric_limits<int>::max();
            *this = rhs;
        }

        void insert(value_type key, Compare value)
        {
            Node_ *n = alloc.allocate(1);
            n->_data.first = key;
            n->value = value;
            // alloc.construct(n->value);
            insert(n);
            size++;
        }

        // insert using pair with enable if you want to use pair
        void insert_(value_type pair)
        {
            // use allocator for rebind to use custom allocator
            if(search(pair) != end && search(pair) != nil)
                return;
            Node_ *n = alloc.allocate(1);
            n->_data = pair;
            // n->_data = pair;
            insert(n);
            size++;
        }

        void printTree()
        {
            printTree(root);
        }

        // insert with return pair

        void addPair(std::pair<value_type, Compare> pair)
        {
            // use allocator for rebind to use custom allocator
            Node_ *n = new Node_(pair.first);
            n->value = pair.second;
            insert(n);
        }

        void makeEmpty()
        {
            makeEmpty(root);
        }

        // check if tree has a RED BLACK PROPERTY
        bool isRBProper()
        {
            return isRBProper(root);
        }

        // search
        Node_ *search(T key)
        {
            Node_ *n = root;
            while (n != nil)
            {
                if (comp(key.first, n->_data.first))
                    n = n->left;
                else if (comp(n->_data.first, key.first))
                    n = n->right;
                else
                    return n;
            }
            return nil;
        }
        // delete node
        void
        deleteNode(value_type key)
        {
            Node_ *x = nil;
            Node_ *y = nil;
            Node_ *_node = search(key);
            if (_node == nil)
                return;
            y = _node;
            int y_original_color = y->color;
            if (_node->left == nil)
            {
                x = _node->right;
                transplant(_node, _node->right);
            }
            else if (_node->right == nil)
            {
                x = _node->left;
                transplant(_node, _node->left);
            }
            else
            {

                y = treeMinimum(_node->right);
                y_original_color = y->color;
                x = y->right;
                if (x && y->parent == _node)
                {
                    x->parent = y;
                }
                else
                {
                    transplant(y, y->right);
                    y->right = _node->right;
                    if (y->right)
                        y->right->parent = y;
                }
                transplant(_node, y);
                y->left = _node->left;
                y->left->parent = y;
                y->color = _node->color;
            }

            alloc.destroy(_node);
            if (y_original_color == BLACK)
            {
                deleteFixup(x);
            }
            if (root != nil && root)
                root->color = BLACK;
            size--;
        }

        // size
        int
        _size_()
        {
            return size;
        }

        // height

        Node_ *search(value_type key, Compare &value)
        {
            Node_ *n = root;
            while (n != nil)
            {
                if (n->_data.first == key)
                {
                    value = n->value;
                    return n;
                }
                else if (n->_data.first > key)
                    n = n->left;
                else
                    n = n->right;
            }
            return nil;
        }
        // insert
        ~RBT()
        {
            // if (root)
                // makeEmpty();
        }

        // begin
        iterator begin()
        {
            return iterator(treeMinimum(root), this);
        }

        // end
        iterator _end_()
        {
            return iterator(end, this);
        }

        // find
        iterator find(T key)
        {
            Node_ *n = root;
            while (n != nil)
            {
                if (n->_data.first == key.first)
                    return iterator(n, this);
                else if (n->_data.first > key.first)
                    n = n->left;
                else
                    n = n->right;
            }
            return iterator(nil, this);
        }

        // erase
        void erase(value_type key)
        {
            deleteNode(key);
        }

        // clear
        void clear()
        {
            makeEmpty();
        }
        // empty
        bool empty()
        {
            return size == 0;
        }

        // find
        const_iterator find(T key) const
        {
            Node_ *n = search(key);
            return const_iterator(n, this);
        }

        Node_ *successor(Node_ *n)
        {
            if (n->right != nil)
                return treeMinimum(n->right);
            Node_ *tmp = n->parent;
            while (tmp != nil && tmp != end && n == tmp->right)
            {
                n = tmp;
                tmp = tmp->parent;
            }
            return (tmp);
        }

        Node_ *treeMaximum(Node_ *n)
        {
            while (n->right != nil)
                n = n->right;
            return n;
        }

        Node_ *predecessor(Node_ *n)
        {
            if (n->left != end && n->left != nil)
                return treeMaximum(n->left);
            Node_ *tmp = n->parent;
            while (n == tmp->left && tmp != end)
            {
                n = tmp;
                tmp = tmp->parent;
            }
            return (tmp);
        }

        //rbegin
        reverse_iterator rbegin()
        {
            return reverse_iterator(_end_());
        }

        //rend
        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }

        // begin
        const_iterator begin() const
        {
            Node_ *n = root;
            while (n->left != nil)
                n = n->left;
            return const_iterator(n, this);
        }

        // end
        const_iterator _end_() const
        {
            return const_iterator(end, this);
        }

        // rbegin const
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(_end_());
        }

        // rend const
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }

        //upper_bound
        iterator upper_bound(T key)
        {
            Node_ *n = root;
            while (n != nil && n->_data.first != key.first)
            {
                if (n->_data.first > key.first)
                    n = n->left;
                else
                    n = n->right;
            }
            return iterator(n->parent, this);
        }

        // lower_bound
        iterator lower_bound(T key)
        {
            Node_ *n = root;
            while (n != nil && n->_data.first != key.first)
            {
                if (n->_data.first > key.first)
                    n = n->left;
                else
                    n = n->right;
            }
            return iterator(n, this);
        }

        //at
        T &at(T key)
        {
            Node_ *n = search(key);
            if (n == nil)
                throw std::out_of_range("out of range");
            return n->_data;
        }

        //at
        const T &at(T key) const
        {
            Node_ *n = search(key);
            if (n == nil)
                throw std::out_of_range("out of range");
            return n->_data;
        }

        //at
        T &operator[](T key)
        {
            Node_ *n = search(key);
            if (n == nil)
                throw std::out_of_range("out of range");
            return n->_data;
        }

        //at
        const T &operator[](T key) const
        {
            Node_ *n = search(key);
            if (n == nil)
                throw std::out_of_range("out of range");
            return n->_data;
        }

        //at
        T &at(iterator it)
        {
            return it.node->_data;
        }

        //swap
        void swap(RBT &other)
        {
            ft::swap(root, other.root);
            ft::swap(nil, other.nil);
            ft::swap(end, other.end);
            ft::swap(size, other.size);
        }

        //equal_range
        ft::pair<iterator, iterator> equal_range(T key)
        {
            iterator first = lower_bound(key);
            iterator last = upper_bound(key);
            return ft::make_pair(first, last);
        }

        //equal_range
        ft::pair<const_iterator, const_iterator> equal_range(T key) const
        {
            const_iterator first = lower_bound(key);
            const_iterator last = upper_bound(key);
            return ft::make_pair(first, last);
        }

        //count 
        size_t count(T key) const
        {
            const_iterator it = find(key);
            if (it == end)
                return 0;
            return 1;
        }

        //max_size
        size_t max_size() const
        {
            return alloc.max_size();
        }

        // erase
        void erase(iterator first, iterator last)
        {
            while (first != last)
            {
                erase(first++);
            }
        }

        // erase with iterator
        void erase(iterator it)
        {
            deleteNode(it.node);
        }

    };
}
#endif