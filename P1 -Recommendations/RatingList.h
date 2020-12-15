// Ashlesha Bhamare
// RatingList.h
// 09/29/2020

#ifndef P1_RATINGLIST_H
#define P1_RATINGLIST_H

using namespace std;

#include <string>
#include <iostream>

class RatingList {

public:
    RatingList(int rows,int columns);                           // Constructor
    ~RatingList();              // Destructor



    //void add(int);        // add element to array
    void addOrUpdate(int isbnNumber, int accountNumber, int ratingValue);
    // add element to array


    string to_string(int rows,int columns) const;

    int  getRating(int accountNumber,int isbnNumber) const;


    bool empty() const;                  // determines if list is empty or not

    int size() const;                    // number of elements in array



private:
    struct Rating {
        int isbnNumber;
        int accountNumber;
        int ratingValue;

    };
    Rating *list;                          // Pointer to the array
    int **ratingsArray;
    int col;                         // columns of 2d array
    int row;                         // rows of 2d array
    int capacity;
    int numElements;                      // Number of elements
    void resize();                        // resize array (when full)


};


#endif //P1_RATINGLIST_H
