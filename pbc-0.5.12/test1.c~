#include<stdio.h>
#include<gmp.h>
#include<stdlib.h>
int main()
{

  FILE *fkey, *frnd;
  mpz_t          rnd;      /* Hold our random numbers */
  mpz_t           rndBnd;       /* Bound for mpz_urandomm */
  mpz_t key, pub_n;		//key for PRF
  gmp_randstate_t gmpRandState; /* Random generator state object */
  char *len;
  mpz_init(rnd);
  mpz_init(rndBnd);
  mpz_init(key);
  mpz_init(pub_n);
  gmp_randinit_default(gmpRandState);
  len = (char *)malloc(2048*sizeof(char));
  fkey = fopen("keyforrand.txt","r");
  fgets(len, 1000, fkey);
  fclose(fkey);
  mpz_set_str(key, len, 10);  
  mpz_out_str(stdout, 10, key);
  gmp_randseed(gmpRandState, key);
  int i;
  frnd = fopen("pairing.txt", "r");
  fgets(len, 1000, frnd);
	fgets(len, 1000, frnd);
	fgets(len, 1000, frnd);
	fgets(len, 1000, frnd);
	fgets(len, 1000, frnd);
	fgets(len, 1000, frnd);
	mpz_init_set_str(pub_n, len, 10);
   fclose(frnd);
  for(i = 0; i < 3; i++)
   {    
      do	
        mpz_urandomm(rnd, gmpRandState, pub_n);
      while(mpz_cmp_ui(rnd,0) ==0);
     printf("\n rand ");
     mpz_out_str(stdout, 10, rnd);
     printf("\n");
   }
 return 0;
}
