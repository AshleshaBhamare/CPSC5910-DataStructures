//
// Created by Rishi Patil on 9/13/20.
//

#ifndef ICE1_DATE_H
#define ICE1_DATE_H
using namespace std;
#include <string>



class Date {

public:
    Date();
    Date(int m, int d, int y);
    void setDate(int m, int d, int y);
    void getDate() const;
    string getSeason() const;
private:
    int month;
    int day;
    int year;


};


#endif //ICE1_DATE_H
