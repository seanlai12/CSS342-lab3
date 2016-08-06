/**
@file compareList.cpp
contains constructor,destructor for a linked list.
Also contains basic functions for linked list: insert, remove, is empty, operator overloads.
Contains 2 functions pertaining to printing out results and formatting.

@author Sean Lai
@author Sai Badey
@section ASSIGNEMT Lab3
@section DUE_DATE 9 Feb 2014
*/


#include "compareList.h"
#include "data.h"
#ifndef COMPARELIST_CPP
#define COMPARELIST_CPP
#include <string.h>
#include <iostream>
#include <iomanip>

using namespace std;

int percentMatch = 0;
int listCount = 0;
bool printToFile = false;
int pfArr[] = {2, 3, 5, 13, 89, 233, 1597, 28657, 514229, 433494437};
ofstream fout;

/**
 Constructor ensures each new list starts with the head at NULL.
 */
compareList::compareList() {
    head = NULL;
}

/**
 Destructor ensures that deleting the list also deletes all the data objects from the node
*/
compareList::~compareList() {
    Node* current = head;
    Node* temp = head;
    
    while(current != NULL){
        delete current->dataptr;
        temp = current;
        current = current->next;
        delete temp;
    }
}

/**
 Insert function which takes a character to insert into a linked list.
 First, wraps target inside a data object, inserts this into node, then inserts node into list.
 Returns true if insert completes successfully.
*/
bool compareList::insert(char target) {
    if (target == (char) NULL) {
        return false;
    }
    Node* ptr= new Node;
    Data* dat = new Data;
    dat->setCharByte(target);
    listCount++;
    if (ptr == NULL){
        return false;                 // out of memory, bail
    }
    ptr->dataptr = dat;
    
    // if the list is empty or if the node should be inserted before
    // the first node of the list
    if (isEmpty()) {
        ptr->next = head;
        head = ptr;
        ptr = NULL;
      
        return true;
    }
   
    // then check the rest of the list until we find where it belongs
    else {
        Node* current = head->next;          // to walk list
        Node* previous = head;               // to walk list, lags behind
        
        // walk until end of the list or found position to insert
        while (current != NULL) {
            previous = current;                  // walk to next node
            current = current->next;
        }
        
        // insert new node, link it in
        ptr->next = current;
        previous->next = ptr;
        ptr = NULL;
        return true;
    }
    return false;
}

/**
 Remove function searches for a target character in the linked list. Deletes the the first node
 in which the target character resides.
 Returns true if remove completes successfully.
*/
bool compareList::remove(char target) {
	Node *previous = head;
	Node *current = head;
    
	if (head == NULL)
		return false;
    
	while (current != NULL) { // Case for deleting non-first node.
		if (current->dataptr->getCharByte() != target) {
            previous = current;
			current = current->next;
		}
        else { // found data
            listCount--;
            previous->next = current->next;
            current->dataptr->setCharByte('z');
            current->next = NULL;
            delete current->dataptr;
            delete current;
            return true;
        }
	}
	return false;
}

/**
 Simple is empty function checks if the head of the list points to a node or NULL
 Returns true if the head does not point to any node
*/
bool compareList::isEmpty() const {
    return head == NULL;
}

/**
 Equals operator override. When one list is compared to another list, returns true if the two lists are equal,
 or if the two lists are of different length, returns true if they are true up to the length of the short list.
 Otherwise returns false, also returns false if one of the lists is empty but the other is not.
 
 Also tracks which characters are equal in order to print out formatting to file or console
*/
bool compareList::operator==(const compareList& bList)const {
    int count = 0;
    percentMatch = 0;
    Node* aCurrent = this->head;
    Node* bCurrent = bList.head;
    if (aCurrent != NULL && bCurrent == NULL) {    //checks to see if either list is empty
        return false;
    }
    if (aCurrent == NULL && bCurrent != NULL) {
        return false;
    }
    while (aCurrent != NULL && bCurrent != NULL) {    //traversing list and checking all data
        
        if (aCurrent->dataptr->getCharByte() != bCurrent->dataptr->getCharByte()) {
            if (printToFile) {
                fout << endl;
                printPFCount(count, true);
            }
            else {
                cout << endl;
                printPFCount(count, false);
            }
            return false;
        }
        if (printToFile) {
            fout << " - ";
        }
        else {
            cout << " - ";
        }
        count++;
        percentMatch++;
        aCurrent = aCurrent->next;
        bCurrent = bCurrent->next;
    }
    if (printToFile) {
        fout << endl;
        printPFCount(count, true);
    }
    else {
        cout << endl;
        printPFCount(count, false);
    }
    return true;
}


/**
 Not equals operator override.Essentially, the reverse of the equals operator.
 When one list is compared to another list, returns false if the two lists are equal,
 or if the two lists are of different length, returns false if they are true up to the length of the short list.
 Otherwise returns true, also returns true if one of the lists is empty but the other is not.
 
 Also tracks which characters are equal in order to print out formatting to file or console
*/
bool compareList::operator!=(const compareList& bList)const {
    percentMatch = 0;
    int count = 0;
    Node* aCurrent = this->head;
    Node* bCurrent = bList.head;
    if (aCurrent != NULL && bCurrent == NULL) {    //checks to see if either list is empty
        return true;
    }
    if (aCurrent == NULL && bCurrent != NULL) {
        return true;
    }
    while (aCurrent != NULL && bCurrent != NULL) { //traverses list to check all characters
        
        if (aCurrent->dataptr->getCharByte() != bCurrent->dataptr->getCharByte()) {
            if (printToFile) {
                fout << endl;
            }
            else {
                cout << endl;
            }
            return true;
        }
        if (printToFile) {
            fout << " - ";
        }
        else {
            cout << " - ";
        }
        count++;
        percentMatch++;
        aCurrent = aCurrent->next;
        bCurrent = bCurrent->next;
    }
    if (printToFile) {
        fout << endl;
        printPFCount(count, true);
    }
    else {
        cout << endl;
        printPFCount(count, false);
    }
    return false;
}

/**
 Output stream operator overload. Prints out the contents of the list in which this is called.
 Returns ostream object which contains some formatting along with the data
*/
ostream& operator<<(ostream &console, const compareList& thelist) {
    int count = 0;
    compareList::Node* current = thelist.head;
    while (current != NULL) {
        if (!printToFile) {
            if (current->dataptr->getCharByte() == ' ') {
                
                console << "' '";
            }
            else if (current->dataptr->getCharByte() == '\t') {
                console << "\\t ";
            }
            else if (current->dataptr->getCharByte() == '\n') {
                console << "\\n ";
            }
            else {
                console  << " " << current->dataptr->getCharByte() << " ";
            }
        }
        else {
            if (current->dataptr->getCharByte() == ' ') {
                fout << "' '";
            }
            else if (current->dataptr->getCharByte() == '\t') {
                fout << "\\t ";
            }
            else if (current->dataptr->getCharByte() == '\n') {
                fout << "\\n ";
            }
            else {
                fout  << " " << current->dataptr->getCharByte() << " ";
            }
        }
        count++;
        current = current->next;
    }
    return console;
}


/**
 A function whose sole purpose is formatting the output. It is handed a count of
 matching chars and then prints out to console or file the identity of the matching chars
*/
void compareList::printPFCount(int count, bool printFile)const {
    if(count > 0) {
        if(!printFile) {
            cout << "Matched Byte Number: ";
        }
        else {
            fout << "Matched Byte Number: ";
        }
        for (int i=0; i < count; i++) {
            if(!printFile){
                cout << pfArr[i] << " ";
            }
            else {
                fout << pfArr[i] << " ";
            }
        }
        if(!printFile) {
            cout << endl;
        }
        else {
            fout << endl;
        }
    }
}
#endif
