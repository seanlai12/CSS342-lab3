//
//  lab3testmain.cpp
//  lab03
//

#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sys/time.h>
#include <ctime>
#include "compareList.h"
#include "data.h"

#define blank ' '
#define enter '\n'
#define tab '\t'

using namespace std;
void compareFilesPF();
void compareFilesAll();
long getFileSize(ifstream* infile);

int FILECOUNT = 0;
int NUMBER_OF_TARGETS = 0;
int primeFibonacciArr[] = {2, 3, 5, 13, 89, 233, 1597, 28657, 514229, 433494437};
const char* filename[] = {"t0.txt", "t999.txt"};

// This testmain will test cases for each functions in lab3main.
int main(int argc, const char * argv[])
{
    if (strcmp(argv[argc-1], "FILE") == 0) {
        printToFile = true;
    }
    
    // It will compare files if filecount, target is 0. and filename is all NULL.
    // Nothing should happen.
    compareFilesPF();
    compareFilesAll();
    
    cout << endl;
    
    // Now tests with 1 text file. This will print the information testing t0.txt to
    // another t0.txt
    FILECOUNT = 1;
    NUMBER_OF_TARGETS = 1;
    compareFilesPF();
    compareFilesAll();
    
    // Tests the case where there is an invalid text input. File could not be open
    // message should be shown.
    FILECOUNT = 2;
    NUMBER_OF_TARGETS = 1;
    compareFilesPF();
    compareFilesAll();
    
    // Tests the case where the filecount, target is negative number. Nothing should
    // happen.
    FILECOUNT = -1;
    NUMBER_OF_TARGETS = -1;
    compareFilesPF();
    compareFilesAll();
    
    // Tests the case where getFileSize parameter is NULL. Nothing should happen.
    getFileSize(NULL);

    return 0;

    
    
}

void compareFilesPF() {
    fout.open ("results.txt");
    for (int k=0; k < NUMBER_OF_TARGETS; k++) {
        for (int i=0; i< FILECOUNT; i++) {
            compareList file1List;
            compareList file2List;
            ifstream infile1(filename[k]);
            ifstream infile2(filename[i]);
            long prospectSize = getFileSize(&infile2);
            
            // Case for file not found.
            if (!infile1 || !infile2)  {
                if (printToFile) {
                    fout << "File could not be opened. = " << filename[i] << endl;
                }
                else {
                    cout << "File could not be opened. = " << filename[i] << endl;
                }
                break;
            }
            
            char byteCheck1;
            char byteCheck2;
            byteCheck1 = infile1.get();
            byteCheck2 = infile2.get();
            // Checks for any tab/enter/blanks in front of the text file. Skips them.
            while (byteCheck1 == blank || byteCheck1 == tab || byteCheck1 == enter){
                byteCheck1 = infile1.get();
            }
            while (byteCheck2 == blank || byteCheck2 == tab || byteCheck2 == enter){
                byteCheck2 = infile2.get();
            }
            int count = 0;
            for (int pfIndex=0; pfIndex< primeFibonacciArr[9]; pfIndex++) {
                if (infile1.eof() || infile2.eof()) {
                    break;
                }
                
                // Inserts the byte index in the primeFibonacci array
                if (pfIndex == primeFibonacciArr[count]){
                    file1List.insert(byteCheck1);
                    file2List.insert(byteCheck2);
                    count ++;
                }
                byteCheck1 = infile1.get();
                byteCheck2 = infile2.get();
                
                
            }
            // Prints to console or file depending on the command line.
            if (printToFile) {
                
                fout << "Prospect File Name: " << filename[i] << endl;
                fout << "Prospect File Size: " << prospectSize << " bytes" << endl;
                fout << "Prospect File Char: \n" << file2List << endl;
                
                
                if (file1List == file2List) {
                    fout << file1List << endl << "Target File Char ^ \n" ;
                    fout << "100% file match!" << endl << endl;
                }
                else {
                    fout << file1List << endl << "Target File Char ^ \n" ;
                    fout << ((percentMatch *1.0 / count) * 100) << "% file match!" << endl << endl;
                }
            }
            else {
                cout << "Prospect File Name: " << filename[i] << endl;
                cout << "Prospect File Size: " << prospectSize << " bytes" << endl;
                cout << "Prospect File Char: \n" << file2List << endl;
                
                
                if (file1List == file2List) {
                    cout  << file1List << endl << "Target File Char ^ \n" ;
                    cout << "100% file match!" << endl << endl;
                }
                else {
                    cout  << file1List << endl << "Target File Char ^ \n" ;
                    cout << ((percentMatch *1.0 / count) * 100) << "% file match!" << endl << endl;
                }
            }
            // Closes the files at the end.
            infile1.close();
            infile2.close();
            
        }
    }
}


void compareFilesAll() {
    fout.open ("results.txt");
    for (int targetIndex=0; targetIndex < NUMBER_OF_TARGETS; targetIndex++) {
        ifstream targetFile(filename[targetIndex]);
        long targetSize = getFileSize(&targetFile);
        if(printToFile) {
            fout << "Target File Name: " << filename[targetIndex] << endl;
            fout << "Target File Size: " << targetSize << " bytes" << endl << endl;
        }
        else {
            cout << "Target File Name: " << filename[targetIndex] << endl;
            cout << "Target File Size: " << targetSize << " bytes" << endl << endl;
        }
        
        for (int prospectIndex=0; prospectIndex< FILECOUNT; prospectIndex++) {
            ifstream infile1(filename[targetIndex]);
            ifstream infile2(filename[prospectIndex]);
            long prospectSize = getFileSize(&infile2);
            
            bool foundDiff = false;
            if (!infile1 || !infile2)  {
                if (printToFile) {
                    fout << "File could not be opened. = " << filename[prospectIndex] << endl;
                }
                else {
                    cout << "File could not be opened. = " << filename[prospectIndex] << endl;
                }
                break;
            }
            char targetChar;
            char prospectChar;
            while(!infile1.eof() && !infile2.eof() && !foundDiff){
                
                targetChar = infile1.get();
                prospectChar = infile2.get();
                if (targetChar != prospectChar) {
                    foundDiff = true;
                }
            }
            if (printToFile ) {
                fout << "Prospect File Name: " << filename[prospectIndex] << endl;
                fout << "Prospect File Size: " << prospectSize << " bytes" << endl;
                if (!foundDiff) {
                    fout << "100% file match!" << endl << endl;
                }
                else {
                    fout << "File did not match!" << endl << endl;
                }
            }
            else {
                cout << "Prospect File Name: " << filename[prospectIndex] << endl;
                cout << "Prospect File Size: " << prospectSize << " bytes" << endl;
                if (!foundDiff) {
                    cout << "100% file match!" << endl << endl;
                }
                else {
                    cout << "File did not match!" << endl << endl;
                }
            }
        }
    }
}

long getFileSize(ifstream* infile) {
    if (infile == NULL) {
        return -1;
    }
    streampos begin,end;
    begin = infile->tellg();
    infile->seekg (0, ios::end);
    end = infile->tellg();
    infile->seekg (0, ios::beg);
    return (end-begin);
}
