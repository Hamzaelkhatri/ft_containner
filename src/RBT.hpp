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
                    _Node *u = n->parent->parent->left;// uncle
                    // check if Node is not empty
                    if ( u && u->color == RED)// if u is NULL that mean uncle/aunt is NULL and any NULL mean Thats BLACK
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
            // print tree with details
            if (n == NULL)
                return;
            printTree(n->left);
            std::cout << "Key: " << n->key << " Color: " << (n->color == 0 ? "RED" : "BLACK") << " Height: " << n->height << " Parent: " << (n->parent == NULL ? "ROOT" : "CHILD") << " Left: " << n->left << " Right: " << n->right << std::endl;
            printTree(n->right);            
        }

        int isRBProper(_Node *n)
        {
            if (n == NULL)
                return 1;
            if (n->color == RED && ((n->left != NULL && n->left->color == RED )|| (n->right != NULL && n->right->color == RED)))
                return 0;
            return isRBProper(n->left) && isRBProper(n->right);
        }
        //  deleteFixup
        void deleteFixup(_Node *n)
        {

            while (n && n != root && n->color == BLACK)
            {
                if (n == n->parent->left)
                {
                    _Node *w = n->parent->right;
                    if (w->color == RED)
                    {
                        w->color = BLACK;
                        n->parent->color = RED;
                        rotateLeft(n->parent);
                        w = n->parent->right;
                    }
                    if (w->left->color == BLACK && w->right->color == BLACK)
                    {
                        w->color = RED;
                        n = n->parent;
                    }
                    else
                    {
                        if (w->right->color == BLACK)
                        {
                            w->left->color = BLACK;
                            w->color = RED;
                            rotateRight(w);
                            w = n->parent->right;
                        }
                        w->color = n->parent->color;
                        n->parent->color = BLACK;
                        w->right->color = BLACK;
                        rotateLeft(n->parent);
                        n = root;
                    }
                }
                else
                {
                    _Node *w = n->parent->left;
                    if (w && w->color == RED)
                    {
                        w->color = BLACK;
                        n->parent->color = RED;
                        rotateRight(n->parent);
                        w = n->parent->left;
                    }
                    if (w->right->color == BLACK && w->left->color == BLACK)
                    {
                        w->color = RED;
                        n = n->parent;
                    }
                    else
                    {
                        if (w->left->color == BLACK)
                        {
                            w->right->color = BLACK;
                            w->color = RED;
                            rotateLeft(w);
                            w = n->parent->left;
                        }
                        w->color = n->parent->color;
                        n->parent->color = BLACK;
                        w->left->color = BLACK;
                        rotateRight(n->parent);
                        n = root;
                    }
                }
            }
        }

        //transplant
        void transplant(_Node *u, _Node *v)
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
        //treeMinimum 
        _Node *treeMinimum(_Node *n)
        {
            while (n->left != NULL)
                n = n->left;
            return n;
        }
        
        // delete
        void deleteNode(_Node *n)
        {
            _Node *x = NULL;
            _Node *y = n;
            _Node *z = NULL;
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
                if (y->parent == n)
                    x->parent = y;
                else
                {
                    transplant(y, y->right);
                    y->right = n->right;
                    y->right->parent = y;
                }
                transplant(n, y);
                y->left = n->left;
                y->left->parent = y;
                y->color = n->color;
            }
            if (y_original_color == BLACK)
                deleteFixup(x);
        }


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

        void makeEmpty()
        {
            makeEmpty(root);
        }

        //check if tree has a RED BLACK PROPERTY
        bool isRBProper()
        {
            return isRBProper(root);
        }

        //search
        _Node *search(T key)
        {
            _Node *n = root;
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
        _Node *end()
        {
            _Node *n = root;
            while (n->right != NULL)
                n = n->right;
            return n;
        }

        // delete node
        void deleteNode(T key)
        {
            _Node *n = search(key);
            if (n != NULL)
                deleteNode(n);
        }

        ~RBT()
        {
            makeEmpty();
        }
    };
};

#endif // RBT_HPP