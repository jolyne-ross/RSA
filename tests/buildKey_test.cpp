#include <iostream>
#include <cassert>
#include "../RSA.h"
using namespace std;

void testBuildKey() {
    keySet testKey;
    RSA::buildKey("testkeys", &testKey, 1024);
    mpz_clears(testKey.PU.k, testKey.PU.n, testKey.PR.k, testKey.PR.n, nullptr);
    
    cout<<"no crashes";
}

int main() {
    testBuildKey();
    return 0;
}
