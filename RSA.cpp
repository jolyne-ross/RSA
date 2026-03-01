#include "RSA.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

// File system Functions
/*
void RSA::getKey(filesystem::path keyPath, keySet* out) {
    out->path = keyPath;
    mpz_inits(out->PU.k, out->PU.n, out->PR.k, out->PR.n);

    ifstream in(keyPath / "public.txt");
    if (!in)
        throw invalid_argument("Cannot open Public File");
    string tmp1, tmp2;
    in >> tmp1 >> tmp2;
    mpz_set_str(out->PU.k, tmp1.c_str(), 10);
    mpz_set_str(out->PU.n, tmp2.c_str(), 10);

    if (in.fail())
        throw invalid_argument("Key file format Invalid");

    in.close();

    in = ifstream(keyPath / "private.txt");
    if (!in)
        throw invalid_argument("Cannot open Private File");
    
    tmp1 = ""; tmp2 = "";
    in >> tmp1 >> tmp2;
    mpz_set_str(out->PR.k, tmp1.c_str(), 10);
    mpz_set_str(out->PR.n, tmp2.c_str(), 10);

    if (in.fail())
        throw invalid_argument("Key file format Invalid");
    
    in.close();
}


void RSA::_writeKey(const keySet& set) {
    ofstream f(set.path / "public.txt");
    if (!f) 
        throw invalid_argument("Cannot open public file");
    
    f << mpz_get_str(0, 10, set.PU.k) << "\n" << mpz_get_str(0, 10, set.PU.n) << "\n";

    if(f.fail())
        throw runtime_error("Key file write failed");
    f.close();


    f = ofstream(set.path / "private.txt");
    if (!f) 
        throw invalid_argument("Cannot open private file");
    
    f << mpz_get_str(0, 10, set.PR.k) << "\n" << mpz_get_str(0, 10, set.PR.n) << "\n";

    if(f.fail())
        throw runtime_error("Key file write failed");
    f.close();
}
*/


// Cryptographic Functions
void RSA::buildKey(filesystem::path keyOutput, keySet* out, uint bits, uint eChoice) {
    // PRIME GENERATION
    bits = bits/2;
    mpz_t p,q;
    mpz_inits(p, q);

    gmp_randstate_t rand;
    gmp_randinit_default(rand);

    gmp_randseed_ui(rand, time(nullptr));

    do {
        mpz_rrandomb(p, rand, bits);
        mpz_nextprime(p, p);
    } while(mpz_probab_prime_p(p, 25) == 0); // reasonable number from docs is 15-50

    do {
        mpz_rrandomb(q, rand, bits);
        mpz_nextprime(q, q);
    } while (mpz_probab_prime_p(q, 25) == 0);

    // N AND TOTIENT CALCULATION
    mpz_t n, totient;
    mpz_inits(n, totient);

    mpz_mul(n, p, q); // n = p*q

    // totient calc
    mpz_sub_ui(p, p, 1); // p = p-1
    mpz_sub_ui(q, q, 1); // q = q-1
    mpz_mul(totient, p, q); // totient = (p-1)(q-1)
    
    // cleanup
    mpz_clears(p, q);
    gmp_randclear(rand);

    mpz_t e, d;
    mpz_inits(e, d);
    mpz_set_ui(e, eChoice); // reccomended e choice

    if(!mpz_invert(d, e, totient))
        throw invalid_argument("Choice of e is invalid, not coprime with generated phi(n); please choose something prime.");

    // KEY INIT AND SETTING
    out->path = keyOutput;
    mpz_inits(out->PU.k, out->PU.n, out->PR.k, out->PR.n);
    mpz_set(out->PU.k, e); mpz_set(out->PU.n, n); mpz_set(out->PR.k, d); mpz_set(out->PR.n, n);

    // clean up
    mpz_clears(e, d, totient, n);

    // WRITE TO FILE, no building functions??? so just writing here
    ofstream f(out->path / "public.txt");
    if (!f) 
        throw invalid_argument("Cannot open public file");
    
    f << mpz_get_str(0, 10, out->PU.k) << "\n" << mpz_get_str(0, 10, out->PU.n) << "\n";

    if(f.fail())
        throw runtime_error("Key file write failed");
    f.close();


    f = ofstream(out->path / "private.txt");
    if (!f) 
        throw invalid_argument("Cannot open private file");
    
    f << mpz_get_str(0, 10, out->PR.k) << "\n" << mpz_get_str(0, 10, out->PR.n) << "\n";

    if(f.fail())
        throw runtime_error("Key file write failed");
    f.close();
}
