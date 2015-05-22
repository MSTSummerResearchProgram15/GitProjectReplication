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
#include "paillier.c"

static const char* param_str = "type f \
q 205523667896953300194896352429254920972540065223 \
r 205523667896953300194895899082072403858390252929 \
b 40218105156867728698573668525883168222119515413 \
beta 115334401956802802075595682801335644058796914268 \
alpha0 191079354656274778837764015557338301375963168470 \
alpha1 71445317903696340296199556072836940741717506375";
int main(int argc, char **argv) {
  
  FILE  *fpairing, *ftag, *fdata, *fresult, *fplain, *fkey, *fcipher, *fpub;
  pairing_t pairing;
  paillier_pubkey_t *pub;
  paillier_prvkey_t *priv;
  element_t g, h, u, sig1, sig2, sig3, temp_pow, m, g1, g2;
  element_t public_key, tag, tag_prod;
  element_t secret_key;
  paillier_get_rand_t get_rand;
  paillier_ciphertext_t *cipher1, *cipher2;
  paillier_plaintext_t *plain1, *plain2;
 
  mpz_t pub_n, a, b, data2, nsquare;
  

  int count = 0, val=5;
  pairing_init_set_str(pairing, param_str);
  //mpz_init_set_str(data_sum, "0", 10);

  plain1 = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
  plain2 = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
  cipher1 = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));
  cipher2 = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));

  //pbc_demo_pairing_init(pairing, argc, argv);
  element_init_G1(g1, pairing);
  element_init_G1(g2, pairing);
  element_init_G2(g, pairing);
  element_init_G2(public_key, pairing);
  element_init_G1(u, pairing);
  element_init_G1(temp_pow, pairing);
  element_init_G2(public_key, pairing);
  element_init_G1(h, pairing);
  element_init_G1(m, pairing);
  element_init_G1(sig1, pairing);
  element_init_G1(sig2, pairing);
  element_init_G1(sig3, pairing); 
  element_init_G1(tag, pairing); 
  element_init_G1(tag_prod, pairing);
  element_init_Zr(secret_key, pairing);
//  mpz_init(pub_n);
  char *len;
  mpz_init(a);
  mpz_init(b);
  mpz_init(data2);
  printf("Short signature test\n");
  len = (char *)malloc(2048*sizeof(char));

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
	//element_printf(" secretkey %B\n",secret_key);
	fgets(len, 1000, fpairing);
	element_set_str(public_key, len, 10);
        //element_printf(" publickey %B\n", public_key);
	fgets(len, 1000, fpairing);
	element_set_str(h, len, 10);
        //element_printf(" \nh = %B\n", h);
	fgets(len, 1000, fpairing);
	mpz_init_set_str(pub_n, len, 10);
	//printf("\n n = ");
	//mpz_out_str(stdout, 10, pub_n);
	fclose(fpairing);
    }
   
  element_set1(tag_prod);
 
   ftag = fopen("./tag/output5.txt", "r");
   fgets(len, 1000, ftag);
   element_set_str(g1, len, 10);
   element_printf("\ng1 = %B\n", g1);
   fclose(ftag);  
 
   ftag = fopen("./tag/output6.txt", "r");
   fgets(len, 1000, ftag);
   element_set_str(g2, len, 10);
   element_printf("\ng2 = %B\n", g2);
   fclose(ftag);

   fplain = fopen("./split/output5.txt", "r");
   fgets(len, 1000, fplain);
//   printf("\nlen %s", len);
   mpz_set_str(a, len, 10);
   //element_printf("\na = %Zd\n", a);
   fclose(fplain);
  fplain = fopen("./split/output6.txt", "r");
   fgets(len, 1000, fplain);
   mpz_set_str(b, len, 10);

  fcipher = fopen("./cipher/copy1/output5.txt", "r");
   fgets(len, 1000, fcipher);
   mpz_init_set_str(cipher1->c, len, 10);
  fclose(fcipher);

   fcipher = fopen("./cipher/copy1/output6.txt", "r");
   fgets(len, 1000, fcipher);
   mpz_init_set_str(cipher2->c, len, 10);
   fclose(fcipher);
  
   paillier_mul(pub, cipher2, cipher2, cipher1);
   plain1 = paillier_dec(plain1, pub, priv, cipher2);
  //tag
    mpz_t an;
    mpz_init(an);
    mpz_init(nsquare);
   // mpz_mul(an, a, pub_n);
    mpz_mul(nsquare, pub_n, pub_n);
    element_pow_mpz(temp_pow,u, plain1->m); 
    element_mul(temp_pow, temp_pow, h);
    element_pow_zn(sig1, temp_pow, secret_key);
    element_printf("\n signature of plain = %B\n", sig1);  

    //mpz_mul(an, b, pub_n);
   // mpz_mul(nsquare, pub_n, pub_n);
    element_pow_mpz(temp_pow,u, b); 
    element_mul(temp_pow, temp_pow, h);
    element_pow_zn(sig2, temp_pow, secret_key);
    element_printf("\n signature of b = %B\n", sig2);  
   
   //element_printf("\nb = %Zd\n", b);
   fclose(fplain);
     mpz_add(a, a, b);
   //  mpz_mod(a, a, pub_n);
  // mpz_mul(a, a, pub_n);
  // mpz_mod(a, a, nsquare);
   count = 2;
   element_pow_mpz(temp_pow,u, a);
   mpz_set_ui(data2, count);
  //  itoa(count, len, 10);+
    //element_printf(" \nh = %B\n", h);
    element_pow_mpz(h, h, data2);
    element_mul(temp_pow, temp_pow, h);
    //element_printf("\n h. u^bN = %B\n", temp_pow);
    element_pow_zn(sig3, temp_pow, secret_key);
    element_printf("\n sig 3 %B\n", sig3); 
    element_mul(g2, g2, g1);
    element_printf("\n Direct Product %B\n", g2); 
    element_mul(sig2, sig1, sig2);
    element_printf("\n Direct Product %B\n", sig2); 
   
 return 0;
}



