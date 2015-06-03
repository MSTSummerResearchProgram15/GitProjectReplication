#include<stdio.h>
#include<stdlib.h>
#include <gmp.h>

int main(int argc, char *argv[])
{  
  FILE  *fpub, *fquad;
  char *len;
  int cmp=0;
  mpz_t n, i;
//  mpz_init_set_str(n, "10", 10);
  mpz_init_set_str(i, "1", 10);
  len = (char *)malloc(2048*sizeof(char));
  if((fpub = fopen("pub.txt", "r")))
   {
     fgets(len, 1000, fpub);
     fgets(len, 1000, fpub); 	
     fgets(len, 1000, fpub);
     mpz_init_set_str(n, len, 10);
     mpz_out_str(stdout, 10, n);       
   }
  fclose(fpub);
  mpz_t temp;
  mpz_init(temp);
  fquad = fopen("quad.txt", "w"); 
   while(cmp == 0)
   {
     // int j = mpz_cmp(i, n);
      //printf("\n value of j = %d",j );
    //   mpz_out_str(stdout, 10, mpz_cmp(i, n));
      if(mpz_cmp(n, i))
       {
         mpz_mul(temp, i, i);
         mpz_mod(temp, temp, n);   
         gmp_fprintf(fquad, "%Zd\n", temp);       
         printf(" \ninside");

	 mpz_add_ui(i, i, 1);
       }
      else
	cmp =1;
   }
  fclose(fquad);
}
