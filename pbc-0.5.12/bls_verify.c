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

/*static const char* param_str = "type f \
q 205523667896953300194896352429254920972540065223 \
r 205523667896953300194895899082072403858390252929 \
b 40218105156867728698573668525883168222119515413 \
beta 115334401956802802075595682801335644058796914268 \
alpha0 191079354656274778837764015557338301375963168470 \
alpha1 71445317903696340296199556072836940741717506375"; */
int main(int argc, char **argv) {
  DIR *d;
  struct dirent *dir;
  FILE  *fpairing, *ftag, *fdata, *fresult, *fplain, *fkey;
  pairing_t pairing;
  element_t g, h, u, sig1, sig2, temp_pow, m;
  element_t public_key, tag, tag_prod;
  element_t secret_key;
  long int key_int;
  mpz_t data1, data2, data_sum, pub_n, nsquare;
  mpz_t           randNum, rnd,rnd_sum;      /* Hold our random numbers */
  mpz_t           rndBnd;       /* Bound for mpz_urandomm */
  mpz_t key;		//key for PRF
  gmp_randstate_t gmpRandState; /* Random generator state object */
  int count = 0, val=163000;
  mpz_t dval;
  mpz_init(dval);
  mpz_init(nsquare);
  mpz_set_ui(dval, val);
 // element_t temp1, temp2;
//pairing_t pairing;
   //pairing_t p;
    //printf("setting pairing parameters\n");
  //  pairing_init_set_str(pairing, param_str);
 pbc_demo_pairing_init(pairing, argc, argv);
 mpz_init_set_str(data_sum, "0", 10);

  //pbc_demo_pairing_init(pairing, argc, argv);

  element_init_G2(g, pairing);
  element_init_G2(public_key, pairing);
  element_init_G1(u, pairing);
  element_init_G1(temp_pow, pairing);
  element_init_G2(public_key, pairing);
  element_init_G1(h, pairing);
  element_init_G1(m, pairing);
  element_init_G1(sig1, pairing);
  element_init_G1(sig2, pairing);
  element_init_G1(tag, pairing); 
  element_init_G1(tag_prod, pairing);
  mpz_init(data_sum);
  mpz_init(data1);
  mpz_init(data2);
  mpz_init(pub_n);
  mpz_init(rnd);
  mpz_init(rndBnd);
  mpz_init(randNum);
  mpz_init(key);
  gmp_randinit_default(gmpRandState);
  mpz_set(rndBnd, dval);
 // element_init_GT(temp1, pairing);
 // element_init_GT(temp2, pairing);
  element_init_Zr(secret_key, pairing);
  char *len;
  
  printf("Short signature test\n");
  len = (char *)malloc(2048*sizeof(char));
  //getting prf key
  fkey = fopen("prf_key.txt", "r");
  fgets(len, 1000, fkey);
  fgets(len, 1000, fkey);
  fclose(fkey);
  mpz_set_str(key, len, 10);
 // key_int = mpz_get_ui(key);
  //printf("\nkey %d", key_int);
   gmp_randseed(gmpRandState, key);
   // mpz_urandomm(rnd, gmpRandState, pub->n); 
  int i;
  
//setting already known pairing parameters
  if((fpairing = fopen("pairing.txt", "r")))
    {
	fgets(len, 1000, fpairing);
	//printf("\n %s\n", len);
   	element_set_str(g, len, 10);
	//element_printf(" g = %B\n", g);
	fgets(len, 1000, fpairing);
	//printf("\n %s\n", len);
   	element_set_str(u, len, 10);
	//element_printf("\n u= %B\n", u);
	fgets(len, 1000, fpairing);
	element_set_str(secret_key, len, 10);
	element_printf(" secretkeuy %B\n",secret_key);
	fgets(len, 1000, fpairing);
	element_set_str(public_key, len, 10);
  //      element_printf(" publickey %B\n", public_key);
	fgets(len, 1000, fpairing);
	element_set_str(h, len, 10);
    //    element_printf(" \nh = %B\n", h);
	fgets(len, 1000, fpairing);
	mpz_init_set_str(pub_n, len, 10);
        mpz_mul(nsquare, pub_n, pub_n);
//	printf("\n n = ");
//	mpz_out_str(stdout, 10, pub_n);
	fclose(fpairing);
    }
   
  element_set1(tag_prod);
  char fileName[1000], file[1000];
  for(i = 0; i < val; i++)
   {    
      do	
        mpz_urandomm(randNum, gmpRandState, rndBnd);
      while(mpz_cmp_ui(randNum,0) ==0);
     // printf("\n2nd random\n");
     // mpz_out_str(stdout, 10, randNum);
      strcpy(fileName, "./tag/output");
      mpz_get_str(file, 10, randNum);
     strcat(fileName, file);
     strcat(fileName,".txt");
   //  printf("\nfile %s", fileName);
     //if(strcmp("output1236.txt", dir->d_name) == 0 || strcmp("output123.txt", dir->d_name) == 0)
    // {	
      if((ftag = fopen(fileName, "r")))
      {
	fgets(len, 1000, ftag);
        element_set_str(tag, len, 10);
	
        if(strstr(fileName, "output") != NULL)
        {	
	  if(count == 0)
	  {
		//  printf(" in count 0");
         	//  element_from_bytes(tag_prod, len);
		  element_set_str(tag_prod, len, 10);
		 // element_printf(" \n tag %B", tag_prod);
	  }
	  else
	  {
	//   printf(" \n in else");
	   element_mul(tag_prod, tag, tag_prod);
	//   element_printf(" \n tag prod %B", tag_prod);
 	  }
	 count++;
	}
	fclose(ftag);
	//verify with sum of plain text
  	strcpy(fileName, "./split/output");
        strcat(fileName, file);
        strcat(fileName,".txt");	
	//printf("\nfile %s", fileName);
	if(!(fplain = fopen(fileName, "r")))
         {
           printf("\n not able to read %s", fileName);
         }
        else
         {
	  fgets(len, 1000, fplain);
	  mpz_init_set_str(data1, len, 10);
	//  printf("\n data %s", len);
	  if(strstr(fileName, "output") != NULL)
          {
	  mpz_add(data_sum, data_sum, data1);
	  mpz_mod(data_sum, data_sum, pub_n);
	  //count++;
           }
          }
	//paillier_mul(pub, cipher_prod, cipher_prod, cipher);
	 fclose(fplain); 
	// } 
       }
      
     }
     
   
   if((fresult = fopen("./result/tag_result.txt", "w")))
     {
	printf("\nwriting to file");
        element_fprintf(fresult, "%B", tag_prod);  
	fclose(fresult);
     }	
   else
     {
	printf("cannot open file");
     }	
    element_printf("\n tag prod - %B \n", tag_prod);	
    printf("\n sum of plain text (without mod)- ");
    mpz_out_str(stdout, 10, data_sum);
    printf("\n count - %d \n", count);
    mpz_t mods;
    mpz_init(mods);
    mpz_mod(mods, data_sum, pub_n);
    printf("\n modded value \n");
    mpz_out_str(stdout, 10, mods);
    printf("\n");
    mpz_t nsq;
    mpz_init(nsq);
    mpz_mul(nsq, pub_n, pub_n);
    element_printf("\n data_sum - %Zd\nnsquare - %Zd\n", data_sum, nsq); 
    
    mpz_mod(data_sum, data_sum, nsq);
    element_printf("\n data_sum after mod nsquare- %Zd\n", data_sum); 
  //  mpz_mul(data_sum, data_sum, pub_n);
    //mpz_mod(data_sum, data_sum, nsquare);
    printf("\n bN = ");
    mpz_out_str(stdout, 10, data_sum);
    element_pow_mpz(temp_pow,u, data_sum);
    //element_printf("\n u^bN = %B\n", temp_pow);
    mpz_set_ui(data2, count);
  //  itoa(count, len, 10);+
    //element_printf(" \nh = %B\n", h);
    element_pow_mpz(h, h, data2);
    element_mul(temp_pow, temp_pow, h);
    //element_printf("\n h. u^bN = %B\n", temp_pow);
    element_pow_zn(sig1, temp_pow, secret_key);
    element_printf("\n user created - %B\n", sig1); 
    
 
 return 0;
}



