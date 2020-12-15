
// AUTHOR:  Ashlesha Bhamare
// PROGRAM: p2x.cpp
// DATE:    10/20/2020
// PURPOSE: This program thoroughly test the functionality of the BST, Also ask
//          user for the file names to read.
// INPUT:   integers.dat, strings.dat
// PROCESS: Test the functionality of different methods.
// OUTPUT:  Prints the output of different functions of BST.

#include <iostream>
#include "BSTx.h"
#include <fstream>

using namespace std;

void welcomeMessage();
// To print welcomeMessage

void processInput();
// To processInput


int main() {
    welcomeMessage();

    processInput();
    cout << "\n\nGoodbye!\n";
    return 0;
}

void welcomeMessage() {
    cout << "\nWelcome\n(Lets test binary search tree operations!)" << endl;

}

void processInput() {
    BST<int> tree(30);
    string fileName = "";
    cout << " \nEnter integer file: ";
    cin >> fileName;
    ifstream infile(fileName);

    int a;
    cout << "Inserting in this order: ";
    while (infile >> a) {
        cout << a << " ";
        tree.insert(a);
    }
    cout << endl;
    cout << "\nwidth of this tree is: " << tree.getWidth();

    cout << "\nlevel-order: " << tree.getLevelOrder();
    cout << endl;

    string strFileName = "";
    cout << " \nEnter string file: ";

    BST<string> stringTree("stringTree");
    cin >> strFileName;
    ifstream inStrfile(strFileName);

    string node;
    cout << "Inserting in this order: ";
    while (inStrfile >> node) {
        cout << node << " ";
        stringTree.insert(node);
    }
    cout << endl;
    cout << "\nwidth of this tree is: " << stringTree.getWidth();

    cout << "\nlevel-order: " << stringTree.getLevelOrder();

}








