//
//  main.cpp
//  DataCompression
//
//  Created by Daniel Walsh on 11/17/13.
//  Copyright (c) 2013 Daniel Walsh. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <set>
#include <bitset>
#include <vector>

using namespace std;

bitset<17> findWord(string w, set<string> key) {
    set<string>::iterator it = key.find(w);
    long dist = distance(key.begin(), it);
    if (dist == key.size()) return dist;
    else return ++dist;
}

int main( )
{
    set<string> words;
    set<string>::iterator itor;
    fstream in;
    
    in.open("brit-a-z.txt");
    if (in.fail()) {
        cerr << "file open failed!";
        exit(1);
    }
    while (!in.eof()) {
        string word;
        in >> word;
        words.insert(word);
    }
    in.close();
    
    in.open("symbols.txt");
    if (in.fail()) {
        cerr << "file open failed!";
        exit(1);
    }
    while (!in.eof()) {
        string word;
        in >> word;
        words.insert(word);
    }
    in.close();
    
    for (auto& elem : words)
        cout << elem << '\n';
    
    itor = words.end();
    words.erase(--itor);
    cout << words.size() << '\n';
    
    vector<bitset<17>> comp;
    
    in.open("macbeth.txt");
    if (in.fail()) {
        cerr << "file open failed!";
        exit(1);
    }
    while (!in.eof()) {
        string word;
        in >> word;
        comp.push_back(findWord(word, words));
    }
    in.close();
    
    copy(comp.begin(), comp.end(), ostream_iterator<bitset<17>>(cout, "\n"));

    for (vector<bitset<17>>::iterator it = comp.begin(); it != comp.end(); ++it) {
        itor = words.begin();
        for (int i = 1; i < it->to_ulong(); ++i) {
            ++itor;
        }
        cout << *itor << " ";
    }
    cout << endl;
    
    return 0;
}

