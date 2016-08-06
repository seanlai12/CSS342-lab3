/**
 @file Data.cpp
 contains constructor for the Data object. 
 Also has overloaded overators, and charByte related functions.
 
 @author Sean Lai
 @author Sai Badey
 @section ASSIGNEMT Lab3
 @section DUE_DATE 9 Feb 2014
 */

#ifndef DATA_CPP
#define DATA_CPP
#include <string.h>
#include <iostream>
#include <iomanip>

using namespace std;


#include "data.h"

/**
 Constructor that creates a data with a placehold charByte.
 */
Data::Data() {
    charByte = ' ';
}

/**
 Operator overload for <. It will compare two Data object's sizes.
 @return true if the left side operator charByte is smaller than the right side charByte.
 */
bool Data::operator<(Data& target){
    if(this->getCharByte() < target.getCharByte()){
        return true;
    }
    return false;
}

/**
 This function will modify the charByte for the data object.
 
 @param target character that this function will set to its data.
 @return true if data is modified successfully
 */
bool Data::setCharByte(char target){
    charByte = target;
    return true;
    
}

/**
 This function will get the charByte at the data object.

 @return charByte, the charByte at this data object.
 */
char Data::getCharByte() {
    return charByte;
}



#endif
