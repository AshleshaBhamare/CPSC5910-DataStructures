// AUTHOR:  Ashlesha Bhamare
// PROGRAM: lab6.cpp
// DATE:    11/10/2020
// PURPOSE: This program implements a hash table (HashTable) using the
//          following hash function: h(k) = k % capacity
// INPUT:   HashTable.h.
// PROCESS: Create a HashTable of size 4093.
//          Insert 4083 unique integers into the table and verify that the
//          size() is now 4083. Retrieve the values mapped to keys 50184 and 77
//          and display to user; they map to 123 and 126 respectively. Also
//          retrieve values for keys that do not exist in the table, they
//          should be -1.
// OUTPUT:  Display the results of the contains() method for the values used in
//          step 4.

#include <iostream>
#include"HashTable.h"

static int const TOTAL_COUNT = 4093;

void welcomeMessage();
// To print welcomeMessage

void goodByeMessage();
// To print goodByeMessage

int main()
{

    welcomeMessage();

    HashTable *hashTable = new HashTable(TOTAL_COUNT);

    cout<<"Hashtable empty: "<<(hashTable->empty()==1?"true":"false")<<endl;

    cout << "\nCreating new Hashtable with  capacity 4093 and inserting \n"
          "4083 random key-value pairs with unique keys.. done.\n" << endl;


    for (int i = 1; i <= (TOTAL_COUNT-10); i++) {
        int j = i+200;
        hashTable->put(i, j);
    }

    cout << "Hashtable Size: " << hashTable->size() << endl;


    cout << "\nInserting 10 additional key-values.." << endl;

    cout << "(1179 , 120)" << endl;
    hashTable->put(1179, 120);
    cout << "(9702 , 121)" << endl;
    hashTable->put(9702, 121);
    cout << "(7183 , 122)" << endl;
    hashTable->put(7183, 122);
    cout << "(50184 , 123)" << endl;
    hashTable->put(50184, 123);
    cout << "(4235 , 124)" << endl;
    hashTable->put(4235, 124);
    cout << "(644 , 125)" << endl;
    hashTable->put(644, 125);
    cout << "(77 , 126)" << endl;
    hashTable->put(77, 126);
    cout << "(3077 , 127)" << endl;
    hashTable->put(3077, 127);
    cout << "(23477 , 128)" << endl;
    hashTable->put(23477, 128);
    cout << "(90777 , 129)" << endl;
    hashTable->put(90777, 129);

    /*cout<<"\nHashtable Size: "<<hashTable->size()
    <<endl;*/

    cout << "\nTesting contains.." << endl;
    cout << "contains(50184): "
    << (hashTable->contains(50184) == 1 ? "true" : "false") << endl;
    cout << "contains(   77): "
    << (hashTable->contains(77) == 1 ? "true" : "false") << endl;
    cout << "contains(    0): "
    << (hashTable->contains(0) == 1 ? "true" : "false") << endl;
    cout << "contains(   -1): "
    <<(hashTable->contains(-1) == 1 ? "true" : "false") << endl;

    cout << "\nTesting get.." << endl;
    cout << "get(50184): " << hashTable->get(50184) << endl;
    cout << "get(   77): " << hashTable->get(77) << endl;
    cout << "get(    0): " << hashTable->get(0) << endl;
    cout << "get(   -1): " << hashTable->get(-1) << endl;

    /* Testing for hashtable full
    cout << "(4093 , 300)" << endl;
    hashTable->put(4093, 300);
    cout << "( 8186, 121)" << endl;
    hashTable->put(8186, 400);
    cout << "(78, 126)" << endl;
    hashTable->put(78 ,6);
    cout << "(3078, 127)" << endl;
    hashTable->put(3078,127);
    cout << "(23478, 128)" << endl;
    hashTable->put(23478,128);
    cout << "(90778, 129)" << endl;
    hashTable->put(90778, 129);
    cout << "(23479, 128)" << endl;
    hashTable->put(23479,128);
    cout << "(90779, 129)" << endl;
    hashTable->put(90779, 129);

    cout<<"\nThe size of hash table after insertion is:"<<hashTable->size()
    <<endl;*/

    goodByeMessage();

    return 0;
}

void welcomeMessage()
{
    cout << "\nWelcome to the HashTable testing program.\n\n";
}

void goodByeMessage()
{
    cout << "\nThanks for using the HashTable testing program. Goodbye.\n";
}