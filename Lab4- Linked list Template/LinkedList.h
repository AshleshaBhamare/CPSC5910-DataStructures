// Ashlesha Bhamare
// LinkedList.h
// 10/13/2020


#ifndef LAB4_LINKEDLIST_H
#define LAB4_LINKEDLIST_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template<typename T>
class LinkedList
{

private:
    struct Node
    {
        T data;
        Node * next;
    };
    Node * head;

public:
    LinkedList();                                  // Constructor
    ~LinkedList();                                 // Destructor
    void appendNode(T);                            // To append Node
    T getlastNegative(Node*node);                  // Helper function
    T getlastNegative();                           // To get last negative
    string to_string() const;

};

template<typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Node * curr;
    while (head != nullptr) {
        curr = head;
        head = head->next;
        delete curr;
    }
}

template<typename T>
void LinkedList<T>::appendNode(T d)
{
    Node * curr;	        // helper Node that allows me to traverse the list
    Node * newNode = new Node;
    newNode->data = d;
    newNode->next = nullptr;

    if (head == nullptr)
        head = newNode;
    else {
        curr = head;
        while (curr->next != nullptr)
            curr = curr->next;
        curr->next = newNode;
    }
}

template<typename T>
T LinkedList<T>::getlastNegative(Node*node)
{
    //Checking if node is NULL
    if(node==NULL)
    {
        return 0;
    }
    //Checking if current node's value is negative
    if(node->data<0)
    {
        //Checking if there is no next negative value
        if(getlastNegative(node->next)==0)
        {
            return node->data;
        }
    }
    //Checking the next node
    return getlastNegative(node->next);
}

template<typename T>
T LinkedList<T>::getlastNegative()
{
    //using the recursive helper method, finding the last negative number
    return getlastNegative(head);
}

template<typename T>
string LinkedList<T>::to_string() const {
    stringstream ss;
    Node *curr = head;
    while (curr) {
        ss << curr->data << "  ";
        curr = curr->next;
    }
    ss << "\n";
    return ss.str();
}

#endif //LAB4_LINKEDLIST_H