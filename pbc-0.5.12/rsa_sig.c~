#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gmp.h>

int main(int argc, char *argv[])
{
  FILE  *fg, *fplain, *ftag, *fn;
  int i, no_files = 8454;
  char *len, fileName[1000];
  mpz_t g, plain, tag, n;
  mpz_init(plain);
  mpz_init(tag);
   len = (char *)malloc(2048*sizeof(char));
  if(!(fg = fopen("generator.txt", "r")))
  {
     
  }
 else
  {
  // printf("generator");
	fgets(len, 1000, fg);
     mpz_init_set_str(g, len, 10);
  //   mpz_out_str(stdout, 10, g);
     fclose(fg);
  }
  if(!(fn = fopen("pub.txt", "r")))
  {
    
  }
  else
  {
     fgets(len, 1000, fn);
     fgets(len, 1000, fn);
     fgets(len, 1000, fn);	
     mpz_init_set_str(n, len, 10);
     fclose(fn);
  }
 
 for(i = 0; i < no_files; i++)
  {
     printf("\n %d", i);
     sprintf(fileName, "./split/output%d.txt", (i+1));
     if(!(fplain = fopen(fileName, "r")))
         {
           printf("\n not read %s", fileName);
	 //  count1++;
         }
        else
         {
	  fgets(len, 1000, fplain);
          mpz_set_str(plain, len, 10);
	  fclose(fplain);
	 } 
     mpz_powm(tag, g, plain, n); 
     sprintf(fileName, "./tag_rsa/output%d.txt", (i+1));
     ftag = fopen(fileName, "w");
     gmp_fprintf(ftag, "%Zd", tag);
     fclose(ftag); 
  } 

}
