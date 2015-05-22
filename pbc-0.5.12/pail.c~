#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include <dirent.h> 
#include <string.h>
#include "paillier.c"
#include "include/pbc.h"
#include "include/pbc_test.h"

/*static const char* param_str = "type f \
q 205523667896953300194896352429254920972540065223 \
r 205523667896953300194895899082072403858390252929 \
b 40218105156867728698573668525883168222119515413 \
beta 115334401956802802075595682801335644058796914268 \
alpha0 191079354656274778837764015557338301375963168470 \
alpha1 71445317903696340296199556072836940741717506375";
*/

int main(int argc, char *argv[])
{  
  ///list all the files in the directory///
   DIR *d;
   FILE  *fpub, *fpriv, *fciph, *fplain, *ftag, *fpairing, *ftemp, *frand;//, *fp6, *fp7;
   paillier_pubkey_t *pub;
   paillier_prvkey_t *priv;
   paillier_get_rand_t get_rand;
   paillier_plaintext_t *plain;
   paillier_ciphertext_t *cipher, *cipher_copy;
   paillier_tag* tag;
   mpz_t tag_sig, *rand_prf;
   gmp_randstate_t rand;
   char *len;
   struct stat st= {0};
   unsigned char *data;
   int count=0, count1=0, gbytes, n, no_copies=10;
   struct dirent *dir;
   ///pairing parameters
   pairing_t pairing;
   //pairing_t p;
    //printf("setting pairing parameters\n");
    //pairing_init_set_str(pairing, param_str);
  // printf("after pairing setup\n");
   element_t g, h, u, temp_pow, test1, test2;
   element_t public_key, sig;
   element_t secret_key;
   ///end of pairing parameters
   //initialize pairing parametrs
   pbc_demo_pairing_init(pairing, argc, argv);
   element_init_G2(g, pairing);
   element_init_G1(u, pairing);
   element_init_G1(test1, pairing);
   element_init_G2(test2, pairing);
   element_init_G1(temp_pow, pairing);
   element_init_G2(public_key, pairing);
  // element_from_hash(h, "hashofmessage", 13);
   element_init_G1(h, pairing);
   element_init_G1(sig, pairing);
   element_init_Zr(secret_key, pairing);
   //end of pairing parameters initialization
   //set up pairing parameters
   //generate system parameters
   element_random(g);
  // n = pairing_length_in_bytes_x_only_G1(pairing);
  // data = pbc_malloc(n);
  // gbytes = pairing_length_in_bytes_G2(pairing);
  // printf(" \n g in bytes %d \n", gbytes);
  // element_printf("system parameter g = %B\n", g);
   //generate private key
   element_random(secret_key);
   //generate u
   element_random(u);
   //calculating hash of a file name and mapping it to element in group G1
  // element_from_hash(h, "FileName", 8);	
   element_random(h);
   //element_printf("private key = %B\n", secret_key);
   //compute corresponding public key
   element_pow_zn(public_key, g, secret_key);
   //element_printf("public key = %B\n", public_key);
   //end of setup
   tag = (paillier_tag*) malloc(sizeof(paillier_tag));
   plain = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
   cipher = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));
   mpz_init(plain->m);
   mpz_init(tag->t);	
   mpz_init(cipher->c);
   mpz_init(tag_sig);	
   rand_prf = (mpz_t*) malloc(n*sizeof(mpz_t));
   
   len = (char *)malloc(2048*sizeof(char));
  //****paillier key generation****
   if(!(fpub = fopen("pub.txt", "r")))
    {
       //fputs("Not able to read public key file!\n", stderr);
       paillier_keygen(&pub, &priv, get_rand,450);
       //fclose(fpub);	
       fpub = fopen("pub.txt", "w");
       gmp_fprintf(fpub, "%Zd\n", pub->p); 
       gmp_fprintf(fpub, "%Zd\n", pub->q);	
       gmp_fprintf(fpub, "%Zd\n", pub->n_plusone);
       //***Writing private keys into a file***
       fpriv = fopen("priv.txt", "w"); 	
       gmp_fprintf(fpriv, "%Zd\n", priv->lambda);  		
       gmp_fprintf(fpriv, "%Zd\n", priv->x);  		
       fclose(fpriv);
       //****End of writing private key in a file***	
    }
   else
    {
        printf("\n in else");
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
    }
   fclose(fpub);
  //****end of paillier key generation****
  //printf("writing pairing parameters to a file\n");
  //writing pairing keys to file
  fpairing = fopen("pairing.txt", "w"); 
  
 /* n = pairing_length_in_bytes_compressed_G2(pairing);
  data = pbc_malloc(n);

  element_to_bytes_compressed(data, g);	
  element_printf(" decomp g %B\n", g);
  element_from_bytes_compressed(test2, data);
  element_printf(" decomp g %B\n", test2); */
  //writing compressed g to file
  element_fprintf(fpairing, "%B\n", g); 
//  element_printf(" g = %B\n", g);
  /*n = pairing_length_in_bytes_compressed_G1(pairing);
  data = pbc_malloc(n);
  element_to_bytes_compressed(data, u);	
  element_printf(" decomp g %B\n", u);
  element_from_bytes_compressed(test1, data);
  element_printf(" decomp g %B\n", test1);  
  //writing compressed u to file */
  element_fprintf(fpairing, "%B\n", u);
  //element_printf(" u = %B\n", u);
  //writing secret key to file
  element_fprintf(fpairing, "%B\n", secret_key); 
  //element_printf(" sk = %B\n", secret_key);
//  printf("secret key = %s\n",secret_key);	
 /* n = pairing_length_in_bytes_compressed_G2(pairing);
  data = pbc_malloc(n);
  element_to_bytes_compressed(data, public_key); 
  //writing compressed public key to file	*/ 
  element_fprintf(fpairing, "%B\n", public_key); 
  //element_printf("pk = %B\n", public_key);	
 /* n = pairing_length_in_bytes_compressed_G1(pairing);
  data = pbc_malloc(n);
  element_to_bytes_compressed(data, h);	
  element_printf(" decomp g %B\n", h);
  element_from_bytes_compressed(test1, data);
  element_printf(" decomp g %B\n", test1);  
  //writing compressed h to file */
  element_fprintf(fpairing, "%B\n", h);
  //element_printf("h = %B\n", h);
  //writing n to file
  gmp_fprintf(fpairing, "%Zd\n", pub->n);  		
  fclose(fpairing);
  //end of writing pairing keys to file  
  cipher_copy = (paillier_ciphertext_t*)malloc(no_copies*sizeof(paillier_ciphertext_t));
  frand = fopen("rand.txt","w");
  int i;
   init_rand(rand, get_rand, pub->bits / 8 + 1);
   for(i = 0; i< no_copies; i++)
   {
	mpz_init(rand_prf[i]);
	do
		mpz_urandomb(rand_prf[i], rand, pub->bits);
	while( mpz_cmp(rand_prf[i], pub->n) >= 0 );
	gmp_fprintf(frand, "%Zd\n", rand_prf[i]); 
	//printf("\nrandom : \n");
        //mpz_out_str(stdout, 10, rand_prf[i]);
   }
  fclose(frand);
  //****Opening files to read files and encrypt***** 
  d = opendir("./split");
   if (d)
   {
    while ((dir = readdir(d)) != NULL)
    {
     //printf("%s\n", dir->d_name);
     char fileName[1000], copy[1000];
     strcpy(fileName, "./split/");
     strcat(fileName,dir->d_name);	
     //printf("\nfile name %s", fileName);
     if(!(fplain = fopen(fileName, "r")))
      {
        printf("\n not able to read %s", fileName);
      //  fputs("not possible to read  file!\n", stderr);
	 count1++;
      }
      else
      {
	//printf("\n able to read %s", fileName);
	fgets(len, 2048, fplain);
        mpz_init_set_str(plain->m, len, 10);	
       // mpz_out_str(stdout, 10, plain->m);
	fclose(fplain);	
	//Writing cipher text to files
	strcpy(fileName, "./cipher/");
        //strcat(fileName,dir->d_name);	
        //printf("\nfilename %s",fileName);
        
         paillier_enc(tag, cipher_copy, pub,plain, get_rand, no_copies, rand_prf);
	// mpz_out_str(stdout, 10, tag->t);
	 int j;
         for(j=0;j < no_copies; j++)
         {
	    char num[20];
	    strcpy(copy, fileName);

	    sprintf(num, "copy%d/", (j+1));
	   // strcat(copy, );
	    strcat(copy, num);
	   if(stat(copy, &st) == -1)
	      mkdir(copy,0777);

            strcat(copy,dir->d_name);
            if(!(fciph = fopen(copy, "w")))
            {
	         printf("\nnot able to open file for writing cipher text %s", copy);
	    }
            else
            {
		// printf("\nbefore enc");
		
	        gmp_fprintf(fciph, "%Zd\n", cipher_copy[j].c); 	
                fclose(fciph); 	
	    }
         }	
	//writing tags to files
	strcpy(fileName, "./tag/");
        strcat(fileName,dir->d_name);	
        //printf("\nfilename %s",fileName);
        if(!(ftag = fopen(fileName, "w")))
        {
         printf("not able to open file for writing tag  %s", fileName);
        }
        else
        {
	
	 element_pow_mpz(temp_pow,u, tag->t);
	 element_mul(temp_pow, temp_pow, h);
	 element_pow_zn(sig, temp_pow, secret_key);
	 element_fprintf(ftag, "%B", sig);
	 fclose(ftag); 
        } 	
      }	
	count++;
    }	
   
    closedir(d);
   }
   
   printf("\nTotal number of files : %d, unreadable files %d", count, count1);
  
   return 0;
}
