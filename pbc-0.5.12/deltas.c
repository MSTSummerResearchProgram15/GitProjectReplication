#include<stdio.h>
#include <dirent.h> 
#include <string.h>
#include "paillier.c"
int main(int argc, char *argv[])
{  
   DIR *d;
   FILE  *fpub, *fciph, *fplain, *fprod, *fkey;
   paillier_pubkey_t *pub;
   paillier_plaintext_t *plain, *plain_sum, *plain_temp;
   paillier_prvkey_t *priv;
   paillier_get_rand_t get_rand;
   paillier_ciphertext_t *cipher, *cipher_prod;
   plain = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
   plain_sum = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
   plain_temp = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
   cipher_prod = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));
 //  cipher_total = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));
   cipher = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));
   char* len;
   len = (char *)malloc(2048*sizeof(char));
   //mpz_init(cipher_prod->c);
  // mpz_init(cipher_total->c);
  // mpz_set_ui(rnd_sum, 0);
   mpz_init_set_str(cipher_prod->c, "1", 10);
   //mpz_init_set_str(cipher_total->c, "1", 10);
   mpz_init_set_str(plain_sum->m, "0", 10);
  // printf("\nloading pailler keys");
   if((fpub = fopen("pub.txt", "r")))
    {
       	pub = (paillier_pubkey_t*) malloc(sizeof(paillier_pubkey_t));
	priv = (paillier_prvkey_t*) malloc(sizeof(paillier_prvkey_t));	
	mpz_init(pub->n_squared);
	mpz_init(pub->n);
	fgets(len, 1000, fpub);
   	mpz_init_set_str(pub->p, len, 10);
	fgets(len, 1000, fpub);
   	mpz_init_set_str(pub->q, len, 10);
	fgets(len, 1000, fpub);
   	mpz_init_set_str(pub->n_plusone, len, 10);
	//printf("value of nplusone : \n");
	//mpz_out_str(stdout, 10, pub->n_plusone);
	paillier_keygen(&pub, &priv, get_rand, 0);
        pub->bits = mpz_sizeinbase(pub->n, 2);	
        fclose(fpub);
    }
  char fileName[1000], file[1000];
  int i;
  for(i = 0; i < 4050; i++)
   {
     sprintf(fileName, "./split/output%d.txt", (i+1));
     if(!(fplain = fopen(fileName, "r")))
         {
           printf("\n not read %s", fileName);
	 //  count1++;
         }
        else
         {
	  fgets(len, 1000, fplain);
         
	  mpz_init_set_str(plain->m, len, 10);
	  paillier_enc_orig(cipher, pub,plain, get_rand);
          fclose(fplain);
	 } 
     sprintf(fileName, "./cipher/copy1/output%d.txt", (i+1));
     if(!(fplain = fopen(fileName, "r")))
         {
           printf("\n not read %s", fileName);
	 //  count1++;
         }
        else
         {
	  fgets(len, 1000, fplain);
          
	  mpz_init_set_str(cipher_prod->c, len, 10);
	  paillier_mul(pub, cipher_prod, cipher_prod, cipher);
          fclose(fplain);
	 } 	
    sprintf(fileName, "./delta/output%d.txt", (i+1)); 
    if(!(fciph = fopen(fileName, "w")))
            {
	         printf("\nnot able to open file for writing cipher text %s", fileName);
	    }
            else
            {
		// printf("\nbefore enc");
		
	        gmp_fprintf(fciph, "%Zd\n", cipher_prod->c); 	
                fclose(fciph); 	
	    }

   }  
 


}
