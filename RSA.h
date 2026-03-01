// Basic header file (guessing atp)
#pragma once
#include <filesystem>
#include <string>
#include <gmp.h>
using namespace std;

struct key { mpz_t k; mpz_t n; }; 
struct keySet { filesystem::path path; key PU; key PR; };

class RSA {
public:
    RSA(filesystem::path keyPath, uint bits = 1024, bool writeNew = false) {
        if (writeNew) buildKey(keyPath, keys, bits);
        else getKey(keyPath, keys);
    }

    filesystem::path getKeyPath() const { return keys->path; }

    string Encrypt (const string& plaintext) const { return Encrypt(keys->PU, plaintext); } // use the class member key (gotten from the constructors)
    static string Encrypt(const key& publicKey, const string& plaintext); // input your own

    string Decrypt (const string& ciphertext) const { return Decrypt(keys->PR, ciphertext); } // use the class member key
    static string Decrypt(const key& privatekey, const string& ciphertext); // input your own

    static void buildKey(filesystem::path keyOutput, keySet* out, uint bits, uint eChoice = 65537); // writes key to file
    static void getKey(filesystem::path keyPath, keySet* out);

private:
    keySet* keys;

    static void _writeKey(const keySet& key);
    
    friend void testGMPreadWrite();
};
