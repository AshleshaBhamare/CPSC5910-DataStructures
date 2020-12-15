//AUTHOR:   Ashlesha Bhamare
//FILENAME: RatingList.cpp
//DATE:     09/29/2020
//PURPOSE:  This program keeps the track of the Ratings which has
//          three pieces of information like Book, member and Rating.


#include "RatingList.h"
#include <string>
#include <sstream>

using namespace std;

RatingList::RatingList(int rows, int columns)
{

    ratingsArray = new int*[rows];
    col = columns;
    row = rows;
    capacity = rows;
    for (int i = 0; i < rows; i++)
    {
        ratingsArray[i] = new int[columns];
    }
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<col;j++)
        {
            ratingsArray[i][j]=0;
        }
    }
}

RatingList::~RatingList()
{
    for (int i = 0; i < row; i++)
        delete[] ratingsArray[i];
    delete[] ratingsArray;
}

void RatingList::addOrUpdate(int isbnNumber, int accountNumber, int
                                                                ratingValue)
{


    ratingsArray[accountNumber-1][isbnNumber-1] = ratingValue;
}

bool RatingList::empty() const
{
    return numElements == 0;
}

int RatingList::size() const
{
    return numElements;
}

void RatingList::resize()
{
    // update capacity
    capacity *= 2;

    // create new array based on updated capacity
    Rating *tempArr = new Rating[capacity];

    // copy old array values to new array
    for (int i = 0; i < numElements; i++)
        tempArr[i] = list[i];

    // delete old array
    delete[] list;

    // reassign old array to new array
    list = tempArr;
}

int RatingList::getRating(int accountNumber, int isbnNumber) const
{
    return ratingsArray[accountNumber-1][isbnNumber-1];
}

string RatingList::to_string(int rows,int columns) const
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<columns;j++)
        {
            cout<<ratingsArray[i][j]<< " ";

        }
        cout<<endl;
    }
    return "";
}



