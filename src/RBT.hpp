#ifndef RBT_HPP
#define RBT_HPP

#include <iostream>

// Red-Black Tree class
//
// CONSTRUCTION: with (a) no parameters
//
//  ******************PUBLIC OPERATIONS*********************
//  void insert( x )       --> Insert x
//  void remove( x )       --> Remove x (unimplemented)
//  bool contains( x )     --> Return true if x is present
//  Comparable findMin( )  --> Return smallest item
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

    template <class T, typename Comparable = std::less<T> >
    class RBT
    {
    private:
        // enum Color
        enum Color
        {
            RED,
            BLACK
        };

        // struct for red-black tree
        typedef struct Node
        {
            T key; // Key
            Comparable value;
            Node *left;
            Node *right;
            Node *parent;
            int height;
            int color;
            Node(T k)
            {
                key = k;
                left = right = NULL;
                color = RED;
                height = 1;
            }
        } _Node;

        _Node *root;
        int size;
        int height;
        Comparable comp;
        _Node *NIL;
        _Node *grandparent(_Node *n)
        {
            if (n == NULL || n->parent == NULL)
                return NULL;
            return n->parent->parent;
        }

        _Node *uncle(_Node *n)
        {
            _Node *g = grandparent(n);
            if (g == NULL)
                return NULL;
            if (n->parent == g->left)
                return g->right;
            else
                return g->left;
        }
        // update height of a node
        void updateHeight(_Node *n)
        {
            int hl = (n->left == NULL) ? 0 : n->left->height;
            int hr = (n->right == NULL) ? 0 : n->right->height;
            n->height = (hl > hr ? hl : hr) + 1;
        }

        void rotateLeft(_Node *n)
        {
            _Node *r = n->right;
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

        void rotateRight(_Node *n)
        {
            _Node *l = n->left;
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

        void doublerotateLeft(_Node *n)
        {
            rotateRight(n->right);
            rotateLeft(n);
        }

        void doublerotateRight(_Node *n)
        {
            rotateLeft(n->left);
            rotateRight(n);
        }

        void makeEmpty(_Node *n)
        {
            if (n == NULL)
                return;
            makeEmpty(n->left);
            makeEmpty(n->right);
            delete n;
        }
        // insertFixup
        void insertFixup(_Node *n)
        {
            while (n != root && n->parent->color == RED)
            {
                if (n->parent == n->parent->parent->left)
                {
                    _Node *u = n->parent->parent->right;
                    if (u->color == RED)
                    {
                        n->parent->color = BLACK;
                        u->color = BLACK;
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
                    _Node *u = n->parent->parent->left;
                    if (u->color == RED)
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

        void insert(_Node *n)
        {
            _Node *y = NULL;
            _Node *x = root;
            while (x != NULL)
            {
                y = x;
                if (comp(n->key, x->key))
                    x = x->left;
                else
                    x = x->right;
            }
            n->parent = y;
            if (y == NULL)
                root = n;
            else if (comp(n->key, y->key))
                y->left = n;
            else
                y->right = n;
            n->left = n->right = NULL;
            n->color = RED;
            n->height = 1;
            insertFixup(n);
        }

        void printTree(_Node *n)
        {
            if (n == NULL)
                return;
            printTree(n->left);
            std::cout << n->key << " ";
            printTree(n->right);
        }

        //  INSERTION using heigh balanced tree

    public:
        // Constructors and destructor
        RBT()
        {
            root = NULL;
            size = 0;
            height = 1;
        }
        RBT(const RBT<T, Comparable> &rhs)
        {
            root = NULL;
            size = 0;
            height = 1;
            *this = rhs;
        }

        void insert(T key, Comparable value)
        {
            _Node *n = new _Node(key);
            n->value = value;
            insert(n);
        }

        void insert(T key)
        {
            _Node *n = new _Node(key);
            insert(n);
        }

        void printTree()
        {
            printTree(root);
        }

        ~RBT()
        {
            makeEmpty(root);
        }
    };
};

#endif // RBT_HPP