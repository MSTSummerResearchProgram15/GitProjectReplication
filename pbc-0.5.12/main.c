// AES usage example
// compile as: gcc main.c aes.h aes.c

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include "aes.h"
#include "aes.c"
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
        FILE *fp, *fpairing;
	unsigned char key[KEY_128] = "uber strong key!";
	unsigned char ctext[16];
	unsigned char decptext[16];
	aes_ctx_t *ctx;
	int i, count=0, no_copies =3, j;
        mpz_t tags;
       // struct stat st= {0};
       // struct dirent *dir;
        pairing_t pairing;
        pairing_init_set_str(pairing, param_str);
        element_t g, h, u, temp_pow, prod;
        element_t public_key, sig;
        element_t secret_key;
        ///end of pairing parameters
        //initialize pairing parametrs
        // pbc_demo_pairing_init(pairing, argc, argv);
        mpz_init(tags);
        element_init_G2(g, pairing);
	element_init_G1(u, pairing);
	element_init_G1(prod, pairing); 
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
        element_random(secret_key);
        //generate u
        element_random(u);
        element_random(h);
        element_pow_zn(public_key, g, secret_key);
        //end of setup
        //writing pairing parameters to file
        fpairing = fopen("pairing_aes.txt", "w"); 
        element_fprintf(fpairing, "%B\n", g); 
        element_fprintf(fpairing, "%B\n", u);
        element_fprintf(fpairing, "%B\n", secret_key); 
        element_fprintf(fpairing, "%B\n", public_key); 
        element_fprintf(fpairing, "%B\n", h);
        fclose(fpairing);
        //end of writing to file
        char *len, fileName[1000], *data;
        len = (char *)malloc(2048*sizeof(char));
        data = (char *)malloc(2048*sizeof(char));
        init_aes();
        ctx = aes_alloc_ctx(key, sizeof(key));
	if(!ctx) {
		perror("aes_alloc_ctx");
		return EXIT_FAILURE;
	}
        char *copy, *fname, x[50], tm[50];
        int num, k;
        copy = (char *)malloc(1000*sizeof(char));
        fname = (char *)malloc(1000*sizeof(char));
        for(i = 0; i < 748398; i++)
        {
           sprintf(fileName, "./split_aes/output%d.txt",(i+1));
          //strcpy(fileName, "./split_aes/");
          if((fp = fopen(fileName, "r")))
          {
           //printf("\nfile opened");
	   fgets(len, 1000, fp);
           fclose(fp);
          
           for(j = 0; j < 3; j++)
           {
            sprintf(data, "%d", (j+1));
            strcat(data, len);
            //printf("\n copy %d file %d - text %s", (j+1), (i+1), data);
            aes_encrypt(ctx, data, ctext);
           // printf("\n");          
            
            if((i % 256) == 0)
            { 
              sprintf(copy, "./cipher_aes/copy%d/",(j+1));
              d = opendir(copy);
              num = (i/256)+1;
             // printf("\n num %d", num);
              sprintf(fname, "file%d/", num);
              strcat(copy, fname);
              mkdir(copy,0777);
              closedir(d);
//              printf("\nfile %s - %d",fname, num);
            }
            sprintf(fileName, "./cipher_aes/copy%d/file%d/output%d.txt",(j+1), num, (i+1) );
            //printf("\n file name - %s", fileName);
            if(fp = fopen(fileName, "w"))
            {
            // printf("\n");
             strcpy(tm, "");
	     for(k = 0; k < 16; k++)
		{
              //    printf("%02d", ctext[k]);   
                  sprintf(x,"%02d", ctext[k]);
                  strcat(tm, x);
                fprintf(fp,"%02d", ctext[k]);
                }
             fclose(fp);
            }
           /* else
            {
              printf("\n in else");
            } */
            //creating tags
            mpz_set_str(tags, tm, 10);
	   // element_printf("\n val %Zd", tags);
	    element_pow_mpz(temp_pow,u, tags);
	   // element_mul(temp_pow, temp_pow, h);
	    element_pow_zn(sig, temp_pow, secret_key);
         
             
            if((i % 256) == 0)
            { 
               if(i > 0)
               { 
                sprintf(fileName, "./tag_aes/copy%d/output%d.txt", (j+1),num-1);
	        fp = fopen(fileName, "w");
                element_fprintf(fp, "%B", prod);
                fclose(fp);
               } 
               element_set(prod, sig);
            }
            else
              element_mul(prod, prod, sig);	
	   }
            count++;
          }
        else
          {
           printf("\n file not opened %s", fileName);
           break;
          }
        } 
        
        printf("\n count %d", count);
	aes_free_ctx(ctx);
	return EXIT_SUCCESS;
}
