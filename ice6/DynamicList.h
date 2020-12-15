// Sheila Oh
// File: DynamicList.h
// Date: 9/15/20

#ifndef WEEK1_DynamicList_H
#define WEEK1_DynamicList_H

#include <string>
#include <sstream>
using namespace std;
template <typename T>
class DynamicList {
public:
    DynamicList(int);           // Constructor
    ~DynamicList();             // Destructor
    DynamicList(const DynamicList &);               // Copy constructor
    DynamicList& operator=(const DynamicList &);    // Overloaded = operator
    void add(T);          // add element to array
    int get(T) const;     // find element in array; return index
                            // where found or -1 if not found
    bool empty() const;     // determines if list is empty or not
    int size() const;       // number of elements in array
    string to_string() const;   // returns string representation of
                                // of the DynamicList class
private:
    int * list;             // Pointer to the array
    int capacity;           // capacity of array
    int numElements;        // Number of elements
    void resize();          // resize array (when full)
};
template <typename T>
DynamicList<T>::DynamicList(int cap) {
    list = new int[cap];
    capacity = cap;
    numElements = 0;
}
template <typename T>
DynamicList<T>::~DynamicList() {
    delete [] list;
}
template <typename T>
DynamicList<T>::DynamicList(const DynamicList &obj) {
    // assign numElements and capacity (from obj)
    capacity = obj.capacity;
    numElements = obj.numElements;

    // allocate memory based on new capacity
    list = new int[capacity];

    // copy over elements (from obj)
    for (int i = 0; i < numElements; i++)
        list[i] = obj.list[i];
}
template <typename T>
DynamicList<T>& DynamicList<T>::operator=(const DynamicList &obj) {
    if (this != &obj) {
        // deallocate memory
        delete [] list;

        // assign numElements and capacity (from obj)
        capacity = obj.capacity;
        numElements = obj.numElements;

        // allocate memory based on new capacity
        list = new int[capacity];

        // copy over elements (from obj)
        for (int i = 0; i < numElements; i++)
            list[i] = obj.list[i];
    }
    return *this;
}
template <typename T>
void DynamicList<T>::add(T el) {
    if (numElements >= capacity)
        resize();
    list[numElements] = el;
    numElements++;
}
template <typename T>
int DynamicList<T>::get(T el) const {
    for (int i = 0; i < numElements; i++) {
        if (list[i] == el)
            return i;
    }
    return -1;
}
template <typename T>
bool DynamicList<T>::empty() const {
    return numElements == 0;
}
template <typename T>
int DynamicList<T>::size() const {
    return numElements;
}
template <typename T>
string DynamicList<T>::to_string() const {
    stringstream ss;
    for (int i = 0; i < numElements; i++)
        ss << list[i] << " ";
    return ss.str();
}
template <typename T>
void DynamicList<T>::resize() {
    // update capacity
    capacity *= 2;

    // create new array based on updated capacity
    int * tempArr = new int[capacity];

    // copy old array values to new array
    for (int i = 0; i < numElements; i++)
        tempArr[i] = list[i];

    // delete old array
    delete [] list;

    // reassign old array to new array
    list = tempArr;
}
#endif //WEEK1_DynamicList_H
