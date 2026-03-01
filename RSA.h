// Basic header file (guessing atp)
#pragma once
#include <filesystem>
#include <string>
using namespace std;

struct key { int k; int n; };
struct keySet { key PU; key PR; };

class RSA {
public:
    RSA(filesystem::path keyPath, bool writeNew = false) {
        if (writeNew) keyPath = buildKey(keyPath);
        keySet keys = getKey(keyPath);
        privatekey = keys.PR;
        publickey = keys.PU;
    }

    string Encrypt (string plaintext) { Encrypt(publickey, plaintext); } // use the class member key (gotten from the constructors)
    static string Encrypt(key publicKey, string plaintext) {} // input your own

    string Decrypt (string ciphertext) { Decrypt(privatekey, ciphertext); } // use the class member key
    static string Decrypt(key privatekey, string ciphertext) {} // input your own

    static filesystem::path buildKey(filesystem::path keyOutput) {} // writes key to file
    static keySet getKey(filesystem::path keyPath) {}

private:
    key privatekey;
    key publickey;
};
