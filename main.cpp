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

    RSA rsa("./", 1024, genNew);

    cout<<"Input a plaintext: ";
    string plain;
    while(getline(cin, plain)) {
        cout<<"\nplaintext:  "<<plain<<"\n";

        string cipher = rsa.Encrypt(plain);
        cout<<"ciphertext: "<<cipher<<"\n";
        cout<<"ciphertext: ";
        for (unsigned char c : cipher)
            cout << hex << setw(2) << setfill('0') << (int)c;
        cout << dec << '\n';

        plain = rsa.Decrypt(cipher);
        cout<<"plaintext:  "<<plain<<"\n";


        cout<<"\nInput a plaintext: ";
    }

    return 0;
}
