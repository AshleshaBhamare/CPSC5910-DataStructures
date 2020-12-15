// Implementation file for the FeetInches class
#include <cstdlib>  // Needed for abs()
#include <sstream>
#include "FeetInches.h"

//*********************
// PUBLIC FUNCTIONS   *
//*********************

FeetInches::FeetInches(int f, int i) {
    feet = f;
    inches = i;
    simplify();
}

void FeetInches::setFeet(int f) {
    feet = f;
}

void FeetInches::setInches(int i) {
    inches = i;
    simplify();
}

int FeetInches::getFeet() const {
    return feet;
}

int FeetInches::getInches() const {
    return inches;
}

string FeetInches::to_string() const {
    stringstream ss;
    ss << feet << "' " << inches << "\"\n";
    return ss.str();
}

FeetInches FeetInches::operator + (const FeetInches &right) {
    // TODO: Overloaded binary + operator
    // Add the right object from the current object.
    // Returns the sum. Note that neither object is changed.
/*
    // version 1
    FeetInches r;
    r.feet = this->feet + right.feet;
    r.inches = this->inches + right.inches;
    r.simplify();
    return r;
*/
    //version 2
    FeetInches temp;

    temp.feet = feet + right.feet;
    temp.inches = inches + right.inches;
    temp.simplify();

    return temp;
/*
    // Version 3
    FeetInches temp(feet - right.feet, inches - right.inches);
    return temp;
*/
}

FeetInches FeetInches::operator - (const FeetInches &right) {
    // TODO: Overloaded binary - operator
    // Subtracts the right object from the current object.
    // Returns the difference. Note that neither object is changed.

    FeetInches temp;

    temp.feet = feet - right.feet;
    temp.inches = inches - right.inches;
    temp.simplify();

    return temp;

    // Version 2
    FeetInches R;
    R.feet = feet - right.feet;
    R.inches = inches - right.inches;
    return R;

}

FeetInches& FeetInches::operator ++ () {
    // TODO: Overloaded prefix ++ operator
    // Causes the inches member to be incremented.
    // Returns the incremented object.

    ++inches;
    simplify();
    return *this;
}

FeetInches FeetInches::operator ++ (int) {
    // TODO: Overloaded postfix ++ operator
    // Causes the inches member to be incremented.
    // Returns the value of the object before the increment.

    FeetInches temp(feet, inches);
    inches++;
    simplify();

    return temp;
}

bool FeetInches::operator > (const FeetInches &right) {
    // TODO: Overloaded > operator
    // Returns true if the current object is set to a value
    // greater than that of right.
    return (feet > right.feet) || (feet == right.feet && inches > right.inches);
}

bool FeetInches::operator < (const FeetInches &right) {
    // TODO: Overloaded < operator
    // Returns true if the current object is set to a value
    // less than that of right.
    return (feet < right.feet) || (feet == right.feet && inches < right.inches);

}

bool FeetInches::operator == (const FeetInches &right) {
    // TODO: Overloaded == operator
    // Returns true if the current object is set to a value
    // equal to that of right
    return feet == right.feet && inches == right.inches;
}


//*********************
// PRIVATE FUNCTIONS  *
//*********************

void FeetInches::simplify() {
    if (inches >= 12) {
        feet += (inches / 12);
        inches = inches % 12;
    } else if (inches < 0) {
        feet -= ((abs(inches) / 12) + 1);
        inches = 12 - (abs(inches) % 12);
    }
}