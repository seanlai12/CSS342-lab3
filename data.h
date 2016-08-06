/**
 @file data.h
 Contains the prototypes for data.cpp
 Also contains the charByte object that compareList will point to.
 Which is the character byte of the files that we are comparing for this lab.
 
 @author Sean Lai
 @author Sai Badey
 @section ASSIGNEMT Lab3
 @section DUE_DATE 9 Feb 2014
 */

#ifndef DATA_H
#define DATA_H

#include <iostream>


using namespace std;


class Data {
    
public:
    Data();
    bool operator<(Data& target);
    bool setCharByte(char target);
    char getCharByte();
    
private:
    // Data contains the character byte of certain bytes in byte numbers.
    char charByte;
    
};

#include "data.cpp"
#endif
