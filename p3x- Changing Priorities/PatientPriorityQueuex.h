// Ashlesha Bhamare
// PatientPriorityQueuex.h
// 11/04/2020
// Specification and Implementation file for the PatientPriorityQueue class
// having different public functions like add, peek, remove, size and to_string
// and private function heapify

#ifndef P3X_PATIENTPRIORITYQUEUEX_H
#define P3X_PATIENTPRIORITYQUEUEX_H


#include <iostream>
#include <vector>
#include "Patient.h"
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>


using namespace std;

class PatientPriorityQueuex {
public :

    PatientPriorityQueuex(int n);                          // Constructor
    ~PatientPriorityQueuex();                               // Destructor


    void add(Patient);
    // Adds the patient to the priority queue
    // precondition: Input argument with valid name and priority required
    // postcondition: Add patients details to Priority queue

    void update(Patient);
    // to update patients priority
    // precondition: patient name should be available with priority
    // postcondition: Returns the updated priority for patient

    Patient peek() const;
    // Returns the highest priority patient without removing it.
    // precondition:
    // postcondition: Returns the highest priority patient

    void remove();
    // Removes the highest priority patient from the queue and returns it
    // precondition: Assumes that the queue is not empty
    // postcondition: Removes the highest priority patient from the queue

    int size();
    // Returns the number of patients still waiting.
    // precondition: There should be patients in waiting room
    // postcondition: Returns the number of patients in the waiting room

    string to_string();
    // Returns the string representation of the object in heap (or level) order.
    // precondition: None
    // postcondition: Returns string representation

    void save(string fileName);
    // To save patients with details to the file .
    // precondition: file should be available
    // postcondition: Patients details saved to the file


private:
    vector<Patient> patients;                             // Vector
    int heapSize;                                         // To hold heapSize
    int capacity;                                        // To hold capacity

    void heapify( int i);
    // Function to heapify the tree
    // precondition: Priority queue should be not empty
    // postcondition: Balances queue in heap order

};

PatientPriorityQueuex::PatientPriorityQueuex(int n) {
                capacity=n;
}

PatientPriorityQueuex::~PatientPriorityQueuex() {
    patients.clear();
}

void PatientPriorityQueuex::add(Patient newPatient) {

    patients.push_back(newPatient);
    heapSize=patients.size();
    if(heapSize>1){
        for (int i = (heapSize-1) / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
    }

}

void PatientPriorityQueuex::update(Patient newPatient) {

    for (unsigned int i = 0; i < patients.size(); i++) {
        if (patients[i] == newPatient) {
            newPatient = newPatient.updatePriority(patients[i]);
            patients[i] = newPatient;
            string patientName = newPatient.to_string();
            size_t pos = 0;
            int counter = 0;
            string delimiter = "\t";
            string token;
            while ((pos = patientName.find(delimiter)) != string::npos) {
                token = patientName.substr(0, pos);
                patientName.erase(0, pos + delimiter.length());
                counter++;
            }

        }

    }
}

Patient PatientPriorityQueuex::peek() const {
    //assert(!empty());
    return patients[0];
}


void PatientPriorityQueuex::remove() {

    int size = patients.size();


    Patient temp("","",-1);

    if(size>1) {
        temp = patients[size - 1];
        patients[size - 1] = patients[0];
        patients[0] = temp;
        patients.pop_back();

        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
    }
    else
    {
        patients.pop_back();
    }
    heapSize--;
}

int PatientPriorityQueuex::size() {
    return (int) patients.size();
    //return heapSize == 0;

}


string PatientPriorityQueuex::to_string() {
    std::stringstream ss;

    for(unsigned int i=0; i < patients.size(); i++)
        ss << patients.at(i).to_string() << '\n';

    return ss.str();

}

void PatientPriorityQueuex::save(string fileName)
{
    std::stringstream ss;
    std::ofstream outfile (fileName);
    for(unsigned int i=0; i < patients.size(); i++)
        outfile << patients.at(i).to_string() << '\n';


    outfile.close();
}



// Function to heapify the tree
void PatientPriorityQueuex :: heapify( int i) {
    int size =patients.size();

    // Find the largest among root, left child and right child
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && patients[largest] < patients[l])
        largest = l;
    if (r < size && patients[largest] < patients[r])
        largest = r;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
        Patient temp("","",-1);
        temp = patients[largest];
        patients[largest]=patients[i];
        patients[i] = temp;

        heapify(largest);
    }
}



#endif //P3X_PATIENTPRIORITYQUEUEX_H
