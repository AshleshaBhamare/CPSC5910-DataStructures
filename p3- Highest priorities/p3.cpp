// AUTHOR:  Ashlesha Bhamare
// PROGRAM: p3.cpp
// DATE:    11/04/2020
// PURPOSE: This program creates Triage system for a hospital emergency room.
//          There are four levels of priority for the patients like immediate,
//          emergency, urgent and minimal. The triage nurse will determine
//          the patient's priority based on their injury or illness and enter
//          the patient's full name along with the urgency level based on the
//          table above to indicate the
//          priority.
// INPUT:   Commands.txt, Patients.h and PatientPriorityQueue.h
// PROCESS: Run the different commands like help, add, list, peek, next, list
//          and quit based on user input.
// OUTPUT:  Prints the output of different commands with the list of patients.

#include "PatientPriorityQueue.h"
#include "Patient.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void welcome();
// Prints welcome message.

void goodbye();
// Prints goodbye message.

void help();
// Prints help menu.

bool processLine(string, PatientPriorityQueue &);
// Process the line entered from the user or read from the file.
// IN: string, PatientPriorityQueue &
// MODIFY: none
// OUT: returns the result

void addPatientCmd(string, PatientPriorityQueue &);
// Adds the patient to the waiting room.
// IN: string, PatientPriorityQueue &
// MODIFY: none
// OUT: none

void peekNextCmd(PatientPriorityQueue &);
// Displays the next patient in the waiting room that will be called.
// IN: PatientPriorityQueue &
// MODIFY: none
// OUT: none

void removePatientCmd(PatientPriorityQueue &);
// Removes a patient from the waiting room and displays the name on the screen.
// IN: PatientPriorityQueue &
// MODIFY: none
// OUT: none


void showPatientListCmd(PatientPriorityQueue &);
// Displays the list of patients in the waiting room.
// IN: PatientPriorityQueue &
// MODIFY: none
// OUT: none


void execCommandsFromFileCmd(string, PatientPriorityQueue &);
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.
// IN: string, PatientPriorityQueue &
// MODIFY: none
// OUT: none


string delimitBySpace(string &);
// Delimits (by space) the string from user or file input.
// IN: string &
// MODIFY: none
// OUT: returns updated string for priorityCode

string delimitForName(string &s);
// Delimits (by space) the string from user or file input.
// IN: string &
// MODIFY: none
// OUT: returns updated string for name

int validatePriority(string priority);
// Validates the Priority.
// IN: string priority
// MODIFY: none
// OUT: Returns the level for priority code

const string WHITESPACE = " \n\r\t\f\v";
// Constant for ltrim and rtrim function

string ltrim(const string& s);
// To trim left.
// IN: const string& s
// MODIFY: none
// OUT: Returns the string for left

string rtrim(const string& s);
// To trim right.
// IN: const string& s
// MODIFY: none
// OUT: Returns the string for right

string trim(const string& s);
// To trim .
// IN: const string& s
// MODIFY: none
// OUT: Returns the updated output for ltrim and rtrim


static int arrivalOrder=0;

int main() {

    // declare variables
    string line;
    arrivalOrder=0;

    // welcome message
    welcome();

    // process commands
    PatientPriorityQueue priQueue(30);
    do {
        cout << "\ntriage> ";
        getline(cin, line);
    } while (processLine(line, priQueue));

    // goodbye message
    goodbye();
}

bool processLine(string line, PatientPriorityQueue &priQueue) {
    // get command
    string cmd = delimitBySpace(line);
    if (cmd.length() == 0) {
        cout << "Error: no command given.";
        return false;
    }

    // process user input
    if (cmd == "help")
        help();
    else if (cmd == "add")
        addPatientCmd(line, priQueue);
    else if (cmd == "peek")
        peekNextCmd(priQueue);
    else if (cmd == "next")
        removePatientCmd(priQueue);
    else if (cmd == "list")
        showPatientListCmd(priQueue);
    else if (cmd == "load")
        execCommandsFromFileCmd(line, priQueue);
    else if (cmd == "quit")
        return false;
    else
        cout << "Error: unrecognized command: " << cmd << endl;

    return true;
}

void addPatientCmd(string line, PatientPriorityQueue &priQueue) {
    string priority, name;
    string updatedInput;

    updatedInput = trim(line);

    // get priority and name
    priority = delimitBySpace(updatedInput);
    if (priority.length() == 0) {
        cout << "Error: no priority code given.\n";
        return;
    }
    name = delimitForName(line);

    if (name.length() == 0) {
        cout << "Error: no patient name given.\n";
        return;
    }

    Patient newPatient (name,priority,++arrivalOrder);


    int validatedPriority = validatePriority(priority);

    if(validatedPriority!=-1)
    {
        priQueue.add(newPatient);
        cout << "Added patient " << "'" << name << "'"<< " to the "
                                                         "priority system\n";
    }
    else
        cout<<"Invalid priority entered. Please try again!\n";
}

void peekNextCmd(PatientPriorityQueue &priQueue) {

    string patientName = (priQueue.peek()
            .to_string());
    size_t pos = 0;
    int counter=0;
    string delimiter="\t";
    string token;
    while ((pos = patientName.find(delimiter)) != string::npos) {
        token = patientName.substr(0, pos);
        patientName.erase(0, pos + delimiter.length());
        counter++;
    }

    cout <<"Highest priority patient to be called next: "<< patientName <<
    endl;
}

void removePatientCmd(PatientPriorityQueue &priQueue) {

    if(priQueue.size()==0)
    {
        cout<<"There are no new patients in the waiting area." << endl;

    }
    else {
        string patientName=(priQueue.peek()
                .to_string());


        size_t pos = 0;
        int counter=0;
        string delimiter="\t";
        string token;
        while ((pos = patientName.find(delimiter)) != string::npos) {
            token = patientName.substr(0, pos);
            patientName.erase(0, pos + delimiter.length());
            counter++;
        }
        cout << "This patient will now be seen: " <<  patientName << endl;
        priQueue.remove();
    }
}

void showPatientListCmd(PatientPriorityQueue &priQueue) {
    cout << "# patients waiting: " << priQueue.size() << endl;
    cout << endl;
    cout << "  Arrival #   Priority Code   Patient Name\n"
         << "+-----------+---------------+--------------+\n";

    cout<< priQueue.to_string();
}

void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue) {
    ifstream infile;
    string line;

    // open and read from file
    infile.open(filename);
    // infile.open(filename);
    if (infile) {
        while (getline(infile, line)) {
            cout << "\ntriage> " << line << endl;
            // process file input
            processLine(line, priQueue);
        }
    } else {
        cout << "Error: could not open file.\n";
    }
    // close file
    infile.close();
}

string delimitBySpace(string &s) {
    unsigned pos = 0;
    char delimiter = ' ';
    string result = "";

    pos = s.find(delimiter);
    if (pos != string::npos) {
        result = s.substr(0, pos);
        s.erase(0, pos + 1);
    }
    return result;
}

string delimitForName(string &s) {
    unsigned pos = 0;
    char delimiter = ' ';
    string result = "";

    pos = s.find(delimiter);

    return  s.substr(pos+1);
}

int validatePriority(string priority)
{
    if (priority == "immediate") return 1;
    if (priority== "emergency") return 2;
    if (priority == "urgent") return 3;
    if (priority == "minimal") return 4;
    return -1;
}

void welcome() {
    cout << "\nWelcome to the Hospital emergency room triage system!\n"
    << "There are 4 levels of priority for patients immediate, emergency, "
       "urgent and minimal.\n" << "The triage nurse will determine the patient's"
       <<" priority based on their injury or illness\n";
}

void goodbye() {
    cout << "\nThank you for using Hospital emergency room triage system!\n"
         << endl;
}

void help() {
    cout << "add <priority-code> <patient-name>\n"
         << "            Adds the patient to the triage system.\n"
         << "            <priority-code> must be one of the 4 accepted "
                                                           "priority codes:\n"
         << "                1. immediate 2. emergency 3. urgent 4. minimal\n"
         << "            <patient-name>: patient's full legal name (may "
                                                            "contain spaces)\n"
         << "next        Announces the patient to be seen next. Takes into"
                                                               " account the\n"
         << "            type of emergency and the patient's arrival order.\n"
         << "peek        Displays the patient that is next in line, but"
                                                             " keeps in queue\n"
         << "list        Displays the list of all patients that are"
                                                              " still waiting\n"
         << "            in the order that they have arrived.\n"
         << "load <file> Reads the file and executes the command on each line\n"
         << "help        Displays this menu\n"
         << "quit        Exits the program\n";
}


string ltrim(const string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}

string rtrim(const string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string trim(const string& s)
{
    return rtrim(ltrim(s));
}