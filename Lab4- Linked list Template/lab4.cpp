// AUTHOR:  Ashlesha Bhamare
// PROGRAM: lab4.cpp
// DATE:    10/13/2020
// PURPOSE: This program creates an array of integers and doubles,populates the
//          list with array elements and displays last negative value of the
//          array.
// INPUT:   LinkedList.h
// PROCESS: Run the program
// OUTPUT:  Prints the list with array elements and prints last negative value

#include <iostream>
#include "LinkedList.h"
using namespace std;

int main()
{
    //creating a linked list of integers
    LinkedList<int> list1;

    //creating an array, and populating list with array elements
    int arr[] = {3,-2,5,12,-2,-4,5};

    for(int i = 0; i < 7; i++)
    {
        list1.appendNode(arr[i]);
    }

    //displaying list values and printing last negative value
    cout << "\nLinked list values: ";

    cout << list1.to_string();

    cout << "Last negative number: " << list1.getlastNegative() << endl;

    //creating a linked list of doubles, doing the same steps.
    LinkedList<double> list2;

    double arr2[] = {-3.2,2.14,-5.7,-12.01,-2.99,4.6,5.2};

    for(int i = 0; i < 7; i++)
    {
        list2.appendNode(arr2[i]);
    }

    cout << "\nLinked list values: ";

    cout << list2.to_string();

    cout << "Last negative number: " << list2.getlastNegative() << endl;

    return 0;
}
