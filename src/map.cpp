#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "map.hpp"
#include <utility>
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

// clear tree
void clear(Node *&root)
{
    if (root == NULL)
        return;
    clear(root->left);
    clear(root->right);
    delete root;
    root = NULL;
}
// COLOR ENUM
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
void InsertNewNode(Node *&root, int key, std::string value)
{
    if (root == NULL)
    {
        root = new Node(key, value);
        return;
    }
    if (key < root->key)
        InsertNewNode(root->left, key, value);
    else if (key > root->key)
        InsertNewNode(root->right, key, value);
    else
        return;
    // fix the tree after insertion of new node
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
    if (root->color == RED)
        std::cout << "RED ";
    else
        std::cout << "BLACK ";
    std::cout << root->key << " -->  " << root->value << " " << std::endl;
    PrintTree(root->right);
}

void DeleteNode(Node *&root, int key)
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
    // Node *root = NULL;
    // int i = 0;
    // ft::map<std::string, std::string> map;

    // //insert in loop
    // while (i < 10)
    // {
    //     std::string key = "key" + std::to_string(i);
    //     std::string value = "value" + std::to_string(i);
    //     map.insert(std::pair<std::string, std::string>(key, value));
    //     i++;
    // }

    // map.print();
    
    // map.insert(std::pair<int, std::string>(1, "one"));
    // while (i < 1000)
    // {
    //     InsertNewNode(root, i, "test");
    //     i++;
    // }

    // InsertNewNode(root, 30, "30");

    // // print the tree
    // std::cout << "The tree is after insert: " << std::endl;
    // PrintTree(root);

    // // delete a node
    // DeleteNode(root, 10);

    // // print the tree
    // std::cout << "The tree after delete is: " << std::endl;
    // PrintTree(root);

    // // search a node
    // Node *temp = SearchNode(root, 120);
    // if (temp != NULL)
    //     std::cout << "\nThe node is found: " << temp->key << std::endl;
    // else
    //     std::cout << "\nThe node is not found" << std::endl;

    // compare beteen map and red-black tree
    // map[10] = "10";
    // map[20] = "20";
    // map[30] = "30";
    // map[40] = "40";

    // std::cout << "The map is: " << std::endl;
    // // iterate through the map
    // for (std::map<int, std::string>::iterator it = map.begin(); it != map.end(); ++it)
    //     std::cout << it->first << " --> " << it->second << std::endl;

    // calculate the time
    // clock_t start, end;
    // double cpu_time_used;
    // start = clock();
    // // insert a node
    // int i = 0;
    // while (i < 10000)
    // {
    //     InsertNewNode(root, i, "test");
    //     i++;
    // }
    // end = clock();
    // cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    // std::cout << "The time for insert is: " << cpu_time_used << std::endl;

    // // calculate the time for search
    // start = clock();
    // // search a node
    // i = 0;
    // while (i < 10000)
    // {
    //     SearchNode(root, i);
    //     i++;
    // }
    // end = clock();
    // cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    // std::cout << "The time for search is: " << cpu_time_used << std::endl;

    // // calculate the time for map
    // // iterate through the insert map
    // start = clock();
    // while (i < 10000)
    // {
    //     map[i] = "test";
    //     i++;
    // }
    // end = clock();
    // cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    // std::cout << "The time for map is: " << cpu_time_used << std::endl;
    // 1 2 3 4
    // 0x001 0x002 0x003  0x005 0x004
    //
    return 0;
}