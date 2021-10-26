#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include "hash24.h"

using namespace std;

// hash table class
class Dictionary {

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
    Hash24* primaryHash24;

    //figures
    int inputWordsCnt = 0;
    int MaxCollision = 0;
    int primarySlots[21];
    int maxCollisionIndex = 0;
    int secondaryTrial[21];
    vector<string> maxCollideVec;

    //storages
    vector<vector<string>> primaryHashTable;
    vector<Hash24*> secondaryHash24;
    int* primaryHashScale;

public:
    Dictionary(string fname, string paramFileName);
    void loadParam(string paramFileName);
    int primaryScaling();
    int build();
    int insertSecondary();
    void printResult();
    bool find(string word);

};

#endif

