// Ashlesha Bhamare
// BookList.h
// 09/22/2020

#ifndef LAB2_UPDATED_BOOKLIST_H
#define LAB2_UPDATED_BOOKLIST_H

#include <string>
#include <iostream>
using namespace std;
 struct Book {
    int isbnNumber;
    string authorName;
    string titleOfBook;
    string year;
};

class BookList {

public:

    BookList(int);                           // Constructor
    ~BookList();              // Destructor
    BookList(const BookList &);              // Copy constructor


    void add(int isbnNumbers, string authorName, string titleOfBook,
             string year);        // add element to array

    Book get(int) const;                 // find element in array; return index
                                         // where found or -1 if not found
    bool empty() const;                  // determines if list is empty or not

    int size() const;                    // number of elements in array

    string to_string() const;            // returns string representation of

private:
    Book *list;                          // Pointer to the array
    int capacity;                         // capacity of array
    int numElements;                      // Number of elements
    void resize();                        // resize array (when full)



};

#endif //LAB2_UPDATED_BOOKLIST_H
