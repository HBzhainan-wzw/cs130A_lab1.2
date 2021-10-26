#include <iostream>
#include "dictionary.h"

using namespace std;


int main(int argc, char* argv[]){
    string pFileName = argv[1];
    string dFileName = argv[2];
    string qFileName = argv[3];

    Dictionary d(dFileName,pFileName);

    ifstream queryFile(qFileName.c_str());
    string line;
    cout<<"Queries:"<<endl;
    while(getline(queryFile,line)){
        d.find(line.c_str());
    }
}
