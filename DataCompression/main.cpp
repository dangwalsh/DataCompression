//  Daniel Walsh
//  Final Exam
//
//  main.cpp
//  DataCompression
//
//  Created by Daniel Walsh on 11/17/13.
//  Copyright (c) 2013 Daniel Walsh. All rights reserved.
//
//#define _DEBUG
#define SIZE 10

#include <iostream>
#include <fstream>
#include <set>
#include <bitset>
#include <vector>
#include "Compressor.h"
#include "Compressor.cpp"

using namespace std;

int main()
{
    // version 1
    // writing and reading to an intenral array
    // less practical but fulfills the assignment

    size_t count = 0;
    string word = "";
    Compressor<SIZE> comp("declaration.txt");

    ifstream in("gettysburg.txt");
    if (in.fail()) {
        cerr << "file open failed!";
        exit(1);
    }
    while (!in.eof()) {
        in >> word;
        ++count;
    }
    in.close();
    
    bitset<SIZE> *bitarr = new bitset<SIZE>[count];
    in.open("gettysburg.txt");
    for (int i = 0; i < count; ++i) {
        in >> word;
        bitarr[i] = comp.getBits(word);
    }
    in.close();
    
    for (bitset<SIZE> *ptr = bitarr; ptr < bitarr + count; ++ptr)
        cout << comp.inflate(ptr) << " ";
    
    delete [] bitarr;
    bitarr = NULL;
    
    cout << "\n\n\n";
    
    // version 2
    // writing and reading to a file
    // more practical since data is stored outside of application
    
    Compressor<SIZE> compressor;
    compressor.setKey("declaration.txt");
    compressor.compress("gettysburg.txt", "gettysburg.comp");
    compressor.inflate("gettysburg.comp");
    
    return EXIT_SUCCESS;
}
