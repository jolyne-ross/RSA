// Basic header file (guessing atp)
#pragma once
#include <filesystem>
#include <string>
#include <gmpxx.h>
using namespace std;

struct key { mpz_class k; mpz_class n; };
struct keySet {filesystem::path path; key PU; key PR; };

class RSA {
public:
    RSA(filesystem::path keyPath, bool writeNew = false) {
        if (writeNew) keys = buildKey(keyPath);
        else keys = getKey(keyPath);
    }

    filesystem::path getKeyPath() const { return keys.path; }

    string Encrypt (string plaintext) const { Encrypt(keys.PU, plaintext); } // use the class member key (gotten from the constructors)
    static string Encrypt(const key& publicKey, const string& plaintext); // input your own

    string Decrypt (string ciphertext) const { Decrypt(keys.PR, ciphertext); } // use the class member key
    static string Decrypt(const key& privatekey, const string& ciphertext); // input your own

    static keySet buildKey(filesystem::path keyOutput); // writes key to file
    static keySet getKey(filesystem::path keyPath);

private:
    keySet keys;

    static void _writeKey(const keySet& key);
};
