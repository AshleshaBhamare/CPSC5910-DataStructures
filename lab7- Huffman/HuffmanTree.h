// Ashlesha Bhamare
// HuffmanTree.h
// 11/14/2020
// Specification file for the HuffmanTree class
// having different public functions like createCodeTree, encodeFile,
// decodeFile, displayCode and private functions  traverseAndPrint,
// printHuffmanCode, getHuffmanCode.


#ifndef LAB7_HUFFMANTREE_H
#define LAB7_HUFFMANTREE_H

#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <bitset>
#include "BST.h"

using namespace std;

class CharFreq {
public:
    CharFreq() : letter('\0'), frequency(0), encoding("") { }
    CharFreq(unsigned char l, float f) :letter(l), frequency(f), encoding("") { }

    unsigned char letter;
    float frequency;
    string encoding;

    bool operator>(const CharFreq &rhs) const {
        return frequency > rhs.frequency;
    }
};

class HuffmanTree : BST<CharFreq> {
public:
    HuffmanTree() {}
    bool createCodeTree(string filename);
    bool encodeFile(string originalFilename, string outputFilename);
    bool decodeFile(string filename);
    void displayCode(ostream &out);
private:
    inline int traverseAndPrint(string &bits, int i) {
        return traverseAndPrint(bits, i, root);
    }
    int traverseAndPrint(string &bits, int i, BSTNode *cur);
    void printHuffmanCode(BSTNode * root, string str);
    string getHuffmanCode(BSTNode *root, char c,int frequency);
    string fileText="";
};

ostream& operator<<(ostream &out, HuffmanTree &code);

#endif //LAB7_HUFFMANTREE_H
