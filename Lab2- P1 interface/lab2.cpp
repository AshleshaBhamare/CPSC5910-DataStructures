// Ashlesha Bhamare
// lab2.cpp
// 09/22/2020
// Purpose: Create Booklist object, open and read from books.txt and tests
//           all functionality in the Booklist class

#include <iostream>
#include "BookList.h"
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

void printListState(const BookList &);

void printIndex(int, int);

int main() {

    const int SIZE = 100;
    string fileName;
    ifstream myFile;
    string line;

    BookList bookList(SIZE);

    cout << endl;

    cout << "Enter books file: ";
    cin >> fileName;

    int counter = 0;
    int isbnCounter = 1;

    ifstream myfile(fileName);
    string arr[3];
    if (myfile.is_open()) {
        while (getline(myfile, line, '\n')) {

            istringstream ss(line);
            string token;

            while(getline(ss, token, ',')) {
                arr[counter] = token;
                ++counter;
            }

            bookList.add(isbnCounter, arr[0],
                         arr[1], arr[2]);
            isbnCounter++;
            counter = 0;                    //resetting counter for next line
        }
    }
    cout << endl;

    cout << "# of books: " << bookList.size() << "\n";
    cout << endl;

    cout<< bookList.to_string();

    myfile.close();

    return 0;
}

void printListState(const BookList &obj) {
    if (obj.empty())
        cout << "List is empty";
    else
        cout << "List is not empty";
    cout << " and has a size of " << obj.size() << endl;
}
void printIndex(int val, int index) {
    if (index == -1)
        cout << val << " not found!" << endl;
    else
        cout << val << " found at index " << index << endl;


}
