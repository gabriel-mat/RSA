#include <stdio.h>
#include <gmp.h>

#define MAX_SIZE 4096

void quadrado_e_multiplicacao(mpz_t res, mpz_t msg, mpz_t exp, mpz_t mod);

int main(){
    int base;
    char modulo[MAX_SIZE + 1], expoente[MAX_SIZE + 1], mensagem[MAX_SIZE + 1];

    scanf("%d", &base);
    scanf(" %s", modulo);
    scanf(" %s", expoente);
    scanf(" %s", mensagem);

    mpz_t mod, exp, msg, res;
    mpz_init(mod);
    mpz_init(exp);
    mpz_init(msg);
    mpz_init(res);

    mpz_set_str(mod, modulo, base);
    mpz_set_str(exp, expoente, base);
    mpz_set_str(msg, mensagem, base);

    quadrado_e_multiplicacao(res, msg, exp, mod);

    printf("%d\n", base);
    mpz_out_str(stdout, base, res);
    printf("\n");

    mpz_clears(mod, exp, msg, res, NULL);
    return 0;
}

void quadrado_e_multiplicacao(mpz_t res, mpz_t msg, mpz_t exp, mpz_t mod){
    int num_bits = mpz_sizeinbase(exp, 2);

    if (!num_bits){
        mpz_set_ui(res, 1);
        return;
    }

    mpz_t y;
    mpz_init(y);

    // y = x (mod mod)
    mpz_mod(y, msg, mod);

    for (int i = num_bits - 2; i >= 0; --i) {
        // Square
        mpz_mul(y, y, y);
        mpz_mod(y, y, mod);

        // Multiply
        if (mpz_tstbit(exp, i)){ 
            mpz_mul(y, y, msg);
            mpz_mod(y, y, mod);
        }
    }

    mpz_set(res, y);
    mpz_clear(y);
}