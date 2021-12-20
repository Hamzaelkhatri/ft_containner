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
    
    template <class Key, class T>
    struct Node
    {
        Key key;
        T value;
        Node *left;   // Left child
        Node *right;  // Right child
        Node *parent; // Parent
        int height;   // Height
        int color;    //

        // default constructor
        Node()
        {
            left = right = parent = NULL;
            height = 0;
            color = RED;
        }

        Node(Key k,T v)
        {
            value = v;
            key = k;
            left = right = NULL;
            color = RED;
            height = 1;
        }
    };

    template <class Key,                                            // map::key_type
              class T,                                              // map::mapped_type
              class Compare = std::less<Key>,                       // map::key_compare
              class Alloc = std::allocator<std::pair<const Key, T>> // map::allocator_type
              >
    class RBT
    {
    private:
        // typedef T *iterator;
        // iterator
        // typedef std::pair<const Key, T> value_type;
        // enum Color

        // struct for red-black tree

        struct Node<Key,T> *root;
        struct Node<Key,T> *end;
        int size;
        int height;
        Compare comp;
        Alloc alloc;
        struct Node<Key,T> *grandparent(struct Node<Key,T> *n)
        {
            if (n == NULL || n->parent == NULL)
                return NULL;
            return n->parent->parent;
        }

        struct Node<Key,T> *uncle(struct Node<Key,T> *n)
        {
            struct Node<Key,T> *g = grandparent(n);
            if (g == NULL)
                return NULL;
            if (n->parent == g->left)
                return g->right;
            else
                return g->left;
        }

        // update height of a node
        void updateHeight(struct Node<Key,T> *n)
        {
            int hl = (n->left == NULL) ? 0 : n->left->height;
            int hr = (n->right == NULL) ? 0 : n->right->height;
            n->height = (hl > hr ? hl : hr) + 1;
        }

        void rotateLeft(struct Node<Key,T> *n)
        {
            struct Node<Key,T> *r = n->right;
            n->right = r->left;
            if (r->left != NULL)
                r->left->parent = n;
            r->parent = n->parent;
            if (n->parent == NULL)
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

        void rotateRight(struct Node<Key,T> *n)
        {
            struct Node<Key,T> *l = n->left;
            n->left = l->right;
            if (l->right != NULL)
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

        void doublerotateLeft(struct Node<Key,T> *n)
        {
            rotateRight(n->right);
            rotateLeft(n);
        }

        void doublerotateRight(struct Node<Key,T> *n)
        {
            rotateLeft(n->left);
            rotateRight(n);
        }

        void makeEmpty(struct Node<Key,T> *n)
        {
            if (n == NULL)
                return;
            makeEmpty(n->left);
            makeEmpty(n->right);
            delete n;
        }

        struct Node<Key,T> *getRootOfTree()
        {
            return root;
        }

        // insertFixup
        void insertFixup(struct Node<Key,T> *n)
        {
            while (n && n != root && n->parent->color == RED)
            {
                if (n->parent == n->parent->parent->left)
                {
                    struct Node<Key,T> *u = n->parent->parent->right;
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
                    struct Node<Key,T> *u = n->parent->parent->left; // uncle
                    // check if Node is not empty
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

        void insert(struct Node<Key,T> *n) // 1 ---->
        {
            struct Node<Key,T> *y = NULL;
            struct Node<Key,T> *x = root;

            while (x != NULL)
            {
                y = x;
                if (n->key < x->key) // 1 2 3 5
                    x = x->left;
                else
                    x = x->right;
            }
            n->parent = y;
            if (y == NULL)
            {
                root = n;
            }
            else if (n->key < y->key)
                y->left = n;
            else
                y->right = n;
            n->left = n->right = NULL;
            n->color = RED;
            n->height = 1;
            insertFixup(n);
        }

        void printTree(struct Node<Key,T> *n)
        {
            // print tree with details
            if (n == NULL)
                return;
            printTree(n->left);
            std::cout << "Key: " << n->key << " Color: " << (n->color == 0 ? "RED" : "BLACK") << " Height: " << n->height << " Parent: " << (n->parent == NULL ? "\033[0;31mROOT " : "CHILD ") << "\033[0mLeft: " << n->left << " Right: " << n->right << std::endl;
            printTree(n->right);
        }

        int isRBProper(struct Node<Key,T> *n)
        {
            if (n == NULL)
                return 1;
            if (n->color == RED && ((n->left != NULL && n->left->color == RED) || (n->right != NULL && n->right->color == RED)))
            {
                // print details
                std::cout << "Node: " << n->key << " Color: " << (n->color == 0 ? "RED" : "BLACK") << " Height: " << n->height << " Parent: " << (n->parent == NULL ? "\033[0;31mROOT\033[0m" : "CHILD ") << " Left: " << n->left << " Right: " << n->right << std::endl;
                return 0;
            }
            return isRBProper(n->left) && isRBProper(n->right);
        }

        //  deleteFixup
        void deleteFixup(struct Node<Key,T> *n)
        {
            insertFixup(n);
        }

        // transplant
        void transplant(struct Node<Key,T> *u, struct Node<Key,T> *v)
        {
            if (u->parent == NULL)
                root = v;
            else if (u == u->parent->left)
                u->parent->left = v;
            else
                u->parent->right = v;
            if (v != NULL)
                v->parent = u->parent;
        }

        // treeMinimum
        struct Node<Key,T> *treeMinimum(struct Node<Key,T> *n)
        {
            while (n->left != NULL)
                n = n->left;
            return n;
        }

        // delete
        void deleteNode(struct Node<Key,T> *n)
        {
            struct Node<Key,T> *x = NULL;
            struct Node<Key,T> *y = n;
            struct Node<Key,T> *z = NULL;
            bool y_original_color = y->color;
            if (n->left == NULL)
            {
                x = n->right;
                transplant(n, n->right);
            }
            else if (n->right == NULL)
            {
                x = n->left;
                transplant(n, n->left);
            }
            else
            {
                y = treeMinimum(n->right);
                y_original_color = y->color;
                x = y->right;
                if (x && y->parent == n)
                    x->parent = y;
                else
                {
                    if (y->parent != n)
                    {
                        z = y->parent;
                        transplant(y, y->right);
                        y->right = n->right;
                        y->right->parent = y;
                    }
                }
                transplant(n, y);
                y->left = n->left;
                y->left->parent = y;
                y->color = n->color;
            }
            if (y_original_color == BLACK)
                insertFixup(x);
        }

    public:

        RBT()
        {
            root = NULL;
            size = 0;
            height = 1;
            end = new struct Node<Key,T>(std::numeric_limits<Key>::max(),std::numeric_limits<T>::max());
            end->left = end;
            end->right = end;
            end->parent = end;
            end->color = BLACK;
            end->height = 1;
        }
        RBT(const RBT<T, Compare> &rhs)
        {
            root = NULL;
            end = new struct Node<Key,T>(0);
            end->left = NULL;
            end->right = NULL;
            end->parent = NULL;
            end->color = -1;
            end->height = 1;
            end->key = std::numeric_limits<int>::max();
            *this = rhs;
        }

        void insert(T key, Compare value)
        {
            struct Node<Key,T> *n = new struct Node<Key,T>(key);
            n->value = value;
            insert(n);
        }
        // void insert(T key)
        // {
        //     struct Node<Key,T> *n = new struct Node<Key,T>(key);
        //     insert(n);
        // }

        // insert using pair with enable if you want to use pair
        void insert(std::pair<Key, T> pair)
        {
            // use allocator for rebind to use custom allocator
            struct Node<Key,T> *n = new struct Node<Key,T>(pair.first,pair.second);
            insert(n);
            size++;
        }

        void printTree()
        {
            printTree(root);
        }

        // insert with return pair

        void addPair(std::pair<T, Compare> pair)
        {
            // use allocator for rebind to use custom allocator
            struct Node<Key,T> *n = new struct Node<Key,T>(pair.first);
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
        struct Node<Key,T> *search(T key)
        {
            struct Node<Key,T> *n = root;
            while (n != NULL)
            {
                if (n->key == key)
                    return n;
                else if (n->key > key)
                    n = n->left;
                else
                    n = n->right;
            }
            return NULL;
        }

        // end()
        struct Node<Key,T> *_end_()
        {
            // get the maximum element
            struct Node<Key,T> *n = root;
            while (n->right != NULL)
                n = n->right;

            std::cout << "end: " << end << " root :" << std::endl;
            return end;
        }

        // delete node
        void deleteNode(T key)
        {
            struct Node<Key,T> *n = search(key);
            if (n != NULL)
            {
                deleteNode(n);
                size--;
            }
        }

        struct Node<Key,T> *_begin_()
        {
            return treeMinimum(root);
        }

        // size
        int _size_()
        {
            return size;
        }

        // height

        struct Node<Key,T> *search(T key, Compare &value)
        {
            struct Node<Key,T> *n = root;
            while (n != NULL)
            {
                if (n->key == key)
                {
                    value = n->value;
                    return n;
                }
                else if (n->key > key)
                    n = n->left;
                else
                    n = n->right;
            }
            return NULL;
        }
        // insert
        ~RBT()
        {
            makeEmpty();
        }
        //constractor

        // begin iterator
        // iterator *begin()
        // {
        //     return iterator(_begin_());
        // }

        // // end iterator
        // iterator *end1()
        // {
        //     return iterator(_end_());
        // }
    };
};

#endif // RBT_HPP∂