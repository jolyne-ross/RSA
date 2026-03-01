#include <iostream>
#include "RSA.h"

int main() {
    RSA rsa("./", 1024, true);
    string plain = "Talia Jolyne Ross RSA Encryption Implementation for C4476.";
    std::cout<<"plaintext:  "<<plain<<"\n";

    string cipher = rsa.Encrypt(plain);
    std::cout<<"ciphertext: "<<cipher<<"\n";
    std::cout<<"ciphertext: ";
    for (unsigned char c : cipher)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c;
     std::cout << std::dec << '\n';

    plain = rsa.Decrypt(cipher);
    std::cout<<"plaintext:  "<<plain<<"\n";

    return 0;
}
