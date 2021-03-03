//
//  main.cpp
//  BigInt
//
//  Created by Min Kyaw on 5/3/20.
//  Copyright © 2020 Min Kyaw. All rights reserved.
//

// Min Kyaw
// CECS 282 - Sec 05
// Program #5 - Overloading Operators
// May 7, 2020

#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <vector>
#include <map>
#include <string>

using namespace std;

class BigInt {
private:
    vector<char> bigI; // no dynamically allocated memory - no need for copy contructor and assignment operator
public:
    BigInt();
    BigInt(int);
    BigInt(string);
    
    BigInt operator+(BigInt);
    BigInt operator-(BigInt) const;
    friend BigInt operator+(int, const BigInt &);
    friend BigInt operator-(int, const BigInt &);
    
    BigInt operator+=(BigInt);
    BigInt operator-=(BigInt);
    
    BigInt& operator++();
    BigInt operator++(int);
    BigInt& operator--();
    BigInt operator--(int);
    
    
    friend ostream& operator<<(ostream &, const BigInt &);
    
    friend bool operator==(const BigInt &, const BigInt &);
    friend bool operator>(const BigInt &, const BigInt &);
    friend bool operator<(const BigInt &, const BigInt &);
    friend bool operator>=(const BigInt &, const BigInt &);
    friend bool operator<=(const BigInt &, const BigInt &);
    
    void print();
    
};

int goldRabbits(int);
BigInt goldRabbits(BigInt);
void pause() {cout << "Press Enter to continue..."; getchar();}

int main() { // MAIN
    BigInt B1("123456789123456789123456789123456789");
    BigInt B2(B1);
    BigInt MAX(INT_MAX);
    cout << "B1: " << B1 << "\nB2: " << B2 << "\nMAX: " << MAX << endl;
    pause();
    cout << "\nB1: ";
    B1.print();
    cout << endl;
    pause();

    for (BigInt i = 0; i <= 3000; i++)
    {
        cout << "\ngoldRabbits(" << i << ") = " << goldRabbits(i);
    }
    cout << endl;
    pause();

    cout << "\nThis is the value of goldRabbits(3000)\n\n";
    BigInt gR3000 = goldRabbits(BigInt(3000));
    gR3000.print();
    cout << endl;
    pause();
    
}

int goldRabbits(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return goldRabbits(n - 1) + goldRabbits(n - 2);
}

BigInt goldRabbits(BigInt n) {
    static map<BigInt, BigInt> grMap;
    
    if(n == 0 || n == 1)
        return BigInt(1);
    else if (grMap.find(n) != grMap.end())
        return grMap.find(n)->second;
    
    else {
        BigInt temp = goldRabbits(n - 1) + goldRabbits(n - 2);
        grMap[n] = temp;
        return temp;
    }
}

BigInt::BigInt() {
    bigI.push_back(0);
}

BigInt::BigInt(int val) {
    while (val > 9) {
        int num = val % 10;
        bigI.push_back(num);
        val /= 10;
    }
    bigI.push_back(val);
}

BigInt::BigInt(string s) {
    for (int i = 0; i < s.size(); i++) {
        bigI.insert(bigI.begin(), s[i] - 48);
    }
}

BigInt BigInt::operator+(BigInt B) {
    BigInt temp1, temp2;

    if (bigI.size() < B.bigI.size()) {
        temp2 = *this;
        temp1 = B;
    } else {
        temp1 = *this;
        temp2 = B;
    }

    for (int i = 0; i < temp2.bigI.size(); i++)
        temp1.bigI[i] += temp2.bigI[i];

    for (int j = 0; j < temp1.bigI.size() - 1; j++) {
        if (temp1.bigI[j] > 9) {
            if (temp1.bigI[j + 1] != 0) {
                temp1.bigI[j + 1]++;
                temp1.bigI[j] -= 10;
            } else {
                temp1.bigI[j + 1] = 1;
                temp1.bigI[j] -= 10;
            }
        }
    }
    if (temp1.bigI.back() > 9) {
        temp1.bigI.back() -= 10;
        temp1.bigI.push_back(1);
    }
    return temp1;
}

BigInt operator+(int n, const BigInt &B) {
    return BigInt(n) + B;
}

BigInt BigInt::operator+=(BigInt B) {
    *this = *this + B;
    return *this;
}

BigInt BigInt::operator-(BigInt B)const{
    BigInt temp(*this);
    while (B.bigI.size() != temp.bigI.size()) {
        if (B.bigI.size() > temp.bigI.size()) {
            temp.bigI.push_back(0);
        }
        else {
           B.bigI.push_back(0);
        }
    }

    for (int i = 0; i < temp.bigI.size();i++) {
        if (temp.bigI[i] < B.bigI[i]) {
            temp.bigI[i] += 10;
            temp.bigI[i + 1] -= 1;
        }
        temp.bigI[i] -= B.bigI[i];
        if (temp.bigI[i] == 0 && B.bigI[i] == 0 && i == temp.bigI.size() - 1) {
            temp.bigI.erase(temp.bigI.end() - 1);
        }
    }
    return temp;
}

BigInt operator-(int n, const BigInt &B) {
    return BigInt(n) + B;
}

BigInt BigInt::operator-=(BigInt B) {
    *this = *this - B;
    return *this;
}

BigInt& BigInt::operator++() {
    *this += 1;
    return *this;
}

BigInt BigInt::operator++(int n) {
    BigInt temp = *this;
    ++*this;
    return temp;
}

BigInt& BigInt::operator--() {
    *this -= 1;
    return *this;
}

BigInt BigInt::operator--(int n) {
    BigInt temp = *this;
    --*this;
    return temp;
}

ostream& operator<<(ostream &o, const BigInt &B) {
    vector<char>::const_reverse_iterator rit = B.bigI.rbegin();
    int length = B.bigI.size();
    int count = 0;
    int temp = length;
    
    while (temp >= 10) {
        temp /= 10;
        count++;
    }
    
    if (length <= 12) {
        while(rit != B.bigI.rend()) {
            o << (int) *rit++;
        }
    }
    
    else {
        o << (int) *rit++ << ".";
        for (int i = 1; i < 12 - count; i++) {
            o << (int) *rit++;
        }
        o << "e" << length;
    }
    return o;
}

bool operator>(const BigInt &B1, const BigInt &B2) {
    if (B1.bigI.size() > B2.bigI.size()) {
        return true;
    }
    else if (B1.bigI.size() < B2.bigI.size()) {
        return false;
    }
    
    else {
        vector<char>::const_reverse_iterator ritr1, ritr2;
            ritr1 = B1.bigI.rbegin();
            ritr2 = B2.bigI.rbegin();
            
            while ((*ritr1++ == *ritr2++) && ritr1 != B1.bigI.rend());
            --ritr1;
            --ritr2;
            return (int) *ritr1 > (int )*ritr2;
    }
}

bool operator<(const BigInt &B1, const BigInt &B2) {
    if (B1.bigI.size() < B2.bigI.size()) {
        return true;
    }
    else if (B1.bigI.size() > B2.bigI.size()) {
        return false;
    }
    
    else {
        vector<char>::const_reverse_iterator ritr1, ritr2;
            ritr1 = B1.bigI.rbegin();
            ritr2 = B2.bigI.rbegin();
            
            while ((*ritr1++ == *ritr2++) && ritr1 != B1.bigI.rend());
            --ritr1;
            --ritr2;
            return (int) *ritr1 < (int )*ritr2;
    }
}

bool operator>=(const BigInt &B1, const BigInt &B2) {
    if (B1 > B2 || B1 == B2) {
        return true;
    }
    else {
        return false;
    }
}

bool operator<=(const BigInt &B1, const BigInt &B2) {
    if (B1 < B2 || B1 == B2) {
        return true;
    }
    else {
        return false;
    }
}

bool operator==(const BigInt &B1, const BigInt &B2) {
    if (B1.bigI.size() != B2.bigI.size()) {
        return false;
    }
    
    else {
        vector<char>::const_reverse_iterator ritr1, ritr2;
        ritr1 = B1.bigI.rbegin();
        ritr2 = B2.bigI.rbegin();
        
        while ((*ritr1++ == *ritr2++) && ritr1 != B1.bigI.rend());
        --ritr1;
        --ritr2;
        return (int) *ritr1 == (int )*ritr2;
    }
}


void BigInt::print() {
    vector<char>::reverse_iterator ritr;
    for(ritr = bigI.rbegin(); ritr != bigI.rend(); ritr++)
        cout << (int)*ritr;
    }
