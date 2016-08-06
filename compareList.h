/**
 @file compareList.h
 Contains the prototypes for compareList.cpp
 Also contains the struct for the node.
 This node will compose the list, and will hold the data object 
 which houses the char we are comparing.
  
 @author Sean Lai
 @author Sai Badey
 @section ASSIGNEMT Lab3
 @section DUE_DATE 9 Feb 2014
 */

#ifndef COMPARELIST_H
#define COMPARELIST_H
#include <iostream>
#include <fstream>
#include "data.cpp"


using namespace std;


class compareList {
//makes friend with the ostream in order to override the << operator to print out the lists easier
friend ostream &operator<<(ostream&, const compareList&);
    
public:
    compareList();
    ~compareList();
    bool isEmpty()const;
    bool insert(char target);
    bool remove(char target);
    bool operator==(const compareList& bList)const;
    bool operator!=(const compareList& bList)const;
    void printPFCount(int count, bool printType)const;
    
    
private:
   //the node only contains pointers (one to a data object, one to the next node)
    struct Node {
        Data* dataptr;
        Node* next;
    };
    //the head pointer, the main leash which lets us access the linked list
    Node* head;
};
#include "compareList.cpp"
//#include "lab3testlist.cpp"
#endif

