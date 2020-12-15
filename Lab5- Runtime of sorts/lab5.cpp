// AUTHOR:  Ashlesha Bhamare
// PROGRAM: lab5.cpp
// DATE:    10/27/2020
// PURPOSE: To measure and graph the runtimes of various sorting algorithms.
// INPUT:   Sort.h
// PROCESS: To test values between 40,000 and 20,480,000 for various
//          sorting algorithms like Heapsort, Mergesort, Array sort, Quicksort,
//          and Insertion sort
//
// OUTPUT:  Measure and prints the runtimes of various sorting algorithms.

#include <iostream>
#include <time.h>
#include <vector>
#include"Sort.h"
#define maxRangeForInsertionSort 640000

using namespace std;


vector<long> initialiseInput(int size, vector<long> input);
// To initialize input
// IN: int size, vector<long> input
// MODIFY: none
// OUT: return the input

void displayRunTimes(vector<long> input);
// To display runtimes
// IN: vector<long> input
// MODIFY: none
// OUT: none

template<typename T>
vector<T> create_copy(vector<T> const &vec) {
    vector<T> v(vec);
    return v;
}

void displayRunTimes(vector<long> vecOfRandomNums) {

    clock_t t;

    // creating copy of input to  keep input same for all
    // sorting algorithms
    vector<long> vectorCopy = create_copy(vecOfRandomNums);
    t = clock();// testing quick  sort
    quicksort(vectorCopy.begin(), vectorCopy.end());
    t = clock() - t;
    printf("It took me %f clocks (%f seconds) for Quicksort.\n", (float)t,
                                                 ((float) t)/CLOCKS_PER_SEC);

    //vecOfRandomNums = initialiseInput(size, vecOfRandomNums);
    vectorCopy = create_copy(vecOfRandomNums);
    t = clock();// testing heap sort
    heapsort(vectorCopy.begin(), vectorCopy.end());
    t = clock() - t;
    printf("It took me %f clocks (%f seconds) for Heapsort.\n", (float)t, (
                                                  (float) t) /CLOCKS_PER_SEC);


    vectorCopy = create_copy(vecOfRandomNums);
    t = clock();// testing merge sort
    mergesort(vectorCopy.begin(), vectorCopy.end());
    t = clock() - t;
    printf("It took me %f clocks (%f seconds) for Mergesort.\n", (float)t, (
                                                  (float) t) /CLOCKS_PER_SEC);

    // vecOfRandomNums = initialiseInput(size, vecOfRandomNums);
    vectorCopy = create_copy(vecOfRandomNums);
    t = clock();// testing intro  sort
    sort(vectorCopy.begin(), vectorCopy.end());
    t = clock() - t;
    printf("It took me %f clocks (%f seconds) for STL's IntroSort."
           "\n", (float)t, ((float) t) / CLOCKS_PER_SEC);


    vectorCopy = create_copy(vecOfRandomNums);
    if (vectorCopy.size() <= maxRangeForInsertionSort) {
        t = clock();
        insertionSort(vectorCopy.begin(), vectorCopy.end());
        t = clock() - t;
        printf("It took me %f clocks (%f seconds) for Insertion Sort."
               "\n", (float)t, ((float) t) / CLOCKS_PER_SEC);
    }

    cout<<endl;

}

vector<long> initialiseInput(int size, vector<long> input) {
    input.clear();//resetting input vector
    srand((unsigned) time(NULL));
    for (int i = 0; i < size; i++) {
        long b = rand() % size + 1;
        input.push_back(b);
    }
    return input;
}


int main() {
    // Initialize a vector with 10 ints of value 0
    vector<long> vecOfRandomNums;
    vecOfRandomNums = initialiseInput(40000, vecOfRandomNums);
    cout << "\nSorting 40000 values .." << endl;
    displayRunTimes(vecOfRandomNums);


    vecOfRandomNums=initialiseInput(80000, vecOfRandomNums);
    cout << "\nSorting 80000 values .." << endl;
    displayRunTimes(vecOfRandomNums);


    vecOfRandomNums=initialiseInput(160000, vecOfRandomNums);
    cout << "\nSorting 160000 values .." << endl;
    displayRunTimes(vecOfRandomNums);


    cout << "\nSorting 320000 values .." << endl;
    vecOfRandomNums=initialiseInput(320000, vecOfRandomNums);
    displayRunTimes(vecOfRandomNums);

    cout << "Sorting 640000 values .." << endl;
    vecOfRandomNums=initialiseInput(640000, vecOfRandomNums);
    displayRunTimes(vecOfRandomNums);

    cout << "Sorting 1280000 values .." << endl;
    vecOfRandomNums=initialiseInput(1280000, vecOfRandomNums);
    displayRunTimes(vecOfRandomNums);


    cout << "Sorting 2560000 values .." << endl;
    vecOfRandomNums=initialiseInput(2560000, vecOfRandomNums);
    displayRunTimes(vecOfRandomNums);

    cout << "Sorting 5120000 values .." << endl;
    vecOfRandomNums=initialiseInput(5120000, vecOfRandomNums);
    displayRunTimes(vecOfRandomNums);

    cout << "Sorting 10240000 values .." << endl;
    vecOfRandomNums= initialiseInput(10240000, vecOfRandomNums);
    displayRunTimes(vecOfRandomNums);


    cout << "Sorting 20480000 values .." << endl;
    vecOfRandomNums=initialiseInput(20480000, vecOfRandomNums);
    displayRunTimes(vecOfRandomNums);

    return 0;
}
