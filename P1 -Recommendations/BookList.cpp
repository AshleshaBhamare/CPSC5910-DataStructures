//AUTHOR:   Ashlesha Bhamare
//FILENAME: BookList.cpp
//DATE:     09/29/2020
//PURPOSE:  This program keeps the track of the information about each book in
//          the system like ISBN number, Author, Title, Year. Also able to add
//          book to the list of books.


#include "BookList.h"
#include <sstream>

BookList::BookList(int cap)
{
    list = new Book[cap];
    capacity = cap;
    numElements = 0;
}

BookList::~BookList()
{
    delete[] list;
}

BookList::BookList(const BookList &obj)
{
    // assign numElements and capacity (from obj)
    capacity = obj.capacity;
    numElements = obj.numElements;

    // allocate memory based on new capacity
    list = new Book[capacity];

    // copy over elements (from obj)
    for (int i = 0; i < numElements; i++)
        list[i] = obj.list[i];
}


void BookList::add(int isbnNumber, string authorName, string titleOfBook,
                   string year)
{
    Book book = {isbnNumber, authorName, titleOfBook, year};

    if (numElements >= capacity)
        resize();
    list[numElements] = book;
    numElements++;
}

bool BookList::empty() const
{
    return numElements == 0;
}

int BookList::size() const
{
    return numElements;
}

void BookList::resize()
{
    // update capacity
    capacity *= 2;

    // create new array based on updated capacity
    Book *tempArr = new Book[capacity];

    // copy old array values to new array
    for (int i = 0; i < numElements; i++)
        tempArr[i] = list[i];

    // delete old array
    delete[] list;

    // reassign old array to new array
    list = tempArr;
}

string BookList::to_string() const
{
    stringstream ss;
    for (int i = 0; i < numElements; i++)
        ss << list[i].isbnNumber << ", " << list[i].authorName << ", "
           << list[i].titleOfBook << ", " << list[i].year << "\n";
    return ss.str();
}

string BookList::get(int i) const
{
    stringstream ss;
    ss << list[i].isbnNumber << ", " << list[i].authorName << ", "
       << list[i].titleOfBook << ", " << list[i].year;
    return ss.str();
}


int BookList::getIsbnNumber(int i) const
{
   return list[i].isbnNumber;
}



