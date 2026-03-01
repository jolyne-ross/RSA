#include "RSA.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

// File system Functions
keySet RSA::getKey(filesystem::path keyPath) {
    keySet k;
    k.path = keyPath;

    ifstream in(keyPath / "public.txt");
    if (!in)
        throw invalid_argument("Cannot open Public File");
    
    in >> k.PU.k >> k.PU.n;

    if (in.fail())
        throw invalid_argument("Key file format Invalid");

    in.close();

    in = ifstream(keyPath / "private.txt");
    if (!in)
        throw invalid_argument("Cannot open Private File");
    
    in >> k.PR.k >> k.PR.n;

    if (in.fail())
        throw invalid_argument("Key file format Invalid");
    
    in.close();
    return k;
}

void RSA::_writeKey(const keySet& key) {
    ofstream out(key.path / "public.txt");
    if (!out) 
        throw invalid_argument("Cannot open public file");
    
    out << key.PU.k << "\n" << key.PU.n << "\n";

    if(out.fail())
        throw runtime_error("Key file write failed");
    out.close();


    out = ofstream(key.path / "private.txt");
    if (!out) 
        throw invalid_argument("Cannot open private file");
    
    out << key.PR.k << "\n" << key.PR.n << "\n";

    if(out.fail())
        throw runtime_error("Key file write failed");
    out.close();
}

// Cryptographic Functions
