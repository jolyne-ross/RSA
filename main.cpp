#include <iostream>
#include "RSA.h"

int main() {
    RSA rsa("./", 1024, true);
    string plain = "Talia Jolyne Ross RSA Encryption Implementation for C4476.";
    std::cout<<"plaintext: "<<plain<<"\n";

    string cipher = rsa.Encrypt(plain);
    std::cout<<"ciphertext: "<<cipher<<"\n";

    plain  = rsa.Decrypt(cipher);
    std::cout<<"plaintext: "<<cipher<<"\n";

    return 0;
}
