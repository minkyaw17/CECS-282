//
//  upDate.cpp
//  Overloading Operators (upDate)
//
//  Created by Min Kyaw on 4/20/20.
//  Copyright © 2020 Min Kyaw. All rights reserved.
//

// Min Kyaw
// CECS 282 - Sec 05
// Program #4 - Overloading Operators
// April 21, 2020

#include "upDate.hpp"
#include <iostream>
#include <ostream>
#include <string>
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

int upDate::count = 0; // for the GetDateCount method (incrementing each object created)

upDate::upDate() { // default constructor
    dptr = new int[3];
    dptr[0] = 5; // default date
    dptr[1] = 11;
    dptr[2] = 1959;
    count++;
}

upDate::upDate(int m, int d, int y) { // paremeterized constructor
    dptr = new int[3];
    if (!(m >= 0 && m <=12) || !(d >= 0 && d <= 31) || y < 1) { // checking for validation of bogus dates
        dptr[0] = 5;
        dptr[1] = 11;
        dptr[2] = 1959;
    }
    else {
        dptr[0] = m;
        dptr[1] = d;
        dptr[2] = y;
    }
    count++;
}

upDate::upDate(int J) { // J2G constructor
    dptr = new int[3];
    Julian2Greg(J, dptr[0], dptr[1], dptr[2]);
    count++;
}

upDate::upDate(const upDate &D) { // passed by Date constructor
    dptr = new int[3];
    dptr[0] = D.dptr[0];
    dptr[1] = D.dptr[1];
    dptr[2] = D.dptr[2];
    count++;
}

upDate::~upDate() { //destructor (never needs to be called - C++ will automatically call it)
    count --;
    delete []dptr;
}

void upDate::setDate(int m, int d, int y) {
    if (!(m >= 0 && m <=12) || !(d >= 0 && d <= 31) || y < 1) { // checking for validation of bogus dates
        dptr[0] = 5;
        dptr[1] = 11;
        dptr[2] = 1959;
    }
    else {
        dptr[0] = m;
        dptr[1] = d;
        dptr[2] = y;
    }
}

upDate upDate::operator+(int x) {
    upDate temp(*this);
    int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]) + x;
    Julian2Greg(JD, temp.dptr[0], temp.dptr[1], temp.dptr[2]);
    return temp;
}

upDate operator+(int x, upDate D) { //the friend method that maps together the int and the upDate object
    return D + x;
}

upDate upDate::operator-(int x) {
    upDate temp(*this);
    int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]) - x;
    Julian2Greg(JD, temp.dptr[0], temp.dptr[1], temp.dptr[2]);
    return temp;
}

int upDate::operator-(const upDate &D) { // returning Julian Date
    return (Greg2Julian(dptr[0], dptr[1], dptr[2]) - Greg2Julian(D.dptr[0], D.dptr[1], D.dptr[2]));
}

upDate upDate::operator=(const upDate &D) {
    dptr[0] = D.dptr[0];
    dptr[1] = D.dptr[1];
    dptr[2] = D.dptr[2];
    return *this;
}

upDate upDate::operator+=(int x) { // assignment operator
    int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]);
    JD += x;
    Julian2Greg(JD, dptr[0], dptr[1], dptr[2]);
    return *this;
}

upDate upDate::operator+=(const upDate &D) {
    int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]) + Greg2Julian(D.dptr[0], D.dptr[1], D.dptr[2]);
    Julian2Greg(JD, dptr[0], dptr[1], dptr[2]);
    return *this;
}

upDate upDate::operator-=(int x) {
    int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]);
    JD -= x;
    Julian2Greg(JD, dptr[0], dptr[1], dptr[2]);
    return *this;
}

upDate upDate::operator-=(const upDate &D) { // returning Greg Date
    int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]) - Greg2Julian(D.dptr[0], D.dptr[1], D.dptr[2]);
    Julian2Greg(JD, dptr[0], dptr[1], dptr[2]);
    return *this;
}

upDate upDate::operator++() {
    int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]);
    JD++;
    Julian2Greg(JD, dptr[0], dptr[1], dptr[2]);
    return *this;
}

upDate upDate::operator++(int) {
    upDate temp(dptr[0], dptr[1], dptr[2]);
    int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]);
    JD++;
    Julian2Greg(JD, dptr[0], dptr[1], dptr[2]);
    return temp;
}

upDate upDate::operator--() {
    int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]);
    JD--;
    Julian2Greg(JD, dptr[0], dptr[1], dptr[2]);
    return *this;
}

upDate upDate::operator--(int) {
    upDate temp(dptr[0], dptr[1], dptr[2]);
    int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]);
    JD--;
    Julian2Greg(JD, dptr[0], dptr[1], dptr[2]);
    return temp;
}

bool upDate::operator==(const upDate &D) { // logic operator checking if 2 dates are equal
    return (Greg2Julian(dptr[0], dptr[1], dptr[2]) == Greg2Julian(D.dptr[0], D.dptr[1], D.dptr[2]));
}

bool upDate::operator>(const upDate &D) {
    return (Greg2Julian(dptr[0], dptr[1], dptr[2]) > Greg2Julian(D.dptr[0], D.dptr[1], D.dptr[2]));
}

bool upDate::operator<(const upDate &D) {
    return (Greg2Julian(dptr[0], dptr[1], dptr[2]) < Greg2Julian(D.dptr[0], D.dptr[1], D.dptr[2]));
}

ostream& operator<<(ostream& o, const upDate& D) { // ostream cout
    o << D.dptr[0] << "/" << D.dptr[1] << "/" << D.dptr[2];
    return o;
}

int upDate::getMonth(){
    return dptr[0];
}

int upDate::getDay() {
    return dptr[1];
}

int upDate::getYear() {
    return dptr[2];
}

string upDate::getMonthName() {
    switch (dptr[0]) {
        case 1:
            return "January";
        case 2:
            return "February";
        case 3:
            return "March";
        case 4:
            return "April";
        case 5:
            return "May";
        case 6:
            return "June";
        case 7:
            return "July";
        case 8:
            return "August";
        case 9:
            return "September";
        case 10:
            return "October";
        case 11:
            return "November";
        case 12:
            return "December";
    }
    return "";
}

int upDate::GetDateCount() {
    return count;
}

int upDate::julian() {
    int JD = Greg2Julian(dptr[0], dptr[1], dptr[2]);
    return JD;
}

//void upDate:: display() {
//    string Months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
//    // if statements for bogus if needed
//    cout << dptr[0] << " " << dptr[1] << ", " << dptr[2];
//}
