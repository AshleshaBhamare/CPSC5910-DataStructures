// AUTHOR:  Ashlesha Bhamare
// PROGRAM: p4.cpp
// DATE:    11/21/2020
// PURPOSE: This program program that uses a Hash Table to efficiently solve
//          the following problem: Given a natural language text, generate a
//          table of distinct words with the number of occurrences of each word
//          in the text.
// INPUT:   WordCounter.h, CommonWordList.h
// PROCESS: Ask user for filename and capacity,run the different functions like
//          cleanWord, removeCommonWords. Also ask client for the word(s) that
//          they want to analyze
// OUTPUT:  Prints the hash table statistics and word analysis statistics.

#include "WordCounter.h"
#include "CommonWordList.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include<math.h>
#include <iomanip>
using namespace std;

void welcomeMessage();
// Prints welcome message.

string cleanWord(string);
// Takes in a word and converts it to lower case. Removes any special
// characters that are not hyphen or apostrophe
// IN: string
// MODIFY: none
// OUT: returns the result

void removeCommonWords(WordCounter &);
// Iterates through all the known common words and removes them from the given
// hash table.
// IN: WordCounter &
// MODIFY: none
// OUT: none

double getLoadFactor(WordCounter &,int capacity);
// Get the number of unique words encountered
// IN: WordCounter & and int capacity
// MODIFY: none
// OUT: returns the load factor

void displayWordCount(WordCounter &,int capacity);
// To display word count
// IN: WordCounter & and int capacity
// MODIFY: none
// OUT: none

static int readFile(WordCounter & , string filePath, vector<string>);
// To process and read file
// IN: WordCounter &, string filePath, vector<string>
// MODIFY: none
// OUT: returns the result

void analyzeWord(WordCounter &wc, const string &word);
// to print the analysis of a single word in a wordCounter
// IN: WordCounter &, const string &word
// MODIFY: none
// OUT: none

void goodByeMessage();
// Prints goodbye message.

const char APOSTROPHE_CHAR = '\''; 	// apostrophe character used in cleanWord
const char HYPHEN_CHAR = '-'; 		// hyphen/dash character used in cleanWord

int main() {
    string filePath;                            // To hold filepath
    int capacity=0;                             // To hold capacity
    int choice = 1;                             // To hold choice

    welcomeMessage();
    // populate common words
    CommonWordList::populateWords();
    vector<string> commonWords =CommonWordList::getWords();

    WordCounter wc;
    //cout << "Is hashtable is empty: " << wc.empty() << endl;
    //cout << "Hashtable capacity: " << wc.getCapacity() << endl;


    while (choice != 0) {

        cout << "\nWhat is the filename: ";
        cin >> filePath;
        cout << "What is the capacity: ";
        cin >> capacity;

        WordCounter wc(capacity);

        int isValidFile = readFile(wc, filePath, commonWords);
        if (isValidFile != -1) {
            displayWordCount(wc, capacity);

            string fileName;

            cin.ignore();
            cout << "\nEnter words (separated by space): ";

            string word, in;

            getline(cin, in);

            istringstream iss(in);
            cout << "\nAnalysis of words: " << endl;
            cout << "Given Word" << "\t\t" << " Count" << endl;
            cout << "+----------+-------------+-------------+" << endl;
            while (iss >> word) {
                analyzeWord(wc, word);
            }
            cout << "\nRemove the following words: " << in;
            cout << endl;
            displayWordCount(wc, capacity);

            cout << "\nEnter 1 to read another file or 0 to quit: " ;
            cin >> choice;
        }
}
    goodByeMessage();
    return 0;
}

void displayWordCount(WordCounter & wc,int capacity)
{
    cout << "\nWord counter statistics:" << endl;
    cout << "#unique " << "\t" << "#Total" << "\t\t" << "Load Factor" <<endl;
    cout<<"+----------+-------------+-------------+"<<endl;
    cout << wc.getUniqueWordCount() << "\t\t"<<wc.getTotalWordCount()<<"\t\t"
    << setprecision(3) << fixed<<getLoadFactor(wc,capacity);
    cout << endl;

}
int readFile(WordCounter &wordCounter,string filePath,vector<string>
        commonWords)
{
    string word,subString;
    ifstream inFile;

    //reading file
    inFile.open(filePath);
    if(inFile.is_open())
    {
        //Reading each word in file
        while(inFile>>word)
        {
            if(word[word.length()-1]=='-')
            {
                inFile>>subString;
                word=word.substr(0,word.length()-1);
                word.append(subString);
            }
            word=cleanWord(word);
            wordCounter.addWord(word);
        }
        //removing common words
        for (string common: commonWords)
            removeCommonWords(wordCounter);

        return 1;
    }
    else{
        //Invalid path/file
        cout<<"\nError: Can not open given file!"<<endl;
        return -1;
    }
}

double getLoadFactor(WordCounter &wordCounter,int capacity)  {
    return (round(wordCounter.getUniqueWordCount() * 1000) / 1000.0)
                                                              / capacity;
}

string cleanWord(string s) {
    string result = "";                  // Keep track of the cleaned result.
    unsigned i = 0, length = s.length(); // Input for the for loop.
    for (; i < length; i++) {
        if (isalnum(s[i]))
            result += tolower(s[i]);
        else if (s[i] == APOSTROPHE_CHAR) {
            if (i > 0 && isalnum(s[i-1]))
                result += s[i];
        } else if (s[i] == HYPHEN_CHAR) {
            if (i > 0 && i < (length-1) && isalnum(s[i-1])
                                                && isalnum(s[i+1]))
                result += s[i];
                // If a word ends in a hyphen, we assume it is residue that
                // needs to
                // be paired with the next word. Return the word with the
                // hyphen as a
                // signal to the caller to retain it as residue.
            else if (i > 0 && i == (length-1) && isalnum(s[i-1]))
                result += s[i];
        }
    }
    return result;
}

void removeCommonWords(WordCounter &wc) {
    for (string &s : CommonWordList::getWords())
        wc.removeWord(s);
}

void analyzeWord(WordCounter &wc, const string &word) {
    cout << word << "\t\t: " << wc.getWordCount(word)<<endl ;
    wc.removeWord(word);
}
void welcomeMessage()
{
    cout << "\nWelcome to the Hashing the Hobbit program\n";
}
void goodByeMessage()
{
    cout << "\nGood-Bye!!\n";
}