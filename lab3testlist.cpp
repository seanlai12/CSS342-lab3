//
//  lab3testlist.cpp
//  lab03
//

#include "compareList.h"
#include "data.h"
#ifndef LAB3TESTLIST_CPP
#define LAB3TESTLIST_CPP
#include <string.h>
#include <iostream>
#include <iomanip>

using namespace std;

int percentMatch = 0;
int listCount = 0;
bool printToFile = false;
int pfArr[] = {2, 3, 5, 13, 89, 233, 1597, 28657, 514229, 433494437};
ofstream fout;

int main(int argc, const char * argv[])
{
    // Tests the case when inserting NULL. NULL byte is inserted.
compareList test1;
compareList test2;
test1.insert(NULL);

cout << test1;
    
    test1.insert('a');
    test1.insert('b');
    // Nothing happen when removing 'c'. As it doesn't exist.
    test1.remove('c');

    // test1 includes {a, b}
    // test2 is NULL.
    cout << test1 << endl;
    cout << test2;
    
    // These two printPFCount should not print anything, since it will only print
    // if the first variable count is > 0.
    test1.printPFCount(-1, false);
    test1.printPFCount(NULL, false);
    
    
    if(test1 == test2) {
        cout << "This should not be printed because test2 is NULL and test1 is not\n";
    }
    test2.insert('a');
    
    if(test1 == test2) {
        cout << "This should be printed, since test2 now partially matches test1\n";
    }
    
    compareList test3;
    compareList test4;
    test4.insert('a');
    
    if(test3 == test4) {
        cout << "This should not be printed because test4 is NULL and test3 is not\n";
    }
    
    if(test3 != test4) {
        cout << "This should be printed because test4 is NULL and test3 is not\n";
    }
    
}
    
    
    
compareList::compareList() {
    head = NULL;
}

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


bool compareList::insert(char target) {
    if (target == NULL) {
        return false;
    }
    Node* ptr= new Node;
    Data* dat = new Data;
    dat->setCharByte(target);
    listCount++;
    if (ptr == NULL){
        
        return false;                 // out of memory, bail
    }
    // brb bathroom!
    ptr->dataptr = dat;
    
    // if the list is empty or if the node should be inserted before
    // the first node of the list
    if (isEmpty()) {
        ptr->next = head;
        head = ptr;
        //        cout << head->dataptr->getCharByte();
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

bool compareList::isEmpty() const {
    return head == NULL;
}

bool compareList::operator==(const compareList& bList)const {
    int count = 0;
    percentMatch = 0;
    Node* aCurrent = this->head;
    Node* bCurrent = bList.head;
    if (aCurrent != NULL && bCurrent == NULL) {
        return false;
    }
    if (aCurrent == NULL && bCurrent != NULL) {
        return false;
    }
    while (aCurrent != NULL && bCurrent != NULL) {
        
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

bool compareList::operator!=(const compareList& bList)const {
    percentMatch = 0;
    int count = 0;
    Node* aCurrent = this->head;
    Node* bCurrent = bList.head;
    if (aCurrent != NULL && bCurrent == NULL) {
        return true;
    }
    if (aCurrent == NULL && bCurrent != NULL) {
        return true;
    }
    while (aCurrent != NULL && bCurrent != NULL) {
        
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
