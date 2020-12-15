// Ashlesha Bhamare
// WordCounter.h
// 11/21/2020
// Specification and Implementation file for the WordCounter class
// having different public functions like addWord, removeWord, getCapacity,
// getWordCount, getUniqueWordCount, getTotalWordCount, empty and private
// function like getHashKey.

#ifndef P4X_WORDCOUNTERX_H
#define P4X_WORDCOUNTERX_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include<iostream>
#include<math.h>

using namespace std;


class WordCounterx {
public:
    WordCounterx();
    // Default Constructor

    WordCounterx(int capacity);
    // Constructor that takes capacity as a parameter

    ~WordCounterx();
    // Destructor

    WordCounterx(const WordCounterx &table);
    //Copy constructor

    WordCounterx &operator=(const WordCounterx &rhs);
    // Overloaded Assignment operator

    int addWord(const string &word);
    // Adds word to WordCounter. If the word is already added then it will
    // increment count
    // precondition: the word should be added
    // postcondition: add word to the wordCounter and increment the count

    bool removeWord(const string &word);
    // Remove the word
    // precondition: the word should be added
    // postcondition: remove word completely from hashtable

    int getCapacity() const;
    // To find capacity of hashtable
    // precondition: words should be added
    // postcondition:  Returns the capacity of the hash table.

    int getWordCount(const string &word);
    // To find count of word
    // precondition: words should be added
    // postcondition: Returns the count of the specified (passed in) word

    int getUniqueWordCount() const;
    // To find entries in the hash table
    // precondition: words should be added
    // postcondition: Returns the number of unique words encountered

    int getTotalWordCount() const;
    // To find he total number of words encountered,
    // precondition: words should be added
    // postcondition: Returns the total number of words encountered,
    // including duplicates

    bool empty() const;
    // To find is hashtable is empty
    // precondition: the hashtable should be empty.
    // postcondition: Returns true if no words have been added to the hash
    // table. Otherwise, returns false

private:
    const int defaultSize = 11;                   // To hold defaultSize
    int uniqueWordCount = 0;                       // To hold uniqueWordCount
    int capacity = 0;                              // To hold capacity
    int totalWordCount = 0;                        // To hold totalWordCount

    struct LinkedListNode {
        string word;
        int wordCount = 1;
        LinkedListNode *next;
    };

    LinkedListNode **hashTable;

    int getHashKey(const std::string &word) const;

    // To find hashKey
    // precondition: the woed should be added
    // postcondition: Returns the hashKey
    int isPrime(int n);

    int getNextPrime(int n);

    double getLoadFactor(int unique,int capacity);

};

WordCounterx::WordCounterx() {
    hashTable = new LinkedListNode *[defaultSize];
    for (int i = 0; i < defaultSize; i++)
        hashTable[i] = nullptr;
    this->capacity = defaultSize;

}

WordCounterx::WordCounterx(int capacity) {


    if (isPrime(capacity)) {
        hashTable = new LinkedListNode *[capacity];
        for (int i = 0; i < capacity; i++)
            hashTable[i] = nullptr;
        this->capacity = capacity;
    } else {
        capacity = getNextPrime(capacity);

        hashTable = new LinkedListNode *[capacity];
        for (int i = 0; i < capacity; i++)
            hashTable[i] = nullptr;
        this->capacity = capacity;

    }
}

WordCounterx::~WordCounterx() {
    delete *hashTable;
}

WordCounterx::WordCounterx(const WordCounterx &table) {
    // Copy data elements
    uniqueWordCount = table.uniqueWordCount;
    totalWordCount = table.totalWordCount;
    capacity = table.capacity;

    // Allocate memory with new capacity
    hashTable = new LinkedListNode *[capacity];

    // Copy over elements from other
    for (int i = 0; i < capacity; i++) {
        *hashTable[i] = *table.hashTable[i];
    }
}

WordCounterx &WordCounterx::operator=(const WordCounterx &table) {
    if (this != &table) {
        delete[] this->hashTable;

        //copy
        this->uniqueWordCount = table.uniqueWordCount;
        this->totalWordCount = table.totalWordCount;
        this->capacity = table.capacity;

        // re allocate memory
        this->hashTable = new LinkedListNode *[capacity];

        // Copy over elements from other hashtable
        for (int i = 0; i < capacity; i++) {
            *this->hashTable[i] = *table.hashTable[i];
        }
    }
    return *this;
}


int WordCounterx::addWord(const string &word) {
    int result = 0;

    totalWordCount++;

    if (getWordCount(word) == 0) {

        int hashKey = getHashKey(word);
        LinkedListNode *node = new LinkedListNode();
        node->word = word;
        if (hashTable[hashKey] != nullptr) {  // check if bucket is occupied
            LinkedListNode *temp = hashTable[hashKey];

            hashTable[hashKey] = node;
            hashTable[hashKey]->next = temp;
        } else {
            hashTable[hashKey] = node;
        }
        uniqueWordCount++;
        result = hashTable[hashKey]->wordCount;
    } else {
        int hashKey = getHashKey(word);
        LinkedListNode *curr = hashTable[hashKey];
        while (curr->word != word)
            curr = curr->next;
        result = curr->wordCount + 1;
        curr->wordCount++;
    }

    double loadFactor=getLoadFactor(uniqueWordCount,this->capacity);
    if(loadFactor>0.75) {
         int oldCapacity= this->capacity;
        int newCap = getNextPrime(this->capacity+1);
        newCap =getNextPrime(newCap+1);
        newCap =getNextPrime(newCap+1);
        newCap =getNextPrime(newCap+1);
        this->capacity=newCap;
        cout<<"Resizing:"<<loadFactor<<"> 0.75";
        cout<<"from "<<oldCapacity<<" to "<< this->getCapacity()<<endl;
    }
    return result;
}

bool WordCounterx::removeWord(const string &word) {
    if (getWordCount(word) == 0)
        return false;
    int hashKey = getHashKey(word);
    LinkedListNode *curr = hashTable[hashKey];

    // check if the value is first in list
    if (curr->word == word) {
        totalWordCount = totalWordCount - curr->wordCount;
        hashTable[hashKey] = curr->next;
    } else {
        LinkedListNode *prev = curr;
        while (curr->word != word) {
            prev = curr;
            curr = curr->next;
        }
        totalWordCount = totalWordCount - curr->wordCount;
        prev->next = curr->next;
    }
    uniqueWordCount--;
    return true;

}

int WordCounterx::getCapacity() const {
    return this->capacity;
}


int WordCounterx::getWordCount(const string &word) {
    int result = 0;
    int hashKey = getHashKey(word);
    LinkedListNode *curr = hashTable[hashKey];
    while (curr != nullptr) {
        if (curr->word == word) {
            result = curr->wordCount;
            break;
        }
        curr = curr->next;
    }
    return result;

}

int WordCounterx::getUniqueWordCount() const {
    return uniqueWordCount;
}


int WordCounterx::getTotalWordCount() const {
    return totalWordCount;
}

bool WordCounterx::empty() const {
    if (totalWordCount == 0)
        return true;
    else
        return false;
}

int WordCounterx::getHashKey(const string &word) const {

    hash<string> hashKey;

    size_t hashCode = hashKey(word);
    int index = hashCode % capacity;
    return index;

}

int WordCounterx::isPrime(int n) {
    if (n <= 1)
        return false;
    if (n == 2)
        return true;

    for (int i = 2; i < sqrt(n); i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int WordCounterx::getNextPrime(int n) {
    while (!isPrime(n))
        n++;

    return n;
}

double   WordCounterx ::getLoadFactor(int uniqueWordCount,int capacity)  {
    return (round( uniqueWordCount * 1000) / 1000.0)
           / capacity;
}

#endif //P4X_WORDCOUNTERX_H
