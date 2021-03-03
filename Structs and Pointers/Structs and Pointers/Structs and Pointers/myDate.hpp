//
//  myDate.hpp
//  Structs and Pointers
//
//  Created by Min Kyaw on 3/15/20.
//  Copyright © 2020 Min Kyaw. All rights reserved.
//

// Min Kyaw
// CECS 282 - Sec 05
// Program #3 - Structs and Pointers
// March 3, 2020

#ifndef myDate_hpp
#define myDate_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

class myDate {
private:
    int Year;
    int Month;
    int Day;
    int numOfDays [12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int numOfDaysLeap [12] = {31,29,31,30,31,30,31,31,30,31,30,31};

public:
    myDate();
    myDate(int Y,int M,int D);
    int Greg2Julian(int Month, int Day, int Year);
    void Julian2Greg(int JD, int &Month, int &Day, int &Year);
    void display();
    void increaseDate(int N);
    void decreaseDate(int N); // should be able to take in a negative number
    int daysBetween(myDate D);
    int getMonth();
    int getDay();
    int getYear();
    int dayOfYear();
    string dayName();
//    myDate randomDate(myDate S, myDate F);
    string toString();
};

#endif /* myDate_hpp */
