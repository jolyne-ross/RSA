#include <iostream>
#include "RSA.h"

int main() {
    bool genNew = false;
    string res;
    cout<<"Generate new keys? [y/N] ";
    getline(cin, res);
    if(res == "y" || res=="Y")
        genNew = true;
    cout<<"Key Source: "<<((genNew)? "Generation" : "Read From Files in ./")<<"\n\n";

    keySet set;
    (genNew) ? RSA::buildKey("./", &set, 1024) : RSA::getKey("./", &set);

    cout<<"Input a plaintext ('exit' to exit): ";
    string plain;
    while(getline(cin, plain)) {
        if(plain == "exit") break;

        cout<<"\nplaintext:  "<<plain<<"\n";

        string cipher = RSA::Encrypt(set.PU, plain);
        cout<<"ciphertext: "<<cipher<<"\n";
        cout<<"ciphertext: ";
        for (unsigned char c : cipher)
            cout <<"0x"<< hex << setw(2) << setfill('0') << (int)c<<" ";
        cout << dec << '\n';

        plain = RSA::Decrypt(set.PR, cipher);
        cout<<"plaintext:  "<<plain<<"\n";

        cout<<"\nInput a plaintext: ";
    }

    mpz_clears(set.PR.k, set.PR.n, set.PU.k, set.PU.n); // getting rid of keySet set.

    return 0;
}
