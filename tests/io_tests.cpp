#include <iostream>
#include <cassert>
#include "../RSA.h"
using namespace std;

void testGMPreadWrite() {
    keySet testKey;
    testKey.path = filesystem::path(".");

    mpz_init_set_ui(testKey.PU.k, 12345); mpz_init_set_ui(testKey.PU.n, 99999); 
    mpz_init_set_ui(testKey.PR.k, 67890); mpz_init_set(testKey.PR.n, testKey.PU.n); 
    
    RSA::_writeKey(testKey);

    keySet readKey;
    RSA::getKey(testKey.path, &readKey);

    try {
    assert(mpz_cmp(readKey.PU.k, testKey.PU.k) == 0); assert(mpz_cmp(readKey.PR.k, testKey.PR.k) == 0);
    assert(mpz_cmp(readKey.PU.n, testKey.PU.n) == 0); assert(mpz_cmp(readKey.PR.n, testKey.PR.n) == 0);
    } catch(const exception& e) {
        mpz_clears(readKey.PU.k, readKey.PU.n, readKey.PR.k, readKey.PR.n);
        mpz_clears(testKey.PU.k, testKey.PU.n, testKey.PR.k, testKey.PR.n);
        throw e;
    }

    mpz_clears(readKey.PU.k, readKey.PU.n, readKey.PR.k, readKey.PR.n);
    mpz_clears(testKey.PU.k, testKey.PU.n, testKey.PR.k, testKey.PR.n);

    cout << "all tests passed" << "\n";
}

int main() {
    testGMPreadWrite();
    return 0;
}
