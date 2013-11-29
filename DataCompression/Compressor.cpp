//  Daniel Walsh
//  Final Exam
//
//  Compressor.cpp
//  DataCompression
//
//  Created by Daniel Walsh on 11/28/13.
//  Copyright (c) 2013 Daniel Walsh. All rights reserved.
//

#include "Compressor.h"
template <size_t S>
Compressor<S>::Compressor():
    _key({"zzz"}), _keysize(_key.size()), _kitor(_key.begin())
{
#ifdef _DEBUG
    cout << "default const\n";
#endif
}

template <size_t S>
Compressor<S>::Compressor(string path) :
    _key({"zzz"}), _keysize(_key.size()), _kitor(_key.begin())
{
#ifdef _DEBUG
    cout << "param const\n";
#endif
    setKey(path);
}

template <size_t S>
Compressor<S>::Compressor(const Compressor &rhs)
{
#ifdef _DEBUG
    cout << "copy const\n";
#endif
    for (_kitor = rhs._key.begin(); _kitor != rhs._key.end(); ++_kitor)
        _key.insert(*_kitor);
    
    _kitor = _key.begin();
    _keysize = rhs._size;
}

template <size_t S>
Compressor<S>::~Compressor()
{
#ifdef _DEBUG
    cout << "destructor\n";
#endif
}

template <size_t S>
void Compressor<S>::setKey(string source)
{    
    fstream in(source);
    
    if (in.fail()) {
        cerr << "failed to open " << source << '\n';
        exit(1);
    }
    
    while (!in.eof()) {
        string word;
        in >> word;
        _key.insert(word);
    }
    
    in.close();
    
    _kitor = _key.begin();
    _keysize = _key.size();
}

template <size_t S>
bitset<S> Compressor<S>::getBits(string w)
{    
    set<string>::iterator it = _key.find(w);
    long dist = distance(_key.begin(), it);
    
    if (dist == _keysize)
        return dist;
    else
        return ++dist;
}

template <size_t S>
void Compressor<S>::compress(string source, string target)
{    
    ifstream in(source);
    if (in.fail()) {
        cerr << "failed to open " << source << '\n';
        exit(1);
    }
    
    ofstream out(target);
    if (out.fail()) {
        cerr << "failed to open " << target << '\n';
        exit(1);
    }
    
    while (!in.eof()) {
        string word;
        in >> word;
        out << getBits(word) << '\n';
    }
    in.close();
    out.close();
}

template <size_t S>
void Compressor<S>::inflate(string source)
{    
    ifstream in(source);
    
    if (in.fail()) {
        cerr << "failed to open " << source << '\n';
        exit(1);
    }
    
    while (!in.eof()) {
        bitset<S> word;
        in >> word;
        _kitor = _key.begin();
        for (int i = 1; i < word.to_ulong(); ++i)
            ++_kitor;
        cout << *_kitor << " ";
    }
}

template <size_t S>
string Compressor<S>::inflate(bitset<S> *it)
{
    _kitor = _key.begin();
    for (int i = 1; i < it->to_ulong(); ++i)
        ++_kitor;
    
    return *_kitor;
}