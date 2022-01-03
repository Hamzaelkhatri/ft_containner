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
            this->rbt_ = _other.getTree();
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

        RBT_iter &operator++() //
        {
            it = rbt_->successor(it);
            return *this;
        }

        RBT_iter operator++(int)
        {
            RBT_iter tmp = *this;
            it = rbt_->successor(it);
            return tmp;
        }

        // // <<
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
            RBT_iter tmp = *this;
            rbt_->predecessor(it);
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
              class Alloc = std::allocator<T> > // map::allocator_type
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
        typedef typename Alloc::size_type size_type;
        typedef typename Alloc::difference_type difference_type;
        typedef struct Node<value_type> *NodePtr;
        typedef RBT *self;
        int size;
        typedef ft::RBT_iter<self, Node_, pointer> iterator;
        typedef ft::RBT_iter<self, Node_, pointer> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        Node_ *root;
        Node_ *end;
        Node_ *nil;

    private:
        node_allocator alloc;
        int height;
        Compare comp;

        Node_ *grandparent(Node_ *n)
        {
            if (n == NULL || n->parent == NULL || n == nil || n->parent == nil)
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

        void rotateRight(Node_ *n)
        {

            Node_ *l = n->left;
            n->left = l->right;
            if (l->right != nil)
                l->right->parent = n;
            l->parent = n->parent;
            if (n->parent == nil || n->parent == end)
                root = l;
            else if (n == n->parent->left)
                n->parent->left = l;
            else
                n->parent->right = l;
            l->right = n;
            n->parent = l;
        }

        void rotateLeft(Node_ *n)
        {
            Node_ *r = n->right;
            n->right = r->left;
            if (r->left != nil)
                r->left->parent = n;
            r->parent = n->parent;
            if (n->parent == nil || n->parent == end)
                root = r;
            else if (n == n->parent->left)
                n->parent->left = r;
            else
                n->parent->right = r;
            r->left = n;
            n->parent = r;
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
            if (!n || n == nil || n == end)
                return;
            makeEmpty(n->left);
            makeEmpty(n->right);
            alloc.destroy(n);
            if (n->left != end)
                alloc.deallocate(n, 1);
            n->left = end;
            n->right = end;
        }

        Node_ *getRootOfTree()
        {
            return root;
        }

        // insertFixup
        void
        insertFixup(Node_ *_node)
        {
            Node_ *tmp;
            while (_node->parent->color == RED)
            {
                if (_node->parent == _node->parent->parent->right)
                {
                    tmp = _node->parent->parent->left;
                    if (tmp && tmp->color == RED)
                    {
                        tmp->color = BLACK;
                        _node->parent->color = BLACK;
                        _node->parent->parent->color = RED;
                        _node = _node->parent->parent;
                    }
                    else
                    {
                        if (_node == _node->parent->left)
                        {
                            _node = _node->parent;
                            rotateRight(_node);
                        }
                        _node->parent->color = BLACK;
                        _node->parent->parent->color = RED;
                        rotateLeft(_node->parent->parent);
                    }
                }
                else
                {
                    tmp = _node->parent->parent->right;
                    if (tmp && tmp->color == RED)
                    {
                        tmp->color = BLACK;
                        _node->parent->color = BLACK;
                        _node->parent->parent->color = RED;
                        _node = _node->parent->parent;
                    }
                    else
                    {
                        if (_node == _node->parent->right)
                        {
                            _node = _node->parent;
                            rotateLeft(_node);
                        }
                        _node->parent->color = BLACK;
                        _node->parent->parent->color = RED;
                        rotateRight(_node->parent->parent);
                    }
                }
                if (_node == root)
                    break;
            }
            root->color = BLACK; // root is always black
            root->parent = end;
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

        void insert(T data)
        {
            if (root == nil)
            {
                root = alloc.allocate(1);
                root->color = BLACK;
                root->_data = data;
                root->left = nil;
                root->right = nil;
                root->parent = end;
                size++;
            }
            else
            {
                Node_ *tmp = this->root;
                Node_ *tmp2 = nil;
                Node_ *_new = alloc.allocate(1);
                size++;
                _new->_data = data;
                _new->left = nil;
                _new->right = nil;
                _new->parent = end;
                _new->color = RED;
                while (tmp != nil)
                {
                    tmp2 = tmp;
                    if (comp(data.first, tmp->_data.first))
                        tmp = tmp->left;
                    else if (comp(tmp->_data.first, data.first))
                        tmp = tmp->right;
                    else
                        return;
                }
                _new->parent = tmp2;
                if (comp(data.first, tmp2->_data.first))
                    tmp2->left = _new;
                else if (comp(tmp2->_data.first, data.first))
                    tmp2->right = _new;
                insertFixup(_new);
            }
        }

        void printTree(Node_ *n)
        {
            // print tree with details
            if (n == nil || !n)
                return;
            printTree(n->left);
            std::cout << "adrs of node " << n << " Key: " << n->_data.first << " Color: " << (n->color == 0 ? "RED" : "BLACK") << " Height: " << n->height << " Parent: " << (n->parent == end ? "\033[0;31mROOT " : "CHILD ") << "\033[0mLeft: " << (n->left != nil ? std::to_string(n->left->_data.first) : "nil") << " Right: " << (n->right != nil ? std::to_string(n->right->_data.first) : "nil") << std::endl;
            printTree(n->right);
        }

        int isRBProper(Node_ *n)
        {
            if (n == nil)
                return 1;
            if (n->color == RED && ((n->left != nil && n->left->color == RED) || (n->right != nil && n->right->color == RED)))
            {
                // print details
                std::cout << "adrs of node " << n << " Node_: " << n->_data.first << " Color: " << (n->color == 0 ? "RED" : "BLACK") << " Height: " << n->height << " Parent: " << (n->parent == end ? "\033[0;31mROOT\033[0m" : "CHILD ") << " Left: " << (n->left != nil ? std::to_string(n->left->_data.first) : "nil") << " Right: " << (n->right != nil ? std::to_string(n->right->_data.first) : "nil") << std::endl;
                return 0;
            }
            return isRBProper(n->left) && isRBProper(n->right);
        }

        // transplant
        void transplant(Node_ *u, Node_ *v)
        {
            if (!u->parent)
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
            while (n->left != nil)
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

        // iterative delete
        void clear_leak(Node_ *n)
        {
            while (n != nil)
            {
                if (n->left != nil)
                    clear_leak(n->left);
                if (n->right != nil)
                    clear_leak(n->right);
                alloc.deallocate(n, 1);
                n = nil;
            }
        }

    public:
        RBT()
        {
            nil = alloc.allocate(1);
            end = alloc.allocate(1);
            end->right = nil;
            nil->color = BLACK;
            nil->left = NULL;
            nil->right = NULL;
            root = nil;
            end->left = root;
            end->parent = end;
            comp = Compare();
            size = 0;
        }

        void insert(value_type key, Compare value)
        {
            insert(key);
        }

        // insert using pair with enable if you want to use pair
        void insert_(value_type pair)
        {
            // use allocator for rebind to use custom allocator
            insert(pair);
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
            alloc.deallocate(_node, 1);
            if (y_original_color == BLACK)
            {
                deleteFixup(x);
            }
            if (root != nil && root)
                root->color = BLACK;
        }

        // size
        int
        _size_()
        {
            return size;
        }

        // height

        // Node_ *search(value_type key, Compare &value)
        // {
        //     Node_ *n = root;
        //     while (n != nil)
        //     {
        //         if (n->_data.first == key)
        //         {
        //             value = n->value;
        //             return n;
        //         }
        //         else if (n->_data.first > key)
        //             n = n->left;
        //         else
        //             n = n->right;
        //     }
        //     return nil;
        // }

        void clear_leak()
        {
            clear_leak(root);
        }
        // insert
        ~RBT()
        {
            makeEmpty();
            if (nil->right != end)
            {
                alloc.destroy(nil);
                alloc.deallocate(nil, 1);
                nil->right = end;
            }
            if (end->right != end)
            {
                alloc.destroy(end);
                alloc.deallocate(end, 1);
                end->right = end;
            }
        }

        // begin
        iterator begin()
        {
            Node_ *n = root;
            if (root == nil)
                return _end_();
            while (n->left != nil)
                n = n->left;
            return iterator(n, this);
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
            return iterator(end, this);
        }

        // erase
        void erase(iterator it)
        {
            std::cout << "erase" << std::endl;
            deleteNode(it.it->_data);
        }

        // erase
        void erase(value_type key)
        {
            deleteNode(key);
        }

        // clear
        void clear()
        {
            // makeEmpty();
        }
        // empty
        bool empty()
        {
            return empty();
        }

        // begin
        iterator begin() const
        {
            Node_ *n = root;
            while (n->left != nil)
                n = n->left;
            return iterator(n, this);
        }

        // end
        iterator find(T key) const
        {
            Node_ *n = search(key);
            return iterator(n, this);
        }

        // successor
        Node_ *successor(Node_ *n)
        {
            if (n->right != nil && n->right != NULL)
                return treeMinimum(n->right);
            Node_ *y = n->parent;
            while (y != nil && n == y->right)
            {
                n = y;
                y = y->parent;
            }
            return y;
        }
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
        Node_ *treeMaximum(Node_ *n)
        {
            while (n->right != nil)
                n = n->right;
            return n;
        }
        // predecessor
        Node_ *predecessor(Node_ *n)
        {
            if (n->left != nil && n->left != end)
                return treeMaximum(n->left);
            Node_ *tmp = n->parent;
            while (tmp != end && n == tmp->left)
            {
                n = tmp;
                tmp = tmp->parent;
            }
            if (tmp == end)
                return treeMaximum(root);
            return (tmp);
        }

        // count
        size_t count(const T &key) const
        {
            Node_ *n = root;
            int count = 0;
            while (n != nil)
            {
                if (n->_data.first == key.first)
                {
                    count++;
                    break;
                }
                else if (n->_data.first > key.first)
                    n = n->left;
                else
                    n = n->right;
            }
            return count;
        }

        // swap
        void swap(RBT &other)
        {
            std::swap(root, other.root);
            std::swap(size, other.size);
            std::swap(comp, other.comp);
            std::swap(alloc, other.alloc);
        }

        // lower_bound
        iterator lower_bound(const T &data)
        {
            iterator _from = this->begin();
            iterator _to = this->_end_();
            while (_from != _to)
            {
                if (!comp((*_from).first, data.first))
                    return _from;
                ++_from;
            }
            return _from;
        }
        const_iterator lower_bound(const T &data) const
        {
            return (const_iterator(lower_bound(data)));
        }
        // upper_bound
        iterator upper_bound(const T &data)
        {
            iterator _from = this->begin();
            iterator _to = this->_end_();
            while (_from != _to)
            {
                if (comp(data.first, (*_from).first))
                    return _from;
                ++_from;
            }
            return _from;
        }
        const_iterator upper_bound(const T &data) const
        {
            return (const_iterator(upper_bound(data)));
        }

        // equal_range
        ft::pair<iterator, iterator> equal_range(const T &data)
        {
            return ft::make_pair(lower_bound(data), upper_bound(data));
        }
        // max_size
        size_t max_size() const
        {
            return (std::min(alloc.max_size(), std::numeric_limits<size_type>::max()));
        }

        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }
        reverse_iterator rbegin()
        {
            return reverse_iterator(_end_());
        }

        //operator=
        // RBT &operator=(RBT other)
        // {
        //     // this->root = other.root;
        //     // this->size = other.size;
        //     // this->comp = other.comp;
        //     // this->alloc = other.alloc;
        //     // this->end = other.end;
        //     // this->nil = other.nil;
        //     return *this;
        // }
    };
}
#endif // RBT_HPP∂