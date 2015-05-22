#include<stdio.h>
#include <dirent.h> 
#include <string.h>
#include "paillier.c"
int main(int argc, char *argv[])
{  
  ///list all the files in the directory///
   DIR *d;
   FILE  *fpub, *fpriv, *fciph, *fplain;//, *fp6, *fp7;
   paillier_pubkey_t *pub;
   paillier_prvkey_t *priv;
   paillier_get_rand_t get_rand;
   paillier_plaintext_t *plain;
   paillier_ciphertext_t *cipher;
   char *len;
   int count=0;
   struct dirent *dir;
   plain = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
   cipher = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));
   mpz_init(plain->m);	
   len = (char *)malloc(2048*sizeof(char));
//****paillier key generation****
   if(!(fpub = fopen("pub.txt", "r")))
    {
       fputs("Not able to read public key file!\n", stderr);
       paillier_keygen(&pub, &priv, get_rand,2048);
       //fclose(fpub);	
       fpub = fopen("pub.txt", "w");
       gmp_fprintf(fpub, "%Zd\n", pub->p); 
       gmp_fprintf(fpub, "%Zd\n", pub->q);	
       gmp_fprintf(fpub, "%Zd\n", pub->n_plusone);	
    }
  else
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
    } 
   fclose(fpub);
  //****end of paillier key generation****
   d = opendir("./cipher/copy3");
   if (d)
   {
    while ((dir = readdir(d)) != NULL)
    {
     //printf("%s\n", dir->d_name);
     char fileName[1000];
     strcpy(fileName, "./cipher/copy3/");
     strcat(fileName,dir->d_name);
     if(!(fciph = fopen(fileName, "r")))
      {
        printf("\n not able to read %s", fileName);
      }
      else
      {
	//printf("\n able to read %s", fileName);
	fgets(len, 2048, fciph);
        mpz_init_set_str(cipher->c, len, 10);	
        //mpz_out_str(stdout, 10, cipher->c);
	fclose(fciph);	
	count++;	
      }		
    strcpy(fileName, "./plain/");
      strcat(fileName,dir->d_name);	
     // printf("\nfilename %s",fileName);
     if(!(fplain = fopen(fileName, "w")))
     {
       printf("not able to open file for writing cipher text %s", fileName);
     }
     else
     {
      plain = paillier_dec(plain, pub,priv, cipher);
      gmp_fprintf(fplain, "%Zd\n", plain->m); 	
      fclose(fplain); 
     }	
    }	
   
    closedir(d);
}
}
