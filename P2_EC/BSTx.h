// BST.h

#ifndef BST_H
#define BST_H

#include <sstream>
#include <algorithm>
#include<queue>

using namespace std;

template<class T>
class BST {

public:
    BST(T);

    ~BST();
    void insert(T Data);


    int getHeight();

    int getLevel(T data);
    string getLevelOrder();

    BST(BST<T> const &);//copy constructor

    int getWidth();

private:
    struct Node {
        T data;
        Node *left;
        Node *right;
    };
    Node *root;
    stringstream response;
    void destroyTree(Node *&);
    void insert(Node *&, Node *&);

    int getHeight(Node *);

    int getLevel(Node *, T, int);

    Node &operator=(const Node &other);

    int getWidth(Node *);

    int getWidth(Node *root, int level);

    void getLevelOrder(Node *);


};

template<typename T>
BST<T>::BST(T) {
    root = nullptr;
}

template<typename T>
BST<T>::~BST() {
    destroyTree(root);
}

template<typename T>
void BST<T>::destroyTree(Node *&ptr) {
    if (ptr != nullptr) {
        destroyTree(ptr->left);
        destroyTree(ptr->right);
        delete ptr;
    }
    ptr = nullptr;
}


template<class T>
int BST<T>::getHeight() {
    return getHeight(root);
}

template<class T>
int BST<T>::getHeight(Node *ptr) {
    if (ptr == nullptr)
        return 0;

    return 1 + max(getHeight(ptr->left), getHeight(ptr->right));
}

template<typename T>
int BST<T>::getLevel(T data) {
    return getLevel(root, data, 0);
}

template<class T>
int BST<T>::getLevel(Node *ptr, T data, int level) {

    if (ptr == NULL)
        return -1;
    if (ptr->data == data)
        return level;
    // If NULL or leaf Node
    if (ptr->left == NULL && ptr->right == NULL)
        return -1;
    // Find If ptr is present in the left or right subtree.
    int levelLeft = getLevel(ptr->left, data, level + 1);
    int levelRight = getLevel(ptr->right, data, level + 1);
    if (levelLeft == -1)
        return levelRight;
    else
        return levelLeft;
}


template<class T>
int BST<T>::getWidth() {
    return getWidth(root);
}

template<class T>
int BST<T>::getWidth(Node *root) {
    int maxWidth = 0;
    int width;
    int h = getHeight(root);
    int i;

    /* Get width of each level and compare
        the width with maximum width so far */
    for (i = 1; i <= h; i++) {
        width = getWidth(root, i);
        if (width > maxWidth)
            maxWidth = width;
    }

    return maxWidth;
}

/* Get width of a given level */
template<class T>
int BST<T>::getWidth(Node *root, int level) {

    if (root == NULL)
        return 0;

    if (level == 1)
        return 1;

    else if (level > 1)
        return getWidth(root->left, level - 1)
               + getWidth(root->right, level - 1);

    return 0;
}


template<typename T>
void BST<T>::insert(T item) {
    Node *newNode = new Node;
    newNode->data = item;
    newNode->left = newNode->right = nullptr;

    insert(root, newNode);
}

template<typename T>
void BST<T>::insert(Node *&ptr, Node *&newNode) {
    if (ptr == nullptr)
        ptr = newNode;
    else if (ptr->data > newNode->data)
        insert(ptr->left, newNode);
    else
        insert(ptr->right, newNode);
}


template<class T>
string BST<T>::getLevelOrder() {
    response.str("");
    response.clear();
    getLevelOrder(root);
    return response.str();
}

template<typename T>
void BST<T>::getLevelOrder(Node *root) {
    // Base Case
    if (root == NULL) return;

    // Create an empty queue for level order traversal
    queue<Node *> q;
    // Enqueue Root and initialize height
    q.push(root);
    while (q.empty() == false) {
        // Print front of queue and remove it from queue
        Node *node = q.front();
        response << node->data << " ";
        q.pop();

        /* Enqueue left child */
        if (node->left != NULL)
            q.push(node->left);

        /*Enqueue right child */
        if (node->right != NULL)
            q.push(node->right);
    }
}


template<class T>
//copy constructor
BST<T>::BST(const BST<T> &) {
    root = nullptr;
}

#endif
