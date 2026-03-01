#include <iostream>
#include <cassert>
#include "../RSA.h"
using namespace std;

void testGMPreadWrite() {
    keySet testKey;
    testKey.path = filesystem::path("test_keys.txt");

    testKey.PU.k = mpz_class(12345); testKey.PR.k = mpz_class(67890); 
    testKey.PU.n = mpz_class(99999); testKey.PR.n = testKey.PU.n;
    
    RSA::_writeKey(testKey);

    keySet readKey = RSA::getKey(testKey.path);

    assert(readKey.PU.k == testKey.PU.k); assert(readKey.PR.k == testKey.PR.k); 
    assert(readKey.PU.n == testKey.PU.n); assert(readKey.PR.n == testKey.PR.n); 

    cout << "all tests passed" << "\n";
}

int main() {
    testGMPreadWrite();
    return 0;
}
