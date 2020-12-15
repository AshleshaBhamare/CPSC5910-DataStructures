// Ashlesha Bhamare
// Patient.h
// 11/04/2020
// Specification and Implementation file for the Patient class having different
// functions like getPriority, to_string and overloaded operators

#ifndef P3_UPDATED_PATIENT_H
#define P3_UPDATED_PATIENT_H

#include <iostream>
#include <sstream>

using namespace std;

class Patient {
public:
    Patient(string, string, int);                        // Constructor

    Patient & operator = (const Patient &t);
    // Its is used to assign patient to a particular index or priority in
    // priority queue
    // precondition: None
    // postcondition: assigned patient to correct index in Priority queue

    bool operator < (const Patient &t);
    // To compare priorityCode of patient and arrival order of patient
    // precondition: None
    // postcondition: Returns true if current patient priority is less than
    // operands priority

    bool operator == (const Patient &t);
    // To compare priorityCode of patient and arrival order of patient
    // precondition: None
    // postcondition: Returns true if current patient priority is less than
    // operands priority

    string to_string();
    // To return concatenated string of priorityCode, name and arrivalOrder
    // precondition: None
    // postcondition: returns the patient details in string format

    Patient & updatePriority (const Patient &t);
    // Its is used to update priority
    // precondition: None
    // postcondition: assigned updated priority to the patient

private:
    string name;                                     // To hold name
    string priorityCode;                             // To hold priorityCode
    int arrivalOrder=0;                              // To hold arrivalOrder


};

Patient::Patient(string patientName, string patientPriorityCode, int
patientArrivalOrder)
{
    name = patientName;
    priorityCode = patientPriorityCode;
    arrivalOrder =  patientArrivalOrder;

}

Patient & Patient::operator = (const Patient &t)
{
    // Check for self assignment
    if(this != &t) {
        this->name = t.name;
        this->arrivalOrder=t.arrivalOrder;
        this->priorityCode=t.priorityCode;
    }

    return *this;
}

int getPriority(string priority)
{
    if (priority == "immediate") return 1;
    if (priority== "emergency") return 2;
    if (priority == "urgent") return 3;
    if (priority == "minimal") return 4;

    return -1;
}

bool Patient::operator < (const Patient &t)
{
    int p1=getPriority(this->priorityCode);
    int p2=getPriority(t.priorityCode);

    if(p1==p2)
    {
         return (this->arrivalOrder>t.arrivalOrder);
    }
   else if(p1>p2)
        return true;
    else
        return false;

}
bool Patient::operator == (const Patient &t)
{
    return (this->arrivalOrder==t.arrivalOrder);
}

string Patient::to_string()
{
    stringstream ss;
    ss << "\t" << arrivalOrder << " \t\t" << priorityCode << "\t\t" <<
       name;
    return ss.str();

}
Patient &Patient::updatePriority (const Patient &t)
{
    // Check for self assignment
    if(this != &t) {
        this->name = t.name;
        this->arrivalOrder=t.arrivalOrder;

    }

    return *this;
}

#endif //P3_UPDATED_PATIENT_H
