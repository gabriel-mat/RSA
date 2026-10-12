#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>
#include <unistd.h>

int eea(mpz_t gcd, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b);
int inverso_modular(mpz_t inv, const mpz_t a, const mpz_t m);

int main(int argc, char* argv[])
{
  // leitura de argumentos
  if (argc < 2) {
    fprintf(stderr, "Uso: %s <tamanho_da_chave_em_bits> [base]\n", argv[0]);
    return 1;
  }

  int bits = atoi(argv[1]);
  if (bits != 512 && bits != 1024 && bits != 2048) {
        fprintf(stderr, "Tamanho de chave invalido. Use 512, 1024 ou 2048.\n");
        return 1;
  }
  int base = 10; // Padrão para decimal
  if (argc >= 3) {
      base = atoi(argv[2]);
      if (base != 10 && base != 16) {
          fprintf(stderr, "Base invalida. Use 10 ou 16.\n");
          return 1;
      }
    }

  mpz_t p, q, n, phi, e, d, gcd_val, tmp;
  mpz_inits(p, q, n, phi, e, d, gcd_val, tmp, NULL);

  // rng
  gmp_randstate_t state;
  gmp_randinit_default(state);
  gmp_randseed_ui(state, time(NULL));

  int prime_bits = bits / 2;

  // gerar primos, n, phi. repete enquanto gcd(e, phi) != 1
  do {
    // gerar p
    mpz_urandomb(p, state, prime_bits);

    // garante que o numero gerado será um de tamanho igual a prime_bits
    mpz_setbit(p, prime_bits-1);

    mpz_nextprime(p, p);

    // gerar q (distinto de p)
    do {
      mpz_urandomb(q, state, prime_bits);

      // mesma garantia de p para q (prime_bits)
      mpz_setbit(q, prime_bits-1);
      
      mpz_nextprime(q, q);
    } while (mpz_cmp(p, q) == 0);

    // calculo de n e phi(n)
    mpz_mul(n, p, q);
    
    mpz_sub_ui(tmp, p, 1);
    mpz_sub_ui(phi, q, 1);
    mpz_mul(phi, phi, tmp);

    // definicao de "e" e verificacao de coprimalidade
    mpz_set_ui(e, 65537);
    mpz_gcd(gcd_val, e, phi);
  } while (mpz_cmp_ui(gcd_val, 1) != 0); // repetir se gcd(e, phi) != 1

  if (!inverso_modular(d, e, phi)) {
    fprintf(stderr, "erro, nao ha inverso modular (d e e nao sao coprimos)\n");
    mpz_clears(p, q, n, phi, e, d, gcd_val, tmp, NULL);
    gmp_randclear(state);
    return 1;
  }


  // imprime: base, n, e, d, p, q : um por linha
  const char *fmt = (base == 16) ? "%Zx\n" : "%Zd\n";
  printf("%d\n", base);
  gmp_printf(fmt, n);
  gmp_printf(fmt, e);
  gmp_printf(fmt, d);
  gmp_printf(fmt, p);
  gmp_printf(fmt, q);

  // libera a memoria alocada pela lib gmp
  mpz_clears(p, q, n, phi, e, d, gcd_val, tmp, NULL);
  gmp_randclear(state);
  return 0;
 
}

/*
 * Algoritmo de Euclides Estendido para mpz_t.
 * Calcula gcd = mdc(a,b) e coeficientes x,y tais que:
 *     a*x + b*y = gcd
 * Retorna 1 se gcd == 1, 0 caso contrário.
 */
int eea(mpz_t gcd, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b)
{
    mpz_t old_r, r, old_s, s, old_t, t, q, tmp;
    mpz_inits(old_r, r, old_s, s, old_t, t, q, tmp, NULL);

    mpz_set(old_r, a);
    mpz_set(r, b);
    mpz_set_ui(old_s, 1);
    mpz_set_ui(s, 0);
    mpz_set_ui(old_t, 0);
    mpz_set_ui(t, 1);

    while (mpz_sgn(r) != 0) {
        mpz_fdiv_q(q, old_r, r);

        mpz_mul(tmp, q, r);
        mpz_sub(tmp, old_r, tmp);
        mpz_set(old_r, r);
        mpz_set(r, tmp);

        mpz_mul(tmp, q, s);
        mpz_sub(tmp, old_s, tmp);
        mpz_set(old_s, s);
        mpz_set(s, tmp);

        mpz_mul(tmp, q, t);
        mpz_sub(tmp, old_t, tmp);
        mpz_set(old_t, t);
        mpz_set(t, tmp);
    }

    mpz_set(gcd, old_r);
    mpz_set(x, old_s);
    mpz_set(y, old_t);

    int ok = (mpz_cmp_ui(gcd, 1) == 0) ? 1 : 0;

    mpz_clears(old_r, r, old_s, s, old_t, t, q, tmp, NULL);
    return ok;
}

/*
 * Inverso modular: inv = a^(-1) mod m.
 * Retorna 1 em sucesso, 0 se gcd(a,m) != 1.
 */
int inverso_modular(mpz_t inv, const mpz_t a, const mpz_t m)
{
    mpz_t gcd, x, y;
    mpz_inits(gcd, x, y, NULL);

    int ok = eea(gcd, x, y, a, m);
    if (ok)
        mpz_mod(inv, x, m);

    mpz_clears(gcd, x, y, NULL);
    return ok;
}
