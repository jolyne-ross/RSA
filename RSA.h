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
    RSA(filesystem::path keyPath, uint bits = 1024, bool writeNew = true) {
        if (writeNew) buildKey(keyPath, &keys, bits);
        else getKey(keyPath, &keys);
    }

    ~RSA() {
        mpz_clears(keys.PR.k, keys.PR.n, keys.PU.k, keys.PU.n); // getting rid of keySet
    }

    filesystem::path getKeyPath() const { return keys.path; }
    
    string Encrypt (const string& plaintext) const { return Encrypt(keys.PU, plaintext); } 
    static string Encrypt(const key& publicKey, const string& plaintext);

    string Decrypt (const string& ciphertext) const { return Decrypt(keys.PR, ciphertext); }
    static string Decrypt(const key& privatekey, const string& ciphertext);

    static void buildKey(filesystem::path keyOutput, keySet* out, uint bits, uint eChoice = 65537);
    static void getKey(filesystem::path keyPath, keySet* out);

private:
    keySet keys;
};
