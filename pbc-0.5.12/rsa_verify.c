// Boneh-Lynn-Shacham short signatures demo.
//
// See the PBC_sig library for a practical implementation.
//
// Ben Lynn
#include<math.h>
#include "gmp.h"
#include<stdlib.h>
#include<stdio.h>
#include <string.h>

/*static const char* param_str = "type f \
q 205523667896953300194896352429254920972540065223 \
r 205523667896953300194895899082072403858390252929 \
b 40218105156867728698573668525883168222119515413 \
beta 115334401956802802075595682801335644058796914268 \
alpha0 191079354656274778837764015557338301375963168470 \
alpha1 71445317903696340296199556072836940741717506375"; */
int main(int argc, char **argv) {
 
  FILE   *ftag, *fresult, *fn, *fkey;
  mpz_t data1, data2, data_sum, tag, tag_prod, pub_n;
  mpz_t           randNum, rnd,rnd_sum;      /* Hold our random numbers */
  mpz_t           rndBnd;       /* Bound for mpz_urandomm */
  mpz_t key;		//key for PRF
  gmp_randstate_t gmpRandState; /* Random generator state object */
  int count = 0, val=80000;
  mpz_t dval;
  mpz_init(dval);
  mpz_init(tag);
  mpz_set_ui(dval, val);
  mpz_init_set_str(data_sum, "0", 10);
  mpz_init(data_sum);
  mpz_init(data1);
  mpz_init(data2);
  mpz_init(rnd);
  mpz_init(rndBnd);
  mpz_init(randNum);
  mpz_init(key);
  gmp_randinit_default(gmpRandState);
  mpz_set(rndBnd, dval);
  char *len;
  
  printf("Short signature test\n");
  len = (char *)malloc(2048*sizeof(char));
  //getting prf key
  fkey = fopen("prf_key.txt", "r");
  fgets(len, 1000, fkey);
  fgets(len, 1000, fkey);
  fclose(fkey);

  if((fn = fopen("pub.txt", "r")))
   {
     fgets(len, 1000, fn);
     //mpz_init_set_str(p, len, 10);
     fgets(len, 1000, fn); 	
     //mpz_init_set_str(q, len, 10);
     fgets(len, 1000, fn);
     mpz_init_set_str(pub_n, len, 10);
     //mpz_out_str(stdout, 10, n);       
   }
  fclose(fn);

  mpz_set_str(key, len, 10);
  gmp_randseed(gmpRandState, key);
  int i;
  

    
  char fileName[1000], file[1000];
  for(i = 0; i < val; i++)
   {    
      do	
        mpz_urandomm(randNum, gmpRandState, rndBnd);
      while(mpz_cmp_ui(randNum,0) ==0);
      strcpy(fileName, "./tag_rsa/output");
      mpz_get_str(file, 10, randNum);
      strcat(fileName, file);
      strcat(fileName,".txt");
      if((ftag = fopen(fileName, "r")))
      {
	fgets(len, 1000, ftag);
        mpz_set_str(tag, len, 10);
	
        if(strstr(fileName, "output") != NULL)
        {	
	  if(count == 0)
	  {
	   mpz_init_set_str(tag_prod, len, 10);
	  }
	  else
	  {
	   mpz_mul(tag_prod, tag, tag_prod);
           mpz_mod(tag_prod, tag_prod, pub_n);
	  }
	 count++;
	}
	fclose(ftag);
	
       }
      
     }
     
   
   if((fresult = fopen("./result/rsa_tag_result.txt", "w")))
     {
	printf("\nwriting to file");
        gmp_fprintf(fresult, "%Zd", tag_prod);  
	fclose(fresult);
     }	
   else
     {
	printf("cannot open file");
     }	
   
 
 return 0;
}



