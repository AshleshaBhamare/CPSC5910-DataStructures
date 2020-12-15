// AUTHOR:  Ashlesha Bhamare
// PROGRAM: p3x.cpp
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

#include "PatientPriorityQueuex.h"
#include "Patient.h"
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

bool processLine(string, PatientPriorityQueuex &);
// Process the line entered from the user or read from the file.
// IN: string, PatientPriorityQueue &
// MODIFY: none
// OUT: returns the result

void addPatientCmd(string, PatientPriorityQueuex &);
// Adds the patient to the waiting room.
// IN: string, PatientPriorityQueue &
// MODIFY: none
// OUT: none

void updatePatientCmd(string, PatientPriorityQueuex &);
// updates the patient in the waiting room.
// IN: string, PatientPriorityQueue &
// MODIFY: none
// OUT: none

void peekNextCmd(PatientPriorityQueuex &);
// Displays the next patient in the waiting room that will be called.
// IN: PatientPriorityQueue &
// MODIFY: none
// OUT: none

void removePatientCmd(PatientPriorityQueuex &);
// Removes a patient from the waiting room and displays the name on the screen.
// IN: PatientPriorityQueue &
// MODIFY: none
// OUT: none


void showPatientListCmd(PatientPriorityQueuex &);
// Displays the list of patients in the waiting room.
// IN: PatientPriorityQueue &
// MODIFY: none
// OUT: none

void execCommandsFromFileCmd(string, PatientPriorityQueuex &);
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.
// IN: string, PatientPriorityQueue &
// MODIFY: none
// OUT: none

void execSaveCmd(string, PatientPriorityQueuex &);


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

string delimitForCommand(string &s);
// Delimits (by space) the string from user or file input.
// IN: string &
// MODIFY: none
// OUT: returns updated command

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
    PatientPriorityQueuex priQueue(30);
    do {
        cout << "\ntriage> ";
        getline(cin, line);
    } while (processLine(line, priQueue));

    // goodbye message
    goodbye();
}

bool processLine(string line, PatientPriorityQueuex &priQueue) {
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
    else if (cmd == "change")
        updatePatientCmd(line, priQueue);
    else if (cmd == "peek")
        peekNextCmd(priQueue);
    else if (cmd == "next")
        removePatientCmd(priQueue);
    else if (cmd == "list")
        showPatientListCmd(priQueue);
    else if (cmd == "load")
        execCommandsFromFileCmd(line, priQueue);
    else if (cmd == "save")
       execSaveCmd(line, priQueue);
    else if (cmd == "quit")
        return false;
    else
        cout << "Error: unrecognized command: " << cmd << endl;

    return true;
}


bool processLineForInputFile(string line, PatientPriorityQueuex &priQueue) {
    // get command
    string patientName = line;
    string cmd = line;
    size_t pos = 0;
    int counter=0;
    string delimiter="\t";
    string token;
    while ((pos = patientName.find(delimiter)) != string::npos) {
        token = patientName.substr(0, pos);
        patientName.erase(0, pos + delimiter.length());
        counter++;
    }
/*

    cout <<"Highest priority patient to be called next: "<<patientName<<
         endl;
*/


    string priority = delimitForCommand(line);

    cmd="add";

    line=priority+ " "+patientName;

    // process user input
    if (cmd == "help")
        help();
    else if (cmd == "add")
        addPatientCmd(line, priQueue);
    else if (cmd == "change")
        updatePatientCmd(line, priQueue);
    else if (cmd == "peek")
        peekNextCmd(priQueue);
    else if (cmd == "next")
        removePatientCmd(priQueue);
    else if (cmd == "list")
        showPatientListCmd(priQueue);
    else if (cmd == "load")
        execCommandsFromFileCmd(line, priQueue);
    else if (cmd == "save")
        execSaveCmd(line, priQueue);
    else if (cmd == "quit")
        return false;
    else
        cout << "Error: unrecognized command: " << cmd << endl;

    return true;
}

void addPatientCmd(string line, PatientPriorityQueuex &priQueue) {
    string priority, name;
    string updatedInput;

    // TODO: add logic to remove leading/trailing spaces

    updatedInput = trim(line);

    // get priority and name
    priority = delimitBySpace(updatedInput);
    if(priority=="" || priority==" ")
    {
        cout<<"";
    }
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

void updatePatientCmd(string line, PatientPriorityQueuex &priQueue) {
    string input,priority, name;
    string updatedInput;
    int exitingArrivalID=0;

    // TODO: add logic to remove leading/trailing spaces

    updatedInput = trim(line);


    // get priority and name
    input= delimitBySpace(updatedInput);
    if( input=="" || input=="change")
    {
        cout<<"Error: No patient id provided" << endl;
    }
   else {

        exitingArrivalID = stoi(input);
        if(exitingArrivalID>priQueue.size())
        {
            cout<<"Error: no patient with the given id was found";
            return;
        }
        if (input=="change" && exitingArrivalID == 0) {
            cout << "Error: no patient with the given id was found." << endl;
            return;
        }
        priority = delimitForName(line);

        if ( priority.length() == 0 ) {
            cout << "Error: invalid priority level code";
            return;
        }

        int validatedPriority = validatePriority(priority);


        if (validatedPriority != -1) {
            Patient newPatient(name, priority,  exitingArrivalID );
            priQueue.update(newPatient);
            cout << "Changed patient priority to " <<
            priority << endl;
        } else
            cout << "Error: invalid priority level code.\n";
    }
}


void peekNextCmd(PatientPriorityQueuex &priQueue) {

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

void removePatientCmd(PatientPriorityQueuex &priQueue) {

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

void showPatientListCmd(PatientPriorityQueuex &priQueue) {
    cout << "# patients waiting: " << priQueue.size() << endl;
    cout << endl;
    cout << "  Arrival #   Priority Code   Patient Name\n"
         << "+-----------+---------------+--------------+\n";
    // TODO: shows patient detail in heap order
    cout<< priQueue.to_string();

}

void execCommandsFromFileCmd(string filename, PatientPriorityQueuex &priQueue) {
    ifstream infile;
    string line;

    // open and read from file
    infile.open(filename);

    if (infile) {
        while (getline(infile, line)) {

            cout << "\ntriage> add " << line.substr(3) << endl;

            // process file input
            processLineForInputFile(line, priQueue);
        }
    } else {
        cout << "Error: could not open file.\n";
    }
    // close file
    infile.close();
}


void execSaveCmd(string filename, PatientPriorityQueuex &priQueue) {


    string input,priority, name;
    string updatedInput;


    // TODO: add logic to remove leading/trailing spaces

    updatedInput = trim(filename);


   if(updatedInput.length()!=0) {
       priQueue.save(updatedInput);
       cout << "Saved "<< priQueue.size() <<" patients to file "
                                << updatedInput << endl;
   }
   else{
       cout<< "Filename not provided";
   }
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
    /*   if (pos != string::npos) {
           result = s.substr(0, pos);
           s.erase(0, pos + 1);
       }*/
    return  s.substr(pos+1);
}

string delimitForCommand(string &line) {
   unsigned pos=0;
    string delimiter="\t";
    string priorityName="";
    string token;
    int priority=-1;
    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);
        priority=validatePriority(token);
        if(priority!=-1)
        {
            priorityName=token;
            break;
        }
        line.erase(0, pos + delimiter.length());

    }

    return priorityName;
   // return  s.substr(pos+1);
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