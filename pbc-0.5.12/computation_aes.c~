#include<stdio.h>
#include <dirent.h> 
#include <string.h>
#include "include/pbc.h"
#include "include/pbc_test.h"

static const char* param_str = "type f \
q 205523667896953300194896352429254920972540065223 \
r 205523667896953300194895899082072403858390252929 \
b 40218105156867728698573668525883168222119515413 \
beta 115334401956802802075595682801335644058796914268 \
alpha0 191079354656274778837764015557338301375963168470 \
alpha1 71445317903696340296199556072836940741717506375";

int main(int argc, char *argv[])
{  
   DIR *d;
   FILE *fkey, *ftag, *fcipher, *fpairing;
   mpz_t           rndKey, randNum, rnd,rnd_sum, rndno;      /* Hold our random numbers */
   mpz_t           rndBnd;       /* Bound for mpz_urandomm */
   gmp_randstate_t gmpRandState; /* Random generator state object */
   mpz_t key, key1, data2;	
   int count = 0, val = 275, no_copies = 2;
   struct dirent *dir;
   char *len;
   len = (char *)malloc(2048*sizeof(char));
  // mpz_init(sum); 
   mpz_init(rnd);
   mpz_init(rndno);
   mpz_init(rndBnd);
   mpz_init(randNum);
   mpz_init(key);
   mpz_init(key1);
   mpz_init(rnd_sum);
   mpz_init(rnd);
   mpz_init(rndKey);
   mpz_init(data2);
   pairing_t pairing;
   element_t g, h, u, sig1, sig2, temp_pow, m;
   element_t public_key, tag, tag_prod, total_prod;
   element_t secret_key;
   //random number initialization
   gmp_randinit_default(gmpRandState);
   mpz_set_str(rndBnd, "1462", 10); 
   mpz_set_ui(rndKey, time(NULL));
   gmp_randseed(gmpRandState, rndKey);
   fkey = fopen("prf_key_aes.txt", "w");
   mpz_urandomm(rndno, gmpRandState, rndKey); 
   mpz_set(key, rndno);
   element_fprintf(fkey, "%Zd\n", key);
   mpz_urandomm(rndno, gmpRandState, rndKey); 
   mpz_set(key1, rndno);
   element_fprintf(fkey, "%Zd", key1);  
   fclose(fkey);
    pairing_init_set_str(pairing, param_str);  
   element_init_G2(g, pairing);
   element_init_G1(total_prod, pairing);
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
   //element_init_G1(sig, pairing);
   element_init_Zr(secret_key, pairing);  
   //setting already known pairing parameters
  if((fpairing = fopen("pairing_aes.txt", "r")))
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
//	element_printf(" secretkeuy %B\n",secret_key);
	fgets(len, 1000, fpairing);
	element_set_str(public_key, len, 10);
  //      element_printf(" publickey %B\n", public_key);
	fgets(len, 1000, fpairing);
	element_set_str(h, len, 10);
    //    element_printf(" \nh = %B\n", h);
	fclose(fpairing);
    }
    mpz_t rand_val[val];
   char fileName[1000], file[1000];;
   mpz_t sum, total_sum, tmp;
   mpz_init(sum);
   mpz_init(total_sum);
   mpz_init(tmp);
   mpz_set_ui(total_sum, 0);
   gmp_randseed(gmpRandState, key);
   int i, j;
  /* for(i  = 0; i < no_copies; i++)
    {
      for(j = 0; j< val;j++) 
      {
        if(i == 0)
        {
          do	
           mpz_urandomm(randNum, gmpRandState, rndBnd);
          while(mpz_cmp_ui(randNum,0) ==0);
          mpz_init(rand_val[i]);
          mpz_set(rand_val[i], randNum);
        }
      }   

    }
    */
   for(i  = 0; i < 275; i++)
    {
      do	
        mpz_urandomm(randNum, gmpRandState, rndBnd);
      while(mpz_cmp_ui(randNum,0) ==0);
   //   printf("\n2nd random\n");
     // mpz_out_str(stdout, 10, randNum);
       mpz_set_ui(sum, 0); 
      for(j = 0; j < no_copies; j++)
      {
	      sprintf(fileName, "./tag_aes/copy%d/output", (j+1));
	      mpz_get_str(file, 10, randNum);
	      strcat(fileName, file);
	      strcat(fileName,".txt");
             // printf("\n filename %s \n", fileName);
	     if((ftag = fopen(fileName, "r")))
	      {
		fgets(len, 1000, ftag);
	        element_set_str(tag, len, 10);
		if(strstr(fileName, "output") != NULL)
	        {	
		  if(j == 0)
		  {
			element_set_str(tag_prod, len, 10);
		  }
		  else
		  {
		        element_mul(tag_prod, tag, tag_prod);
		  }
	        }//for if 
              }//for if
	     fclose(ftag);  
             sprintf(fileName, "./cipher_aes/copy%d/file", (j+1));
              strcat(fileName, file);
	      strcat(fileName,"/");
           //   printf("\n filename %s \n", fileName);
             d = opendir(fileName);
             if (d)
             {
               count = 0;  
                     
               while ((dir = readdir(d)) != NULL)
               {
		    strcpy (file, fileName);
                    strcat(file,dir->d_name);
                    //printf("\n file name %s\n", file);
                    if((fcipher = fopen(file, "r")))
	            {        
                      fgets(len, 1000, fcipher);
                      mpz_set_str(tmp, len, 10);
                      // element_printf(" \nstmp %Zd - %s", tmp, fileName);
                    }
                    else
                    {
                       printf("\n in else");
                    } 
		    fclose(fcipher);
		    mpz_add(sum, sum, tmp);
                    count++;
               }//forwhile
             }//for if
            closedir(d); 
        }//for for with j 
       // printf("\ncount %d", count);
        mpz_mul(total_sum, sum, randNum);
//        if(i == 0)
        element_pow_mpz(tag_prod, tag_prod, randNum);
        if(i == 0)
         element_set(total_prod, tag_prod);
        else
         element_mul(total_prod, tag_prod, total_prod);
        
      }//for for with i 
    mpz_set_ui(data2, 256*(no_copies));
    //element_printf(" \nh = %B\n", h);
   // element_pow_mpz(h, h, data2);
    element_pow_mpz(temp_pow, u, total_sum);
    //element_mul(temp_pow, temp_pow, h);
  
    element_printf("\n %Zd \nh. u^bN = %B\n",sum , temp_pow);
    element_pow_zn(sig1, temp_pow, secret_key);
    element_printf("\n sig 3 %B\n user sig %B", sig1, total_prod); 
   return 0;
}
