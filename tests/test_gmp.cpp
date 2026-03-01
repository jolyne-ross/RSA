#include <iostream>
#include <gmp.h>

int main() {
    mpz_t x;
    mpz_init(x);
    mpz_set_ui(x, 123456789);
    // Print the value of 'x'
    gmp_printf("x = %Zd\n", x);
    mpz_clear(x);
    return 0;
}