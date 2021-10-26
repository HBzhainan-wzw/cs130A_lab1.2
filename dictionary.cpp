#include "dictionary.h"



using namespace std;


//constructor
Dictionary::Dictionary(string fname, string paramFileName){

    // initialize:
    this->fname = fname;
    this->paramFileName = paramFileName;
    // load parameter
    loadParam(paramFileName);
    // initialize primary hash24
    primaryHash24 = new Hash24(random_a, random_b, random_c);
    // initialize primary hashtable size
    int primaryHashScale[primaryHashTableSize];
    // scales primary hashtable
    primaryScaling();
    // constructing primary hashtable
    // constructing secondary hashtables into primary table
    build();
    // give 1 part of output
    printResult();
    // insert words into secondary hashtables
    insertSecondary();
    //give outputs
    

}

// load parameters
void Dictionary :: loadParam(string paramFileName){
    ifstream paramFile(paramFileName.c_str()); // open file
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
int Dictionary :: primaryScaling(){
    // read data file
    string line; // temp string
    ifstream dataFile(fname.c_str());
    int hashKey; // temp int
    while(getline(dataFile,line)){
        hashKey = primaryHash24->hash(line.c_str());
        primaryHashScale[hashKey]++; //increment primary hashtable scale
        inputWordsCnt++; // increment inputWordsCnt
    }
    dataFile.close();
    return 0;
}


int Dictionary :: build(){
    
    for(int i =0; i < primaryHashTableSize; i++){
        int tempSize = primaryHashScale[i]; //temp size
        // cnt for max collision
        if(tempSize > MaxCollision){
            MaxCollision = tempSize;
            maxCollisionIndex = i;
        }
        // cnt for primary slots
        primarySlots[tempSize]++;
        // building secondary hashtables
        vector<string> temp;
        if(tempSize != 0){
            vector<string> temp (tempSize * tempSize, "");// sized empty vector
        }
        primaryHashTable.push_back(temp);
    }
    return 0;
}

int Dictionary :: insertSecondary(){
    // load all words with 1st hash without 2nd hash
    // open file
    ifstream dataFile(fname.c_str());
    string line; // temp string
    int hashKey1; //temp int
    while(getline(dataFile,line)){
        hashKey1 = primaryHash24->hash(line.c_str());
        primaryHashTable[hashKey1].push_back(line.c_str());
        if(hashKey1 == maxCollisionIndex){
            maxCollideVec.push_back(line.c_str());
        }
    }

    // get a temp vector of the primary table size to record number of collisions happened in each slot
    vector<int> tempTrial (primaryHashTableSize, 1);

    // organizing words over again
    for(int i = 0; i < primaryHashTableSize; i++){

        // give each slot a hash function
        Hash24* h = new Hash24();
        secondaryHash24.push_back(h);
        // skip empty slots and slots with 1 word -- already in right position
        int currScale = primaryHashScale[i]; // temp int for current number of words in the slot
        if(currScale <= 1){
            continue;
        }else{

            // start inserting
            vector<string> tempVector (currScale * currScale, ""); // creating a empty vector of the same size
            bool collisionFlag = true; // Flag suggest collision
            while(collisionFlag){
                collisionFlag = false;
                for(int j = 0; j < currScale; j++){
                    int index = secondaryHash24[i]->hash(primaryHashTable[i][j]); 
                    if(tempVector[index] == ""){
                        tempVector[index] = primaryHashTable[i][j];
                    }else{
                        collisionFlag == true;
                        tempTrial[i]++; // cnt for collisions
                        //release previous hash24
                        delete secondaryHash24[i];
                        //assign a new hash24
                        Hash24* h = new Hash24();
                        secondaryHash24[i] = h;
                        break;
                    } 
                }
                // if all finished, copy tempVector to primary hashtable
                primaryHashTable[i] = tempVector;
            }
        }
    }
    // run over figures
    for(int i = 0; i < primaryHashTableSize; i++){
        if(tempTrial[i] <= 20){
            secondaryTrial[tempTrial[i]]++;
        }
    }
}

bool Dictionary::find(string word){
    int index1 = primaryHash24->hash(word.c_str());
    int index2 = secondaryHash24[index1]->hash(word.c_str());
    if(primaryHashTable[index1].size() > index2){
        if(primaryHashTable[index1][index2] == word){
            cout<<word<<" found at "<< index1 <<endl;
            return true;
        }
    }
    cout<<word<<" not found"<<endl;
    return false;
}
void Dictionary::printResult(){
    primaryHash24->dump();
    cout<<"Number of words = "<<inputWordsCnt<<endl;
    cout<<"Table size = "<<primaryHashTableSize<<endl;
    cout<<"Max collisions = "<< MaxCollision<<endl;
    for(int i = 0; i < 21; i++){
        cout<<"# of primary slots with "<< i <<" words = "<< primaryHashScale[i]<<endl;
    }
    cout<<"** Words in the slot with most collisions ***"<<endl;
    for(int i = 0; i < MaxCollision; i++){
        cout<<maxCollideVec[i]<<endl;
    }
    cout<<"Number of hash functions tried:"<<endl;
    int sum = 0; 
    int div = 0;
    for(int i = 0; i < 21; i++){
        cout<<"# of secondary hash tables trying "<< i <<" hash functions = "<< secondaryTrial[i] <<endl;
        sum = sum + i * secondaryTrial[i];
        div = div + secondaryTrial[i];
    }
    double avg = (double)sum / (double)div;
    cout<<"Average # of hash functions tried = "<<avg<<endl;

}

