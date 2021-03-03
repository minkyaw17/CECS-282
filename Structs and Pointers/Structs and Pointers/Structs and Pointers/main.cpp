//
//  main.cpp
//  Structs and Pointers
//
//  Created by Min Kyaw on 3/5/20.
//  Copyright © 2020 Min Kyaw. All rights reserved.
//

// Min Kyaw
// CECS 282 - Sec 05
// Program #3 - Structs and Pointers
// March 3, 2020

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iomanip>
#include "myDate.hpp"

using namespace std;

struct Student {
    char Name[20];
    int StudentID;
    char Grade;
    myDate bDay;
    string HomeTown;
};

void swap(Student **x, Student **y);
void populate(Student *S[]);
void display(Student *D[]);
myDate randomDate(myDate S, myDate F);
int randomIDGenerator();
void sortByName(Student *S[]);
void sortById(Student *S[]);
void sortByGrade(Student *S[]);
void sortBybDay(Student*S[]);
void sortByHometown(Student *S[]);
void copy(Student *p[], Student *q[]);
int main() {
    
//    srand(time(NULL));
    Student *S[10];
    populate(S);
    Student *S2[10];
    copy(S2, S);
//    display(S);
    
    int input = 0;
    
    while (input != 6) {
        cout << endl << "1) Display list sorted by Name" << endl<<
        "2) Display list sorted by Student ID" << endl <<
        "3) Display list sorted by Grade" << endl <<
        "4) Display list sorted by Birthday" << endl <<
        "5) Display list sorted by Home Town" << endl <<
        "6) Exit" << endl;
        
        cin >> input;
        
        switch (input) {
            case 1:
                sortByName(S2);
                display(S2);
                break;
            case 2:
                sortById(S2);
                display(S2);
                break;
                case 3:
                sortByGrade(S2);
                display(S2);
                break;
                case 4:
                sortBybDay(S2);
                display(S2);
                break;
                case 5:
                sortByHometown(S2);
                display(S2);
                break;
                case 6:
                break;
            default:
                break;
        }
    }
}
//    char p [] = "Tech";
//    cout<< strlen(p) << endl; // p = destination, q = source;
//    return 0;

// swap function to use in sorting
void swap(Student **x, Student **y) {
    Student *temp;
    temp = *y;
    *y = *x;
    *x = temp;
}

myDate randomDate(myDate S, myDate F) {
    int D = S.daysBetween(F);
//    srand(time(0));
    int R = rand() % D;
    S.increaseDate(R);
    return S;
}

// random ID to use in populating students
int randomIDGenerator() {
//    srand(time(0));
    return (rand() % (9999 - 1000 + 1) + 1000);
}

void sortByName(Student *S[]) {
    for (int i = 0 ; i < 10; i++) {
        for (int j = 0; j < 9 - i; j++)
            if (strcmp(S[j]->Name, S[j+1]->Name) > 0) {
                swap(S[j], S[j+1]);
        }
    }
}

void sortById(Student *S[]) {
    for (int i = 0; i <10; i++) {
        for (int j = 0; j < 9 - i; j++) {
            if (S[j]->StudentID > S[j + 1]->StudentID)
                swap(S[j], S[j + 1]);
        }
    }
}

void sortByGrade(Student *S[]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9 - i; j++) {
            if (S[j]->Grade > S[j + 1]->Grade)
                swap(S[j], S[j + 1]);
        }
    }
}

void sortBybDay(Student*S[]) {

    for (int i = 0;i < 10; i++) {
        for (int j = 0;j < 9 - i;j++) {

            int m1, d1, y1, m2, d2, y2;

            m1 = S[j]->bDay.getMonth();
            d1 = S[j]->bDay.getDay();
            y1 = S[j]->bDay.getYear();

            m2 = S[j+1]->bDay.getMonth();
            d2 = S[j+1]->bDay.getDay();
            y2 = S[j+1]->bDay.getYear();

            if (S[j] -> bDay.Greg2Julian(m1,d1,y1) >
                S[j+1] -> bDay.Greg2Julian(m2,d2,y2))
                swap(S[j], S[j+1]);
        }
    }
}

void sortByHometown(Student *S[]) {
    for(int i = 0; i <10; i++) {
        for (int j = 0; j < 9 - i; j++) {
            if((S[j]->HomeTown).compare(S[j+1]->HomeTown)>0)
                swap(S[j], S[j+1]);
        }
    }
}

void populate(Student *S[]) {
    const char *nameList[] = {"Spider Man", "Super Man", "Bat Man", "Iron Man", "SpongeBob", "Bob", "Minny", "Patrick Star", "Tommy", "Calvin"};
    char grades[] = {'A', 'B', 'C', 'D', 'F'};
    string HomeTowns[] = {"New York City", "Metropolis", "Gotham City", "Malibu", "Bikini Bottom", "Los Angeles", "Culver City", "Bedrock", "Chicago", "Compton"};
    
    myDate Start(1,1,1999);
    myDate End(12,31,2004);
    
    for (int i = 0; i < 10; i++) {
        S[i] = new Student;
        strcpy(S[i]->Name, nameList[i]);
        S[i]->StudentID = randomIDGenerator();
        S[i]->Grade = grades[rand() % 5];
        S[i]->bDay = randomDate(Start, End);
        S[i]->HomeTown = HomeTowns[i];
    }
}

void display(Student *D[]) {
    cout << left << setw(15) << "Name" << setw(15) << "Student ID" << setw(15) << "Grade" << setw(25) << "Birthday" << setw(15) << "Home Town" << endl;
    cout << left << setw(15) << "----" << setw(15) << "----------" << setw(15) << "-----" << setw(25) << "--------" << setw(15) << "---------" << endl;
    for (int i = 0; i < 10; i++) {
        cout << left << setw(15) << D[i]->Name << setw(15) << D[i]->StudentID << setw(15) << D[i]->Grade << setw(25) << D[i]->bDay.toString() << setw(25) << D[i]->HomeTown << endl;
    }
    cout << endl;
}

void copy(Student *p[], Student *q[]) {
    for (int i = 0; i < 10; i++) {
        p[i] = new Student;
        p[i] = q[i];
    }
}


//void strcpy(char d[], char s[]) {
//    int i = 0;
//    while (s[i] != '\0') {
//        d[i] = s[i];
//        i++;
//    }
//
//    d[i] = '\0';
//
//}

//void strcpy(char *p, char *q) {
//    while ((*p++ = *q++));
//}
//
//int strcmp(char x[], char y[]) {
//    int i = 0;
//    while ((x[i] != '\0' && (y[i] != '\0'))) {
//        i++;
//        if ((x[i] - y[i]) < 0)
//            return -1;
//        else if ((x[i] - y[i] > 0))
//            return 1;
////        i++;
//    }
//    return 0;
//}
//
//int strlen(char arr[]) {
//    int i = 0;
//    while (arr[i] != '\0') {
//        i++;
//    }
//    return i;
//}
//
//
