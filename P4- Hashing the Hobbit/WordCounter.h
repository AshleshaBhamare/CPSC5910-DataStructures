// Ashlesha Bhamare
// WordCounter.h
// 11/21/2020
// Specification and Implementation file for the WordCounter class
// having different public functions like addWord, removeWord, getCapacity,
// getWordCount, getUniqueWordCount, getTotalWordCount, empty and private
// function like getHashKey.

#ifndef P4_WORDCOUNTER_H
#define P4_WORDCOUNTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include<iostream>

using namespace std;

class WordCounter {
public:
    WordCounter();
    // Default Constructor

    WordCounter(int capacity);
    // Constructor that takes capacity as a parameter

    ~WordCounter();
    // Destructor

    WordCounter(const WordCounter &table);
    //Copy constructor

    WordCounter &operator=(const WordCounter &rhs);
    // Overloaded Assignment operator

    int addWord(const string &word) ;
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
    const int defaultSize = 500;                   // To hold defaultSize
    int uniqueWordCount = 0;                       // To hold uniqueWordCount
    int capacity = 0;                              // To hold capacity
    int totalWordCount = 0;                        // To hold totalWordCount

    struct LinkedListNode{
        string word;
        int wordCount=1;
        LinkedListNode *next;
    };

    LinkedListNode **hashTable;

    int getHashKey(const std::string &word) const;
    // To find hashKey
    // precondition: the woed should be added
    // postcondition: Returns the hashKey

};

WordCounter::WordCounter() {
    hashTable = new LinkedListNode*[defaultSize];
    for (int i = 0; i < defaultSize; i++)
        hashTable[i] = nullptr;
    this->capacity = defaultSize;

}
WordCounter::WordCounter(int capacity) {
    hashTable = new LinkedListNode*[capacity];
    for (int i = 0; i < capacity; i++)
        hashTable[i] = nullptr;
    this->capacity = capacity;
}

WordCounter::~WordCounter() {
    delete *hashTable;
}

WordCounter::WordCounter(const WordCounter &table) {
    // Copy data elements
    uniqueWordCount = table.uniqueWordCount;
    totalWordCount = table.totalWordCount;
    capacity =table.capacity;

    // Allocate memory with new capacity
    hashTable = new LinkedListNode*[capacity];

    // Copy over elements from other
    for (int i = 0; i < capacity; i++) {
        *hashTable[i] = *table.hashTable[i];
    }
}

WordCounter &WordCounter::operator=(const WordCounter &table) {
    if (this != &table) {
        delete[] this->hashTable;

        //copy
        this->uniqueWordCount = table.uniqueWordCount;
        this->totalWordCount = table.totalWordCount;
        this->capacity = table.capacity;

        // re allocate memory
        this->hashTable = new LinkedListNode*[capacity];

        // Copy over elements from other hashtable
        for (int i = 0; i < capacity; i++) {
            *this->hashTable[i] = *table.hashTable[i];
        }
    }
    return *this;
}


int WordCounter::addWord(const string &word)  {
    int result = 0;
    totalWordCount++;
    if (getWordCount(word) == 0) {
        int hashKey =getHashKey(word);
        LinkedListNode* node = new LinkedListNode();
        node->word=word;
        if (hashTable[hashKey] != nullptr) {  // check if bucket is occupied
            LinkedListNode* temp = hashTable[hashKey];

            hashTable[hashKey] = node;
            hashTable[hashKey]->next = temp;
        }
        else {
            hashTable[hashKey] = node;
        }
        uniqueWordCount++;
        result = hashTable[hashKey]->wordCount;
    }
    else {
        int hashKey =getHashKey(word);
        LinkedListNode* curr = hashTable[hashKey];
        while (curr->word != word)
            curr = curr->next;
        result = curr->wordCount + 1;
        curr->wordCount++;
    }
    return result;
}

bool WordCounter ::removeWord(const string &word) {
    if (getWordCount(word) == 0)
        return false;
    int hashKey = getHashKey(word);
    LinkedListNode * curr = hashTable[hashKey];

    // check if the value is first in list
    if (curr->word == word) {
        totalWordCount = totalWordCount - curr->wordCount;
        hashTable[hashKey] = curr->next;
    }
    else {
        LinkedListNode* prev = curr;
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
int WordCounter::getCapacity() const
{
    return this->capacity;
}


int WordCounter::getWordCount(const string &word)  {
    int result = 0;
    int hashKey = getHashKey(word);
    LinkedListNode* curr = hashTable[hashKey];
    while (curr != nullptr) {
        if (curr->word == word) {
            result = curr->wordCount;
            break;
        }
        curr = curr->next;
    }
    return result;

}

int WordCounter::getUniqueWordCount() const  {
    return uniqueWordCount;
}


int WordCounter::getTotalWordCount() const {
    return totalWordCount;
}

bool WordCounter::empty() const
{
    if(totalWordCount==0)
        return true;
    else
    return false;
}

int WordCounter::getHashKey(const string &word) const {

    hash<string> hashKey;

    size_t hashCode = hashKey(word);
    int index = hashCode % capacity;
    return index;

}

#endif