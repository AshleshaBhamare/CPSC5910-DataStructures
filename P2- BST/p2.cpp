// AUTHOR:  Ashlesha Bhamare
// PROGRAM: p2.cpp
// DATE:    10/20/2020
// PURPOSE: This program thoroughly test the functionality of the BST, Also ask
//          user for the file names to read.
// INPUT:   integers.dat, strings.dat
// PROCESS: Test the functionality of different methods.
// OUTPUT:  Prints the output of different functions of BST.

#include <iostream>
#include "BST.h"
#include <fstream>

using namespace std;

void welcomeMessage();
// To print welcome message
void processIntegerTree();
// To processIntegerTree
void processStringTree();
// To processStringTree

template<typename T>
void displayTreeDetails(BST<T> *tree);
// To displayTreeDetails
// IN: BST<T> *tree
// MODIFY: none
// OUT: none

template<typename T>
void displayTreeTraversals(BST<T> *tree);
// To displayTreeTraversals
// IN: BST<T> *tree
// MODIFY: none
// OUT: none

template<typename T>
void printLevelAndAncestors(BST<T> *tree);
// To printLevelAndAncestors
// IN: BST<T> *tree
// MODIFY: none
// OUT: none

void testIntegerTreeContains(BST<int> *tree);
// To testIntegerTreeContains
// IN: BST<int> *tree
// MODIFY: none
// OUT: none

void testIntegerTreeRemoval(BST<int> * tree);
// To testIntegerTreeRemoval
// IN: BST<int> *tree
// MODIFY: none
// OUT: none

void testIntegerTreeInsertion(BST<int> * tree);
// To testIntegerTreeInsertion
// IN: BST<int> *tree
// MODIFY: none
// OUT: none

void testStringTreeContains(BST<string> * tree);
// To testStringTreeContains
// IN: BST<string> *tree
// MODIFY: none
// OUT: none

void testStringTreeRemoval(BST<string> * tree);
// To testStringTreeRemoval
// IN: BST<string> *tree
// MODIFY: none
// OUT: none
void testStringTreeInsertion(BST<string> * tree);
// To testStringTreeInsertion
// IN: BST<string> *tree
// MODIFY: none
// OUT: none

void printLevelAndAncestorsOfStringTree(BST<string> *tree);
// To printLevelAndAncestorsOfStringTree
// IN: BST<string> *tree
// MODIFY: none
// OUT: none

bool is_number(const std::string &s);
// To check that is_number
// IN: const std::string &s
// MODIFY: none
// OUT: bool

template<typename T>
int getLevelOfNode(BST<T> *tree, int data);
// To getLevelOfNode
// IN: BST<T> *tree, int data
// MODIFY: none
// OUT: level of nodes

int getLevelOfStringNode(BST<string> *tree, string data);
// To getLevelOfStringNode
// IN: BST<string> *tree, string data
// MODIFY: none
// OUT: level of string node


int main() {
    welcomeMessage();
    cout << "** CREATE BST **" << endl;
    processIntegerTree();
    processStringTree();

    cout<<"\n\nGoodbye!\n";
    return 0;
}

void welcomeMessage() {
    cout << "\nWelcome\n(Lets test binary search tree operations!)\n" << endl;

    cout << "******************************" << endl;
    cout << "* INTEGER BINARY SEARCH TREE *" << endl;
    cout << "******************************" << endl;
    cout << endl;
}

void processIntegerTree()
{

    BST<int> tree(30);
    displayTreeDetails(&tree);
    string fileName="";

    cout << "\nEnter integer file: ";
    cin>>fileName;
    ifstream infile(fileName);

    cout << "\n** TEST INSERT **" << endl;
    cout << "Inserting in the order: ";
    int a;
    while (infile >> a) {
        cout << a << " ";
        tree.insert(a);
    }

    displayTreeDetails(&tree);

    cout << "\n**  TEST TRAVERSALS  **" << endl;
    displayTreeTraversals(&tree);

    printLevelAndAncestors(&tree);
    testIntegerTreeContains(&tree);
    testIntegerTreeRemoval(&tree);
    testIntegerTreeInsertion(&tree);

}

void processStringTree() {
    cout << "\n******************************" << endl;
    cout << "* test string BST *" << endl;
    cout << "******************************" << endl;

    cout << "\n** CREATE BST **";
    BST<string> stringTree("stringTree");
    displayTreeDetails(&stringTree);
    string fileName="";
    cout << " \nEnter String file: ";
    cin>>fileName;
    ifstream inStrfile(fileName);

    cout << "\n**TEST INSERT**" << endl;
    cout << "Inserting in this order: ";
    string node;
    while (inStrfile >> node) {
        cout << node << " ";
        stringTree.insert(node);
    }
    displayTreeDetails(&stringTree);

    cout << "\n**  TEST TRAVERSALS  **" << endl;
    displayTreeTraversals(&stringTree);

    printLevelAndAncestorsOfStringTree(&stringTree);
    testStringTreeContains(&stringTree);
    testStringTreeRemoval(&stringTree);
    testStringTreeInsertion(&stringTree);

}

template<typename T>
void displayTreeDetails(BST<T> *tree) {
    cout << "\n# of nodes: " << tree->size() << endl;
    cout << "# of leaves: " << tree->getLeafCount() << endl;
    cout << "BST height: " << tree->getHeight() << endl;
    cout << "BST empty? " << (tree->empty() ? "true" : "false") << endl;
}

template<typename T>
void displayTreeTraversals(BST<T> *tree) {

    cout << "pre-order: " << tree->getPreOrderTraversal();
    cout << "\nin-order:  " << tree->getInOrderTraversal();
    cout << "\npost-order: " << tree->getPostOrderTraversal();

    cout << endl;
}

template<typename T>
void printLevelAndAncestors(BST<T> *tree) {
    string str = tree->getPreOrderTraversal();
    stringstream temp;
    string word = "";

    cout << "\n** TEST LEVEL & ANCESTORS **";
    int data = 0;
    for (auto s : str) {
        if (s == ' ') {
            if (is_number(word)) {
                stringstream temp(word);
                temp >> data;
                cout << "\nlevel(" << word << "): " <<
                                          getLevelOfNode(tree,data) << ",\t";
                cout << "ancestors(" << word << "): " << tree->getAncestors
                                                                    (data) ;
            }

            word = "";
        } else {
            word = word + s;
        }
    }

}

void testIntegerTreeContains(BST<int> * tree)
{
    cout <<"\n\n** TEST CONTAINS **" << endl;
    int testInputSize=8;

    int testInput[] = {20,40,10,70,99,-2,59,43};
    for(int i = 0; i < testInputSize; i++) {
        cout <<"contains(" <<testInput[i]<<"): "<< (tree->contains
                                      (testInput[i])?"true":"false")<<"\n";
    }
}

void testStringTreeContains(BST<string> * tree)
{
    cout<<"\n\n** TEST CONTAINS **" << endl;
    int testInputSize=8;

    string testInput[] = {"gene","mary","bea","uma","yan","amy","ron","opal"};
    for(int i = 0; i < testInputSize; i++) {
        cout <<"contains(" <<testInput[i]<<"): "<< (tree->contains
                                      (testInput[i])?"true":"false")<<"\n";
    }
}


void testIntegerTreeRemoval(BST<int> * tree)
{
    cout<<"\n** TEST REMOVE **\n";
    int testInputSize=8;
    int testInput[] = {20,40,10,70,99,-2,59,43};
    cout <<"Removing in this order: ";
    for(int i = 0; i < testInputSize; i++) {
        cout <<testInput[i]<<" ";
        tree->remove(testInput[i]);
    }
    displayTreeDetails(tree);
    displayTreeTraversals(tree);
}

void testStringTreeRemoval(BST<string> * tree)
{
    cout<<"\n"<<"** TEST REMOVE **\n";
    int testInputSize=8;
    string testInput[] = {"gene","mary","bea","uma","yan","amy","ron","opal"};
    cout<<"Removing in this order: ";
    for(int i = 0; i < testInputSize; i++) {
        cout <<testInput[i]<<" ";
        tree->remove(testInput[i]);
    }
    displayTreeDetails(tree);
    displayTreeTraversals(tree);
}

void testIntegerTreeInsertion(BST<int> * tree)
{
    cout<<"\n"<<"** TEST INSERT (again) **\n";
    int testInputSize=8;
    int testInput[] = {20,40,10,70,99,-2,59,43};
    cout<<"Inserting in this order: ";
    for(int i = 0; i < testInputSize; i++) {
        cout <<testInput[i]<<" ";
        tree->insert(testInput[i]);
    }
    displayTreeDetails(tree);
    displayTreeTraversals(tree);
}


void testStringTreeInsertion(BST<string> * tree)
{
    cout<<"\n"<<"** TEST INSERT (again) **\n";
    int testInputSize = 8;
    string testInput[] = {"gene","mary","bea","uma","yan","amy","ron","opal"};
    cout<<"Inserting in this order: ";
    for(int i = 0; i < testInputSize; i++) {
        cout <<testInput[i]<<" ";
        tree->insert(testInput[i]);
    }
    displayTreeDetails(tree);
    displayTreeTraversals(tree);
}

void printLevelAndAncestorsOfStringTree(BST<string> *tree) {
    string str = tree->getPreOrderTraversal();
    stringstream temp;
    string word = "";
    cout<<"\n** TEST LEVEL & ANCESTORS **";
    for (auto s : str) {
        if (s == ' ') {
            if (!is_number(word)) {

                cout << "\nlevel(" << word << "): " << getLevelOfStringNode
                                                         (tree, word) << ",\t";
                cout << "ancestors(" << word << "): " << tree->getAncestors
                                                                        (word);
            }
            word = "";
        } else {
            word = word + s;
        }
    }

}

template<typename T>
int getLevelOfNode(BST<T> *tree, int data) {

    return tree->getLevel(data);
}


int getLevelOfStringNode(BST<string> *tree, string data) {
    return tree->getLevel(data);
}

bool is_number(const std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}





