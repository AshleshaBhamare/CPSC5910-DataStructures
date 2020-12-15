// Ashlesha Bhamare
// HuffmanTree.cpp
// 11/14/2020
// Implementation file for the HuffmanTree class
// INPUT: HuffmanTree.h
// having different public functions like createCodeTree, encodeFile,
// decodeFile, displayCode and private functions  traverseAndPrint,
// printHuffmanCode, getHuffmanCode.

#include "HuffmanTree.h"

#define ASCII_OFFSET 128
#define ASCII_MAX 256
#define MAX_SIZE 600

bool HuffmanTree::createCodeTree(string filename) {
    std::priority_queue<
            BST<CharFreq>::BSTNode *,
            std::vector<BST<CharFreq>::BSTNode *>,
            BST<CharFreq>::FrequencyCompare
    > myPriorityQ;
    string str;
    string allText = "";
    ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open()) {
        cout << "ERROR loading file!\n";
        return false;
    }
    while (!infile.eof()) {    // To get you all the lines.
        getline(infile, str); // Saves the line in STRING.
        allText += str + "\n";
    }
    infile.close();
    this->fileText=allText;

    // **************************************************************
    //  1. Count occurrences of every letter or symbol that you care about in
    //     allText (consider spaces ' ', newlines '\n', periods, commas, question
    //     marks, quotation marks, etc.

    int totalLengthOfString = allText.size();

    //hashtable to store character frequency
    int letterFrequencies[MAX_SIZE];
    unsigned char isLetterCounted[ASCII_MAX];


    //Initialising the frequency array
    for (int i = 0; i < ASCII_MAX; i++) {
        letterFrequencies[i] = 0;
        isLetterCounted[i] = 'N';
    }


    //calculate frequency of each character in array
    for (int i = 0; i < totalLengthOfString; i++) {
        //Adding OFFSET to avoid negative index
        letterFrequencies[int(allText[i]) + ASCII_OFFSET]++;

    }

    for (int i = 0; i < totalLengthOfString; i++) {
        unsigned char temp=allText[i];
        if (isLetterCounted[(int)temp] == 'N' ) {
            bool isCharNumber= isdigit(allText[i]);
            CharFreq *charFreq;
            if(isCharNumber)
            {
                int digitCharCode=  int(allText[i]);
              charFreq = new CharFreq(digitCharCode,
                                                  letterFrequencies[
                                                          int(allText[i])+
                                                              ASCII_OFFSET]);

            }
            else {

                    charFreq = new CharFreq(allText[i],
                                            letterFrequencies[
                                                    int(allText[i]) +
                                                    ASCII_OFFSET]);

            }
            BSTNode *node = new BSTNode(CharFreq());
            node->data = *charFreq;
            myPriorityQ.push(node);
            char temp=allText[i];
            isLetterCounted[(int)temp] = 'Y';

        }
    }


    // Iterate while size of heap doesn't become 1
    while (myPriorityQ.size() != 1) {

        // Extract the two minimum
        // freq items from min heap
        BSTNode *left = myPriorityQ.top();
        myPriorityQ.pop();

        BSTNode *right = myPriorityQ.top();
        myPriorityQ.pop();


        BSTNode *top = new BSTNode(CharFreq());

        CharFreq *data = new CharFreq('$', left->data.frequency + right->data
                .frequency);
        top->data = *data;


        top->left = left;
        top->right = right;

        myPriorityQ.push(top);
    }

    this->root = myPriorityQ.top();
    printHuffmanCode(myPriorityQ.top(), "");

    return true;
}

bool HuffmanTree::encodeFile(string originalFilename, string outputFilename) {
    string str;
    string allText = "", currentStream = "";
    ifstream infile;
    const int WRITE_SIZE = 8;


    infile.open(originalFilename.c_str());
    if (!infile.is_open()) {
        cout << "ERROR loading file!\n";
        return false;
    }
    while (!infile.eof()) {        // To get you all the lines.
        getline(infile, str);   // Saves the line in string.
        allText += str + "\n";
    }
    infile.close();

    int totalLengthOfString = allText.size();
    //hashtable to store character frequency
    int letterFrequencies[MAX_SIZE];



    //Initialising the frequency array
    for (int i = 0; i < ASCII_MAX; i++) {
        letterFrequencies[i] = 0;

    }


    //calculate frequncy of each character in array
    for (int i = 0; i < totalLengthOfString; i++) {
        //Adding OFFSET to avoid negative index
        letterFrequencies[int(allText[i]) + ASCII_OFFSET]++;

    }


    std::ofstream outStream(outputFilename.c_str(), std::ios::binary);
    if (!outStream.is_open()) {
        cout << "ERROR creating output file!\n";
        return false;
    }

    for (int i = 0; i < (int) allText.length(); i++) {

        // **************************************************************
        // TODO: encodeFile - add your code here
        //  add the appropriate encoding for allText[i] to currentStream
        // BSTNode node= BST()
        string str = getHuffmanCode(root, allText[i],
                                    letterFrequencies[int(allText[i]) +
                                                      ASCII_OFFSET]);
        currentStream = str; // may need to update this line


        // **************************************************************

        while ((int) currentStream.length() > WRITE_SIZE) {
            string byte = currentStream.substr(0, WRITE_SIZE);
            bitset<8> set(byte);
            const char toWrite = (unsigned char) ((unsigned int) set.to_ulong());
            outStream.write(&toWrite, sizeof(char));
            currentStream = currentStream.substr(WRITE_SIZE,
                                                 currentStream.length() -
                                                 WRITE_SIZE);
        }
        outStream<<currentStream;
    }


    outStream.close();
    return false;
}

bool HuffmanTree::decodeFile(string filename) {
    string bitStream = "";
    ifstream encodedfile;

    encodedfile.open(filename.c_str(), ios::binary);
    if (!encodedfile.is_open()) {
        cout << "ERROR opening encoded file!\n";
        return false;
    }

    encodedfile >> std::noskipws;
    string data="";
    getline(encodedfile,data);
    while (!encodedfile.eof()) {
        unsigned char readMe;
        encodedfile >> readMe;
        bitset<8> set((unsigned long) readMe);
        bitStream += set.to_string();
    }

    traverseAndPrint(data, 0);


    encodedfile.close();
    //cout<<bitStream;
    //while (i != -1)
     //   i = traverseAndPrint(bitStream, i);
    return false;
}

int HuffmanTree::traverseAndPrint(string &bits, int i, BSTNode *cur) {
    if (i >= (int) bits.length())
        return -1;
    // **************************************************************
    // TODO: traverseAndPrint - add your code here
    //  Write this function using recursion. This is essentially your decode
    //  function.  You need to step through the tree based on reading 0 or 1
    //  and when you reach a leaf, print (using cout) the appropriate character.
    //  - i represents your current location in the string
    //  - cur represents the cur node in your tree
    //  Don't forget that you need to keep going after printing out a character
    //  (which means restarting at the top of the tree)

    // **************************************************************
    string ans = "";

        if (bits[i] == '0')
            cur = cur->left;
        else
            cur = cur->right;

        // reached leaf node
        if (cur->left==NULL and cur->right==NULL)
        {
            cout<<cur->data.letter;
            cur = root;

        }

    return traverseAndPrint(bits,i+1,cur);
}

void HuffmanTree::displayCode(ostream &out) {
    // **************************************************************
    // TODO: displayCode - add your code here
    //  Print out each letter and its code, you might want to check for
    //  special cases (space, newline, etc.)
   string allText=this->fileText;

    int totalLengthOfString = allText.size();
    //hashtable to store character frequency
    int letterFrequencies[MAX_SIZE];
    char isLetterCounted[ASCII_MAX];


    //Initialising the frequency array
    for (int i = 0; i < ASCII_MAX; i++) {
        letterFrequencies[i] = 0;
        isLetterCounted[i] = 'N';
    }


    //calculate frequncy of each character in array
    for (int i = 0; i < totalLengthOfString; i++) {
        //Adding OFFSET to avoid negative index
        letterFrequencies[int(allText[i]) + ASCII_OFFSET]++;

    }

    cout<<" Displaying count of occurrence for all letters"<<endl;
    //calculate frequncy of each character in array
    for (int i = 0; i < totalLengthOfString; i++) {
        //Adding OFFSET to avoid negative index
        if( isLetterCounted[i]=='N') {
            cout << allText[i] << " : " << letterFrequencies[int(allText[i]) +
                                                             ASCII_OFFSET]
                 << endl;

        }

    }



    // **************************************************************
}

ostream &operator<<(ostream &out, HuffmanTree &code) {
    code.displayCode(out);
    return out;
}

void HuffmanTree::printHuffmanCode(BSTNode *root, string str) {

    if (!root)
        return;

    if (root->data.letter != '$') {
       // cout << root->data.letter << ": " << str << "\n";
        root->data.encoding = str;
    }
    BSTNode *leftNode = root->left;
    printHuffmanCode(leftNode, str + "0");
    printHuffmanCode(root->right, str + "1");
}

string HuffmanTree::getHuffmanCode(BSTNode *node, char c, int frequency) {
    string code="";
    // Base Case
    if (root == NULL)
        return code;

    // Create an empty queue for
    // level order traversal
    queue<BSTNode *> q;

    // Enqueue Root and initialize height
    q.push(root);

    // Queue based level order traversal
    while (q.empty() == false)
    {
        // See if current node is same as x
      BSTNode *node = q.front();
        if (node->data.letter == c)
            return node->data.encoding;

        // Remove current node and enqueue its children
        q.pop();
        if (node->left != NULL)
            q.push(node->left);
        if (node->right != NULL)
            q.push(node->right);
    }

    return code;

}