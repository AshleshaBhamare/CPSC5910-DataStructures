// AUTHOR:  Ashlesha Bhamare
// PROGRAM: lab3.cpp
// DATE:    10/06/2020
// PURPOSE: This program informs the user if the user input was a palindrome
// INPUT:   inputFile
// PROCESS: Open and read the file and checks if the string is palindrome or not
// OUTPUT:  Prints the output of Palindrome or NOT palindrome

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

void welcomeMessage();
// To print welcome message
bool isPalindrome(string text);
// To check that the input is palindrome or not
// IN: string text
// MODIFY: none
// OUT: return recIsStringPalindrome(text,0,text.length()-1);

bool recIsStringPalindrome(string str, int first, int last);
// This method use recursion to perform the palindrome test
// IN: string str, int first, int last
// MODIFY: none
// OUT: return recIsStringPalindrome(str, first+1, last-1)

string removeSpaces(string str);
// This method use to remove spaces
// IN: string str
// MODIFY: none
// OUT: str

string convertToLower(string upper);
// This method use to convert uppercase to lowercase
// IN: string upper
// MODIFY: none
// OUT: return upper1

string convertString(string original);
// function that calls all previous functions (does the following in
// order for each string)
// IN: string original
// MODIFY: none
// OUT: lower

void goodByeMessage();
// To print GoodBye message


int main()
{

    string text;                                  // To hold text
    string fileName;                              // To hold fileName
    string line;                                  // To hold line

    welcomeMessage();

    cout << "Enter books file: ";
    cin >> fileName;
    cout << endl;

    ifstream myFile(fileName);

    if (myFile.is_open()) {
       while(getline(myFile, line))  //read data from file object and put
                                            // it into string.
       {
           string convert = convertString(line);
           bool palindrome = isPalindrome(convert);

           if (palindrome == true)      //if it is a palindrome, it prints out
                                                      // "PALINDROME"
           {
               cout << line <<" is palindrome!" << endl;
           }
           else if (palindrome == false) //if it is not a palindrome, it prints
                                           // out "NOT A PALINDROME"
           {
               cout << line << " is NOT a palindrome." << endl;
           }
        }

        myFile.close();
    }
    goodByeMessage();
}

bool isPalindrome(string text)
{

    return recIsStringPalindrome(text,0,text.length()-1);

}
bool recIsStringPalindrome(string str, int first, int last)
{
    if(str.length() == 1)
    {
        return true;
    }
    if(first >= last)
    {
        return true;
    }
    if(str[first] != str[last])
    {
        return false;
    }
    return recIsStringPalindrome(str, first+1, last-1);

}

string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

string convertToLower(string upper)

{
    string upper1 = upper;
    transform(upper1.begin(), upper1.end(), upper1.begin(),
                                                   (int(*)(int))tolower);
    return upper1;
}


string convertString(string original)
{
    string noSpace = removeSpaces(original);
    string lower = convertToLower(noSpace);
    return lower;
}

void welcomeMessage()
{
    cout << "\nWelcome to the palindrome testing program!\n" << endl;
}
void goodByeMessage()
{
    cout << "\nThanks for using the palindrome tester!\n" << endl;
}



