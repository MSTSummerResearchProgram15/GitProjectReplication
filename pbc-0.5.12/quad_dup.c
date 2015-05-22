#include<stdio.h>
#include<stdlib.h>
#include <gmp.h>
int main(int argc, char *argv[])
{  
  FILE  *fpub, *fquad;
  int i = 1;
   mpz_t           randNum, n, p, q, amodp, amodq, p1, q1, g;      /* Hold our random numbers */
   gmp_randstate_t gmpRandState; /* Random generator state object */
  char *len;
  len = (char *)malloc(2048*sizeof(char));
  //mpz_init_set_str(i, "0", 10);
 
  mpz_init(amodp);
  mpz_init(amodq);
  mpz_init(randNum);
  mpz_init(p1);
  mpz_init(q1);
  mpz_init(g);
  mpz_sub_ui(p1, p, 1);
  mpz_sub_ui(q1, p, 1);
  gmp_randinit_default(gmpRandState);
  if((fpub = fopen("pub.txt", "r")))
   {
     fgets(len, 1000, fpub);
     mpz_init_set_str(p, len, 10);
     fgets(len, 1000, fpub); 	
     mpz_init_set_str(q, len, 10);
     fgets(len, 1000, fpub);
     mpz_init_set_str(n, len, 10);
     mpz_out_str(stdout, 10, n);       
   }
  fclose(fpub);
  mpz_urandomm (randNum, gmpRandState, n);
  printf("\n");
  int j=0;
  while(i == 1)
  {
     int c1, c2, c3, d1, d2, d3;
    printf("\n%d", j);
    mpz_mod(amodp, randNum, p);
    mpz_mod(amodq, randNum, q);
     c1 = mpz_cmp_si(amodp, 0);
     c2 = mpz_cmp_si(amodp, 1);
     c3 = mpz_cmp(amodp, p1);
     d1 = mpz_cmp_si(amodq, 0);
     d2 = mpz_cmp_si(amodq, 1);
     d3 = mpz_cmp(amodq, q1);
     if(c1 == 0 || c2 == 0 || c3 == 0 || d1 == 0 || d2 == 0|| d3 == 0)
      i = 1;
     else
      {
       i = 0;
       printf("\n");
       mpz_out_str(stdout, 10, randNum);     
       printf("\n");  
      }
  }
  mpz_mul(g, randNum, randNum);
  mpz_mod(g, g, n);
  fquad = fopen("generator.txt", "w");
  gmp_fprintf(fquad, "%Zd\n", g);   
  fclose(fquad);
}
