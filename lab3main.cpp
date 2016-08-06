/**
 @file lab3main.cpp
 This is the lab3main source file that contains the functions to compare two files
 in fibonacciPrime sequenced byte numbers or all consecutive byte numbers. Has the
 commandline options to print results to a results.txt file or console. Also contains
 timer clock() to indicate the time processed for each instance of compare. Info.
 that are printed for each file compare are target/prospect file name, file size,
 percent match for the primeFibonacci compare. The primeFibonacci compare will also
 print the characters being compared, which characters matched, and the byte number.
 Any tab, enter, or blank space before the first character in any file will be ignored.
 
 @author Sean Lai
 @author Sai Badey
 @section ASSIGNEMT Lab3
 @section DUE_DATE 9 Feb 2014
 */

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
// Prototypes for functions
void compareFilesPF();
void compareFilesAll();
long getFileSize(ifstream* infile);

// List of constants, file count and number of target must match the number of files
// compared. The targets that we are using are s0.txt and t0.txt.
const int FILECOUNT = 35;
const int NUMBER_OF_TARGETS = 2;
const int primeFibonacciArr[] = {2, 3, 5, 13, 89, 233, 1597, 28657, 514229, 433494437};
const char* filename[] = {"t0.txt",  "s0.txt", "c1.txt", "c2.txt", "c3.txt", "c4.txt", "c5.txt", "c6.txt", "c7.txt", "c8.txt", "h1.txt", "h2.txt", "license.txt", "s1.txt", "s2.txt", "s3.txt", "s4.txt", "s5.txt", "s6.txt", "s7.txt", "s8.txt", "s9.txt", "s10.txt", "s11.txt", "s12.txt", "s13.txt", "s154.txt",  "t1.txt", "t2.txt", "t3.txt", "t4.txt", "t5.txt", "t6.txt", "t7.txt", "t8.txt"};

// Main function
int main(int argc, const char * argv[])
{
    system("pwd");
    // Command line function, if FILE input is found, all the printout will be
    // stored in results.txt that will be created.
    if (strcmp(argv[argc-1], "FILE") == 0) {
        printToFile = true;
    }
    clock_t clockTimeStart, clockTimeEnd, ticks;
    
    // Runs the compareFilesPF for all the 35 files, 2 targets. Calculates
    // the time it took using the clock().
    clockTimeStart = clock();
    compareFilesPF();
    clockTimeEnd = clock();
    
    ticks = clockTimeEnd - clockTimeStart;
    if (printToFile ) {
        fout << "compareFilesPF takes " << ticks << " clock ticks ~= "
        << (float)ticks / (float)CLOCKS_PER_SEC << " seconds\n";
    }
    else {
        cout << "compareFilesPF takes " << ticks << " clock ticks ~= "
        << (float)ticks / (float)CLOCKS_PER_SEC << " seconds\n";
    }
    
    // Runs the compareFilesAll for all the 35 files, 2 targets. Calculates
    // the time it took using the clock().
    clockTimeStart = clock();
    compareFilesAll();
    clockTimeEnd = clock();
    
    ticks = clockTimeEnd - clockTimeStart;
    if (printToFile ) {
        fout << "compareFilesAll takes " << ticks << " clock ticks ~= "
        << (float)ticks / (float)CLOCKS_PER_SEC << " seconds\n";
    }
    else {
        cout << "compareFilesAll takes " << ticks << " clock ticks ~= "
        << (float)ticks / (float)CLOCKS_PER_SEC << " seconds\n";
    }

    return 0;
}

/**
 Compares all the target text file with all the prospect text files using
 primeFibonacci byte numbers.
 File must exist to be opened. If commandline FILE was in the input, all the console
 output will be printed inside results.txt instead. The function will clear any
 tab, enter, or blanks before it reaches the first valid character.
 References the insert(char target) when inserting each primeFibonacci sequenced
 byte numbers. Information will be printed out at the end.

 @return void
 */
void compareFilesPF() {
    // Opens for results.txt for printing to file.
    fout.open ("results.txt");
    for (int k=0; k < NUMBER_OF_TARGETS; k++) {
        for (int i=0; i< FILECOUNT; i++) {
            compareList file1List;
            compareList file2List;
            ifstream infile1(filename[k]);
            ifstream infile2(filename[i]);
            long prospectSize = getFileSize(&infile2);
            
            // Case for file not found.
            if (!infile1 || !infile2)
            {
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
            // t5.txt, s2.txt, s4.txt has UTF-16 encoded characters.
            while (byteCheck1 == blank || byteCheck1 == tab || byteCheck1 == enter){
                byteCheck1 = infile1.get();
            } // t5.txt, s2.txt, s4.txt
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

/**
 Compares all the target text file with all the prospect text files using
 all consecutive byte numbers. 
 File must exist to be opened. If commandline FILE was in the input, all the console 
 output will be printed inside results.txt instead. The function will clear any 
 tab, enter, or blanks before it reaches the first valid character. 
 It will check every byte consecutively with the get() command, and breaks when it
 reached byte compare that shows difference.
 Information will be printed out at the end.
 
 @return void
 */
void compareFilesAll() {
    // Opens the results.txt for printing to file.
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
                // Checks all the bytes. Triggers foundDiff if difference was found.
                targetChar = infile1.get();
                prospectChar = infile2.get();
                if (targetChar != prospectChar) {
                    foundDiff = true;
                }
            }
            // Information prints below.
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

/**
 Returns the byte size of the infile data. It will calculate the byte using 
 the seekg, from beginning to end, and finds the total bytes in the file.
 
 @param[*infile] The file that this function will size check.
 @return (end-begin), the size for the file in bytes
 */
long getFileSize(ifstream* infile) {
    if (infile == NULL) {
        return -1;
    }
        streampos begin,end;
        begin = infile->tellg();
        infile->seekg (0, ios::end);
        // Calculates the bytes from beginning to end.
        end = infile->tellg();
        infile->seekg (0, ios::beg);
        return (end-begin);
    }

