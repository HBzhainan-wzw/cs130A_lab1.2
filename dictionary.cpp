#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "dictionary.h"

using namespace std;


//constructor
dictionary :: dictionary(string fname, string paramFileName){

    // initialize:
    this->fname = fname;
    this->paramFileName = paramFileName;
    // load parameter
    loadParam(paramFileName);
    // initialize primary hash24
    primaryHash24 = new Hash24(unsigned long rand_a, unsigned long rand_b, unsigned long rand_c);
    // initialize primary hashtable size
    string primaryHashScale[primaryHashTableSize];
    // scales primary hashtable
    primaryScaling(primaryHash24);
    // constructing primary hashtable
    // constructing secondary hashtables into primary table
    build();
    // insert words into secondary hashtables
    insertSecondary(primaryHash24);



}

// load parameters
void dictionary :: loadParam(string paramFileName){
    ifstream paramFile(pFileName.c_str()); // open file
    string line; // temp string
    //readfiles
    getline(paramFile,line);
    primaryHashTableSize = atoi(line.c_str());
    getline(paramFile,line);
    random_a = stoul(line.c_str());
    getline(paramFile,line);
    random_b = stoul(line.c_str());
    getline(paramFile,line);
    random_c = stoul(line.c_str());    
    paramFile.close(); // close file
}

// scaling in for primaryHashing table 
int dictionary :: primaryScaling(){
    // read data file
    stirng line; // temp string
    ifstream dataFile(fname.c_str());
    int hashKey; // temp int
    while(getline(fname,line)){
        hashKey = primaryHash24->hash(line.c_str());
        primaryHashScale[hashKey]++; //increment primary hashtable scale
        inputWordsCnt++; // increment inputWordsCnt
    }
    fname.close();
    return 0;
}


int dictionary :: build(){
    for(int i =0; i < primaryHashTableSize; i++){
        int tempSize = primaryHashScale[i]; //temp size
        if(tempSize == 0){
            vector<string> temp; //empty vector
        }else{
            vector<string> temp (tempSize * tempSize, ""); // sized empty vector
        }
        primaryHashTable.push_back(temp);
    }
    return 0;
}

int dictionary :: insertSecondary(){
    bool collisionFlag = true;
    while(collisionFlag){
        //reset flag
        collisionFlag = false;
        // create a hash24
        secondaryHash24 = new Hash24;
        //open file
        ifstream dataFile(fname.c_str());
        string line; // temp string
        int hashKey1; //temp int
        int hashKey2;
        while(getline(dataFile,line)){
            hashKey1 = primaryHash24->hash(line.c_str());
            hashKey2 = secondaryHash24->hash(line.c_str());
            if(primaryHashTable[hashKey1][hashKey2] == ""){
                primaryHashTable[hashKey1][hashKey2] = line.c_str();
            }else{
                collisionFlag = true;
                break;
            }
        }
    }
}