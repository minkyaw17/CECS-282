//
//  myDate.cpp
//  myDate Object
//
//  Created by Min Kyaw on 2/16/20.
//  Copyright © 2020 Min Kyaw. All rights reserved.
//

// Min Kyaw
// CECS 282 - Sec 05
// Program #2 - myDate Object
// March 3, 2020

#include "myDate.hpp"
#include <iostream>
#include <string.h>
using namespace std;

int Greg2Julian(int Month, int Day, int Year) {
    int i, j, k, JD;
    i = Year;
    j = Month;
    k = Day;
    
    JD = k - 32075 + 1461 * (i + 4800 + (j - 14)/12 ) / 4 + 367 * (j - 2 - (j - 14) / 12 * 12) / 12 - 3 * ((i + 4900 + (j - 14) / 12) / 100) / 4;
    
    return JD;
}

void Julian2Greg(int JD, int &Month, int &Day, int &Year) {
    int i,j,k;
    int l = JD + 68569;
    int n = 4 * l/ 146097;
    l = l - (146097 * n + 3) / 4;
    i = 4000 * (l + 1) / 1461001;
    l = l - 1461 * i / 4 + 31;
    j = 80 * l / 2447;
    k = l - 2447 * j / 80;
    l = j / 11;
    j = j + 2 - 12 * l;
    i = 100 * (n - 49) + i + l;
    
    Year = i;
    Month = j;
    Day = k;
}

myDate::myDate() {
    Year = 1959;
    Month = 05;
    Day = 11;
}

myDate::myDate(int M,int D,int Y) {
    if (!(M >= 0 && M <=12) || !(D >= 0 && D <= 31) || Y < 1) { // checking for validation of bogus dates
        Month = 5;
        Day = 11;
        Year = 1959;
    }
    else {
    Year = Y;
    Month = M;
    Day = D;
    }
}

void myDate:: display() {
    string Months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    // if statements for bogus if needed
    cout << Months[Month-1] << " " << Day << ", " << Year;
}

void myDate:: increaseDate(int N) {
    int JD = Greg2Julian(Month, Day, Year);
    JD += N; // can increase by a negative number
    int &m = Month; // passing by reference
    int &d = Day;
    int &y = Year;
    Julian2Greg(JD, m, d, y);
}

void myDate:: decreaseDate(int N) {
    int JD = Greg2Julian(Month,Day, Year);
    JD -= N; // can decrease by a negative number (+)
    int &m = Month; // passing by reference
    int &d = Day;
    int &y = Year;
    Julian2Greg(JD, m, d, y);
}

int myDate::daysBetween(myDate D){
    int JD1 = Greg2Julian(Month, Day, Year);
    int JD2 = Greg2Julian(D.getMonth(), D.getDay(), D.getYear());
    return JD2 - JD1;
}

int myDate::getMonth(){
    return Month;
}

int myDate::getYear(){
    return Year;
}

int myDate::getDay(){
    return Day;
}

int myDate::dayOfYear() {
    int dayMonth = 0;
    if (((Year % 4 == 0) && (Year % 100 != 0)) || (Year % 400 == 0)) {
        for (int i = 0; i < Month - 1; i++) {
            dayMonth += numOfDaysLeap[i];
        }
    }
    
    else {
        for (int i = 0; i < Month - 1; i++) {
            dayMonth += numOfDays[i];
        }
    }
    
    return dayMonth + Day;
    
}

string myDate::dayName(){
    string days[7] = {"Monday","Tuesday","Wednesday","Thursday","Friday", "Saturday", "Sunday"};
    int JD = Greg2Julian(Month, Day, Year);
    return days[JD % 7];
}
