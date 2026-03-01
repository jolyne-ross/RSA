#include "RSA.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

// File system Functions
keySet RSA::getKey(filesystem::path keyPath) {
    keySet k;
    k.path = keyPath;

    ifstream in(keyPath);
    if (!in)
        throw invalid_argument("Cannot open Key File");
    
    in >> k.PU.k >> k.PR.k >> k.PU.n;
    k.PR.n = k.PU.n;

    if (in.fail())
        throw invalid_argument("Key file format Invalid");
    
    in.close();
    return k;
}

void RSA::_writeKey(const keySet& key) {
    ofstream out(key.path);
    if (!out) 
        throw invalid_argument("Cannot make key file");
    
    out << key.PU.k << "\n" << key.PR.k << "\n" << key.PU.n << "\n";
    if(out.fail())
        throw runtime_error("Key file write failed");
    out.close();
}

// Cryptographic Functions
