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
   paillier_ciphertext_t *cipher, *cipher_prod, *cipher_total;
   int count = 0, count1=0, val = 163000, no_of_copies = 10;
   long int key_int, key_int1, key_rnd;
   struct dirent *dir;
   char* len;	
   mpz_t           rndKey, randNum, rnd,rnd_sum, rndno, sum, pl_sum;      /* Hold our random numbers */
   mpz_t           rndBnd;       /* Bound for mpz_urandomm */
   mpz_t key, key1;		//key for PRF
   mpz_t plain_total, plain_nomod;
   gmp_randstate_t gmpRandState, gmpRandState1, gmpRandState2; /* Random generator state object */
   
   mpz_init(sum); 
   mpz_init(pl_sum);
   mpz_init(rnd);
   mpz_init(rndno);
   mpz_init(rndBnd);
   mpz_init(randNum);
   mpz_init(key);
   mpz_init(key1);
   mpz_init(rnd_sum);
   mpz_init(plain_total);
   mpz_init(rnd);
   mpz_init(rndKey);
   mpz_init(plain_nomod);
   mpz_set_ui(plain_total, 0);
   
   plain = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
   plain_sum = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
   plain_temp = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
   cipher_prod = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));
   cipher_total = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));
   cipher = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));
   len = (char *)malloc(2048*sizeof(char));
   //mpz_init(cipher_prod->c);
   mpz_init(cipher_total->c);
   mpz_set_ui(rnd_sum, 0);
   mpz_init_set_str(cipher_prod->c, "1", 10);
   mpz_init_set_str(cipher_total->c, "1", 10);
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
    gmp_randinit_default(gmpRandState);
    mpz_set_str(rndBnd, "163000", 10); 
    mpz_set_ui(rndKey, time(NULL));
    gmp_randseed(gmpRandState, rndKey);
    fkey = fopen("prf_key.txt", "w");
    mpz_urandomm(rndno, gmpRandState, pub->n); 
    mpz_set(key, rndno);
    element_fprintf(fkey, "%Zd\n", key);
    mpz_urandomm(rndno, gmpRandState, pub->n); 
    mpz_set(key1, rndno);
    element_fprintf(fkey, "%Zd", key1);  
    fclose(fkey);
    
  	 
  gmp_randseed(gmpRandState, key);
  //mpz_out_str(stdout, 10, rnd);
   //****Opening files to read files and encrypt*****  
    int i, j;
   mpz_t rand_val[val], rand_init[no_of_copies], mpz_result[no_of_copies];
   char fileName[1000], file[1000];
   //strcpy(fileName, "./cipher/copy3/output");
  mpz_set_str(sum, "0", 10);
  mpz_set_str(pl_sum, "0", 10);
  for(j =0; j < no_of_copies; j++)
  {
    mpz_init(rand_init[j]);
    mpz_urandomm(rand_init[j], gmpRandState, pub->n); 
    mpz_add(sum, sum, rand_init[j]);
  //  mpz_mod(sum, sum, pub->n);
    //printf("\n 1st rand \n");
    //mpz_out_str(stdout, 10, rand_init[j]);
  }
 // printf("\nsum\n");
 // mpz_out_str(stdout, 10, sum);
  mpz_set_str(pl_sum, "0", 10);
  gmp_randseed(gmpRandState, key1);
  for(j =0; j < no_of_copies; j++)
  {
   mpz_set_ui(cipher_prod->c, 1);
   for(i = 0; i < val; i++)
   {
     sprintf(fileName, "./cipher/copy%d/output", (j+1));
     
     if(j == 0)
     {
      do	
        mpz_urandomm(randNum, gmpRandState, rndBnd);
      while(mpz_cmp_ui(randNum,0) ==0);
      mpz_init(rand_val[i]);
      mpz_set(rand_val[i], randNum);
      //printf("\n2ndrand\n");
      //mpz_out_str(stdout, 10, randNum);
     // printf("random\n");
     // mpz_out_str(stdout, 10, rand_val[i]);
     }
     else
     {
      mpz_set(randNum, rand_val[i]);
      }
    // sprintf(num, "output%d.txt", (j+1));
     mpz_get_str(file, 10, randNum);
     strcat(fileName, file);
     strcat(fileName,".txt");
     count = 0;
   //  printf("\n%s", fileName);
     //mpz_out_str(stdout, 10, randNum);
     if(!(fciph = fopen(fileName, "r")))
       {
         printf("\n not able to read %s", fileName);
         //  fputs("not possible to read  file!\n", stderr);
       } 
     else
       {
	fgets(len, 1000, fciph);
	mpz_init_set_str(cipher->c, len, 10);
	//if(strstr(dir->d_name, "output") != NULL)
        //{
	//  printf("\ncipher\n");
          //mpz_out_str(stdout, 10, cipher->c);
          paillier_mul(pub, cipher_prod, cipher_prod, cipher);
	  // printf("\ncipher after product\n");
          //mpz_out_str(stdout, 10, cipher_prod->c);
        //}
	fclose(fciph);
       }
     if(j == 0)
      {
       strcpy(fileName, "./split/output"); 
       strcat(fileName, file);
       strcat(fileName,".txt");
       if(!(fplain = fopen(fileName, "r")))
         {
           printf("\n not read %s", fileName);
	   count1++;
         }
        else
         {
	  fgets(len, 1000, fplain);
         // printf("\npleain sum\n");
	 // mpz_out_str(stdout, 10, plain_sum->m);
	  mpz_init_set_str(plain->m, len, 10);
	 // if(strstr(dir->d_name, "output") != NULL)
          //{
	   mpz_add(plain_sum->m, plain_sum->m, plain->m);
	   //mpz_mod(pla in_sum->m, plain_sum->m, pub->n);	
 	  //}
          fclose(fplain);
	 } 
       } 
   } 
    mpz_powm(cipher_prod->c, cipher_prod->c, rand_init[j], pub->n_squared);
    paillier_mul(pub, cipher_total, cipher_total, cipher_prod);
   
    mpz_mul(plain_temp->m, plain_sum->m, rand_init[j]);
    mpz_add(plain_total, plain_total, plain_temp->m);
    mpz_mod(plain_total, plain_total, pub->n); 
   }
   plain = paillier_dec(plain, pub, priv, cipher_total);
   printf("\n decrypt \n");
   mpz_out_str(stdout, 10, plain->m);
   // printf("\n plain total \n");
   //mpz_out_str(stdout, 10, plain_total);
   printf("\n plain text total\n");
    mpz_out_str(stdout, 10, plain_sum->m);
   mpz_mul(pl_sum, plain_sum->m, sum);
   mpz_mul(pl_sum, pl_sum, pub->n);
   mpz_mul(pl_sum, pl_sum, priv->lambda);
 //  mpz_mod(pl_sum, pl_sum, pub->n);
    printf("\n plain text * rnd\n");
    mpz_out_str(stdout, 10, pl_sum);  
   if((fprod = fopen("result/cipher_result.txt", "w")))
        {
         printf("\nWriting the result to file \n");
         gmp_fprintf(fprod, "%Zd\n", cipher_total->c);  
	 fclose(fprod);
        }
   
   return 0;
}
