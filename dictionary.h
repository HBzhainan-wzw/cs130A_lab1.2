#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <string>
#include "hash24.h"

// hash table class
class dictionary {

private:
    //inputFileNames
    string fname;
    string paramFileName;

    // parameters
    int primaryHashTableSize;
    unsigned long random_a;
    unsigned long random_b;
    unsigned long random_c;

    // utilities 
    Hash24 primaryHash24;
    Hash24 secondaryHash24;

    //storages
    vector<vector<string>> primaryHashTable;
    int inputWordsCnt = 0;

public:
    dictionary();
    void loadParameter(string paramFileName);
    int primaryScaling();
    int build();
    int insertSecondary();
};

#endif

