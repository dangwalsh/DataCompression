//  Daniel Walsh
//  Final Exam
//
//  Compressor.h
//  DataCompression
//
//  Created by Daniel Walsh on 11/28/13.
//  Copyright (c) 2013 Daniel Walsh. All rights reserved.
//

#ifndef __DataCompression__Compressor__
#define __DataCompression__Compressor__

#include <iostream>
#include <fstream>
#include <set>
#include <bitset>
#include <vector>

using namespace std;

template <size_t S=10>
class Compressor {
    
private:
    set<string> _key;
    size_t _keysize;
    set<string>::iterator _kitor;
    /*
    vector<bitset<S> > _bits;
    size_t _bitsize;
    typename vector<bitset<S> >::iterator _bitor;
    */
    
public:
    // constructors
    Compressor();
    Compressor(string path);
    Compressor(const Compressor &rhs);
    
    // destructor
    ~Compressor();
    
    // accessors/mutators
    void setKey(string path);
    
    // member functions
    bitset<S> getBits(string w);
    void compress(string source, string target);
    void inflate(string source);
    string inflate(bitset<S> *it);
    /*
    void setBits(string w) {
        
        set<string>::iterator it = _key.find(w);
        long dist = distance(_key.begin(), it);
        
        if (dist == _keysize)
            _bits.push_back(dist);
        else
            _bits.push_back(++dist);
    }
    void compress(string path) {
        
        fstream in(path);
        
        if (in.fail()) {
            cerr << "file open failed!";
            exit(1);
        }
        
        while (!in.eof()) {
            string word;
            in >> word;
            setBits(word);
        }
    }
    void inflate() {

        for (_bitor = _bits.begin(); _bitor != _bits.end(); ++_bitor) {
            _kitor = _key.begin();
            for (int i = 1; i < _bitor->to_ulong(); ++i)
                ++_kitor;
            cout << *_kitor << " ";
        }
    }
    */
};

#endif /* defined(__DataCompression__Compressor__) */
