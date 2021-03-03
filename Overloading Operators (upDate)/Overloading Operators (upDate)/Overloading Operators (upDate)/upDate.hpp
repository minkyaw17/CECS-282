//
//  upDate.hpp
//  Overloading Operators (upDate)
//
//  Created by Min Kyaw on 4/20/20.
//  Copyright © 2020 Min Kyaw. All rights reserved.
//

// Min Kyaw
// CECS 282 - Sec 05
// Program #4 - Overloading Operators
// April 21, 2020

#ifndef upDate_hpp
#define upDate_hpp

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

class upDate {
private:
    int *dptr;
    static int count; // getting the count for the GetDateCount() method
    
public:
    upDate();
    upDate(int, int, int);
    upDate(int);
    upDate(const upDate &);
    ~upDate();
    void setDate(int, int, int);
    int getMonth();
    int getDay();
    int getYear();
    string getMonthName();
//    void display();
    
    // operator overload methods
    upDate operator+(int);
    friend upDate operator+(int, upDate);
    upDate operator-(int);
    int operator-(const upDate &);
    upDate operator=(const upDate &);
    
    upDate operator+=(int);
    upDate operator+=(const upDate &);
    upDate operator-=(int);
    upDate operator-=(const upDate &);
    upDate operator++();
    upDate operator++(int);
    upDate operator--();
    upDate operator--(int);
    
    // logic overload methods
    bool operator==(const upDate &);
    bool operator>(const upDate &);
    bool operator<(const upDate &);
    
    // ostream cout
    friend ostream& operator<<(ostream &, const upDate &);
    
    // count and julian methods for the main provided
    static int GetDateCount();
    int julian();
    
};


#endif /* upDate_hpp */
