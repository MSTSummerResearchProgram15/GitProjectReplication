#include <stdlib.h>             /* Standard Lib    ISOC  */
#include <stdio.h>              /* I/O lib         ISOC  */
#include <stdarg.h>             /* Variable args   ISOC  */
#include <gmp.h>                /* GNU GMP Library       */

int main()
{
  int             i;            /* Loop variable */
  mpz_t           randNum;      /* Hold our random numbers */
  int             rndBit;       /* Bound for mpz_urandomb */
  mpz_t           rndBnd, key;       /* Bound for mpz_urandomm */
  gmp_randstate_t gmpRandState; /* Random generator state object */

  /* Initialize randNum before we use it. */
  mpz_init(randNum);
  mpz_init(key);
  /* Initialize Bounds */
  rndBit = 1024;
  mpz_init_set_str(rndBnd, "4000", 10);

  /* Initialize the random state with default algorithm... */
  gmp_randinit_default(gmpRandState);

  /* Seed the state with an unsigned long int before we begin.. */
  /* One can set the seed from an mpz_t too with gmp_randseed() */
  mpz_set_str(key, "1234567891", 10);
  //gmp_randseed_ui(gmpRandState, 1234567891);
  gmp_randseed(gmpRandState, key);
  printf("10 random numbers in U[0, -1+2**%d]:\n\n", rndBit);
 /* for(i=0; i<10; i++) {
    /* mpz_get_ui() can convert randNum to unsigned long int... */
   /* mpz_urandomb(randNum, gmpRandState, rndBit);
    //mpz_out_str(stdout, 10, randNum);
    printf("\n");
  }  /* end for */

  printf("10 random numbers in U[0, ");
  mpz_out_str(stdout, 10, rndBnd);
  printf("]:\n");
  for(i=0; i<10; i++) {
    /* mpz_get_ui() can convert randNum to unsigned long int... */
    mpz_urandomm(randNum, gmpRandState, rndBnd);
    mpz_out_str(stdout, 10, randNum);
    printf("\n");
  } /* end for */

  /* Clean up resources occupied by compensated */
  gmp_randclear(gmpRandState);

  /* Clean up resources occupied by our mpz_t variables */
  mpz_clear(randNum);
  mpz_clear(rndBnd);
  return 0;
}
