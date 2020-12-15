// Ashlesha Bhamare
// HashTable.h
// 11/10/2020
// Specification and Implementation file for the HashTable class
// having different public functions like put, get, contains, size and to_string
// and private function heapify

#ifndef LAB6_HASHTABLE_H
#define LAB6_HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include<iostream>

using namespace std;


class HashTable {
public:

    HashTable(int capacity);                                // Constructor

    ~HashTable();                                           // Destructor

    int put(int key, int value);
    // This function associates the specified value with the specified key
    // in this HashTable
    // precondition:
    // postcondition: Returns value associated with specified key

    int get(int key);
    // This function returns the value to which the specified key is mapped,
    // or -1 if this HashTable contains no mapping for the key.
    // HashTable contains no mapping for the key.
    // precondition: Must have key added
    // postcondition: Returns the value for specified key

    bool contains(int key);
    // This function returns true if this HashTable contains a mapping for
    // the specified key.
    // precondition: keys should be added into the hashtable
    // postcondition: returns true if this HashTable contains a mapping for
    // the specified key.

    int size();
    // This function returns the number of unique keys stored in the table.
    // precondition: keys should be added into the hashtable
    // postcondition: Returns the number of unique keys stored in the tabl

    bool empty();
    // Returns true if the HashTable is empty.
    // precondition: Hashtable should be empty
    // postcondition: Return true if the hashtable is empty

private:
    struct Bucket {
        int key;
        int value;
    };

    const int emptyBucketHash = -9999;               // To hold emptyBucketHash
    int capacity;                                    // To hold capacity

    int size_;                                       // To hold Size
    Bucket* hashTable;                               // array to hold hashtable

    int getHash(int key);
    // Calculates the hash function for the given key
    // precondition: key should be given
    // postcondition: returns the value of hash function

    int linearProbForHash(int hash);
    // This function returns new hash for a bucket on collision
    // precondition: collision should be present
    // postcondition: returns new hash for a bucket on collision
};

HashTable::HashTable(int capacity) {
    this->capacity = capacity;
    size_ = 0;
    hashTable=new Bucket[capacity];

    for(int i=0;i<capacity;i++)
    {
        hashTable[i]=Bucket{emptyBucketHash,0};
    }
}

HashTable::~HashTable() {
        delete[] hashTable;
}

int HashTable::put(int key, int value) {

    Bucket temp;

    if(size()==capacity) {
        cout << "HashTable is full, can not add more values!"<<endl;
        return -1;
    }

    int hash=getHash(key);
    temp=hashTable[hash];

    if(temp.key==emptyBucketHash)//checking if bucket is empty
    {
        hashTable[hash] = Bucket{key, value};
        size_++;
    }
    else if (temp.key==key)//updating existing bucket with new value
    {
        temp.value=value;
        hashTable[hash]=temp;
    }

    else
    {
        int newHash=linearProbForHash(hash);
        hashTable[newHash]= Bucket{key, value};
        size_++;
    }

    return -1;
}

int HashTable::get(int key) {
    Bucket temp;

    int hash=getHash(key);

    temp=hashTable[hash];
    if(temp.key==key)
        return temp.value;

    else
    {
        for(int i=hash;i<capacity;i++)
        {
            temp=hashTable[i];
            if(temp.key==key)
            {
                return temp.value;
            }
        }

        return -1;
    }

}

bool HashTable::contains(int key) {
    Bucket temp;

    int hash=getHash(key);

    temp=hashTable[hash];
    if(temp.key==key)
        return temp.value;

    else
    {
        for(int i=hash;i<capacity;i++)
        {
            temp=hashTable[i];
            if(temp.key==key)
            {
                return true;
            }
        }

        return false;
    }

}

int HashTable::size() {
    return size_;
}

bool HashTable::empty() {
    if (size() == 0) {
        return true;
    }
    return false;
}

int HashTable::getHash(int key) {
    int hash = (key % capacity)+1 ;
    return hash;
}

int HashTable::linearProbForHash(int hash) {
    Bucket temp;
    for(int i=hash;i<capacity;i++)
    {
        temp=hashTable[i];
        if(temp.value==0)
            return i;

    }
    return -1;
}

#endif //LAB6_HASHTABLE_H