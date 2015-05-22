// Boneh-Lynn-Shacham short signatures demo.
//
// See the PBC_sig library for a practical implementation.
//
// Ben Lynn
#include<math.h>
#include "include/pbc.h"
#include "include/pbc_test.h"
#include<stdio.h>
#include <dirent.h> 
#include <string.h>

static const char* param_str = "type f \
q 205523667896953300194896352429254920972540065223 \
r 205523667896953300194895899082072403858390252929 \
b 40218105156867728698573668525883168222119515413 \
beta 115334401956802802075595682801335644058796914268 \
alpha0 191079354656274778837764015557338301375963168470 \
alpha1 71445317903696340296199556072836940741717506375";
int main(int argc, char **argv) {
  
  FILE  *ftag;//, *ftag, *fdata, *fresult, *fplain, *fkey;
  pairing_t pairing;
  element_t g1, g2;
 // element_t public_key, tag, tag_prod;
 // element_t secret_key;
 
 // mpz_t pub_n, a, b, data2, nsquare;
  
  int count = 0, val=5;
  char *len;
  len = (char *)malloc(2048*sizeof(char));
  pairing_init_set_str(pairing, param_str);
  //mpz_init_set_str(data_sum, "0", 10);

  //pbc_demo_pairing_init(pairing, argc, argv);
  element_init_G1(g1, pairing);
  element_init_G1(g2, pairing);

  ftag = fopen("./tag/output3.txt", "r");
  fgets(len, 1000, ftag);
  element_set_str(g1, len, 10);
  element_printf("\ng1 = %B\n", g1);
  fclose(ftag);  
  int i;
  char fileName[1000];
  
  for(i =1; i<= 4227; i++)
   {
    // printf("\n hello");
     sprintf(fileName, "./tag/output%d.txt", i);
     ftag = fopen(fileName, "r");
     fgets(len, 1000, ftag);
     fclose(ftag);     
     element_set_str(g2, len, 10); 
     if(!element_cmp(g1, g2))
      {
        printf("\n%s", fileName);
      }

   }

 return 0;
}



