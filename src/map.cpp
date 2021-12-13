#include <iostream>
#include <fstream>
#include <string>

// COLOR ENUM
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
    Node(int key)
    {
        this->key = key;
        left = right = NULL;
        color = RED;
    }
};

// RIGHTROTATION
Node *RightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

Node *LeftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

// insert a node in the tree
void InsertNewNode(Node *&root, int key)
{
    if (root == NULL)
    {
        root = new Node(key);
        return;
    }
    if (key < root->key)
        InsertNewNode(root->left, key);
    else if (key > root->key)
        InsertNewNode(root->right, key);
    else
        return;
    // fix the tree
    if (root->left != NULL && root->left->color == RED && root->right != NULL && root->right->color == RED)
    {
        root->color = RED;
        root->left->color = BLACK;
        root->right->color = BLACK;
    }
    else if (root->left != NULL && root->left->color == RED)
    {
        root->color = RED;
        root->left->color = BLACK;
        root = RightRotate(root);
    }
    else if (root->right != NULL && root->right->color == RED)
    {
        root->color = RED;
        root->right->color = BLACK;
        root = LeftRotate(root);
    }
    else
        root->color = RED;
}

void PrintTree(Node *root) // print three with designated format
{
    if (root == NULL)
        return;
    PrintTree(root->left);
    std::cout << root->key << " ";
    PrintTree(root->right);
}

void  DeleteNode(Node *&root, int key)
{
    if (root == NULL)
        return;
    if (key < root->key)
        DeleteNode(root->left, key);
    else if (key > root->key)
        DeleteNode(root->right, key);
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
        }
        else if (root->left == NULL)
        {
            Node *temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root;
            root = root->left;
            delete temp;
        }
        else
        {
            Node *temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;
            root->key = temp->key;
            DeleteNode(root->right, temp->key);
        }
    }
}

Node *SearchNode(Node *root, int key)
{
    if (root == NULL)
        return NULL;
    if (key < root->key)
        return SearchNode(root->left, key);
    else if (key > root->key)
        return SearchNode(root->right, key);
    else
        return root;
}

int main()
{
    // RED BLACK TREE ALGORITHM
    // 1. Create a tree
    // 2. Insert a node
    // 3. Delete a node
    // 4. Search a node
    // 5. Traverse the tree
    // 6. Print the tree
    // 7. Destroy the tree
    // 8. Exit

    // test Tree
    Node *root = NULL;
    InsertNewNode(root, 30);
    InsertNewNode(root, 40);
    InsertNewNode(root, 10);
    InsertNewNode(root, 20);

    // print the tree
    std::cout << "The tree is: " << std::endl;
    PrintTree(root);

    // delete a node
    DeleteNode(root, 10);

    // print the tree
    std::cout << "The tree is: " << std::endl;
    PrintTree(root);

    // search a node
    Node *temp = SearchNode(root, 120);
    if (temp != NULL)
        std::cout << "\nThe node is found: " << temp->key << std::endl;
    else
        std::cout << "\nThe node is not found" << std::endl;
    return 0;
}