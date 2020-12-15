// Ashlesha Bhamare
// MemberList.h
// 09/29/2020

#ifndef P1_MEMBERLIST_H
#define P1_MEMBERLIST_H

#include <string>
#include <iostream>
using namespace std;


class MemberList {
public:
    MemberList(int);
    ~MemberList();

    MemberList(const MemberList &);

    void add(string name, int account,bool displayFlag);



    bool empty() const;                  // determines if list is empty or not

    int size() const;                    // number of elements in array

    string to_string() const;

    string getMemberName(int memberAccount) const ;

    int getAccountNumber(int i) const ;

private:
    struct Member {
        string memberName;
        int memberAccount;

    };
    Member*list;                          // Pointer to the array
    int capacity;                         // capacity of array
    int numElements;                      // Number of elements
    void resize();

};


#endif //P1_MEMBERLIST_H
