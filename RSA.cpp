#include "RSA.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

// File system Functions
/*
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
*/

// Cryptographic Functions
void RSA::buildKey(filesystem::path keyOutput, keySet* out, uint bits, uint eChoice = 65537) {
    // PRIME GENERATION
    uint bits = bits/2;
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
    keySet set; set.path = keyOutput;
    mpz_inits(set.PU.k, set.PU.n, set.PR.k, set.PR.n);
    mpz_set(set.PU.k, e); mpz_set(set.PU.n, n); mpz_set(set.PR.k, d); mpz_set(set.PR.n, n);

    // clean up
    mpz_clears(e, d, totient, n);

    // WRITE TO FILE, no building functions??? so just writing here
}
