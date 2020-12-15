// AUTHOR: Ashlesha Bhamare
// FILENAME: lab1.cpp
// DATE: 09/19/2020
// PURPOSE: This program creates dynamic 1D array of strings called "members"
//           and dynamic 2D array of integers called "ratings", populate the
//            arrays and prints the content of both arrays.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    const int SIZE = 100;
    string *members;
    int **ratings;
    string fileName;
    ifstream inFile;
    string line;
    string temp;
    int validInteger;
    int memberCount = 0;
    int booksCount = 0;
    int lineCount=0;
    int rowCount = 0;
    int columnCount=0;
    int row=0;
    int memberRowCount=0;
    stringstream integersSeparatedBySpace;

    //Initialing the members and ratings array
    members=new string[SIZE];
    ratings=new int*[SIZE];
    for(int i = 0; i < SIZE; ++i)
        ratings[i] = new int[SIZE];

    cout << "Enter the Filename: ";
    cin >> fileName;

    //To open and to read file
    inFile.open(fileName);

    if(inFile.is_open()){
        while(!inFile.eof()){
            getline(inFile,line);

            if (lineCount % 2 == 0 && !line.empty())
                memberCount++;
                //counting number of books from first ratings row
            else if(memberCount==1)
            {
                integersSeparatedBySpace << line;
                while (!integersSeparatedBySpace.eof()) {
                    integersSeparatedBySpace >> temp;
                    if (stringstream(temp) >> validInteger)
                        booksCount++;
                    temp = "";

                }
            }
            lineCount++;
        }

        inFile.close();
    }

    cout << "\n# books: "<< booksCount;
    cout << "\n# members: "<< memberCount;
    cout << endl;


    //reopening file to read entries
    inFile.open(fileName);
    rowCount=0;
    if(inFile.is_open()){
        while(!inFile.eof() ){
            columnCount=0;

            getline(inFile,line);

            if (rowCount % 2 == 0 && !line.empty()) {
                members[memberRowCount] = line;
                memberRowCount++;
            }
            else
            {

                std::stringstream  lineStream(line);

                int value=0;
                // Read an integer at a time from the line
                while(lineStream >> value)
                {
                    ratings[row][columnCount]=value;

                    columnCount++;
                }
                row++;
            }

            rowCount++;
        }

        //Printing the members and ratings

        int col=0;
        row=0;
        while(row<memberCount&& !members[row].empty())
        {
            cout << "\n" <<members[row] << "\n";
            while(col<booksCount)
            {
                cout << ratings[row][col] << " ";
                col++;
            }
            row++;
            col=0;
        }

        //Closing file
        inFile.close();

        //deallocating members and ratings array
        delete [] members;
        delete [] ratings;


    }
    return 0;
}

