#include <string.h>
#include "paillier.c"

int main(int argc, char **argv) {

 FILE  *fpairing, *fcipher, *ftag, *fpub, *fkey, *frand; 
 mpz_t pub_n;
 char* len;
 int count = 0, val=80000, no_copies=3;
 mpz_t dval, tag, g;
  mpz_init(g);
  mpz_init(dval);
  mpz_set_ui(dval, val);
 long int key_int;
 paillier_ciphertext_t *cipher, *cipher_test;
 paillier_plaintext_t *plain;
 paillier_pubkey_t *pub;
 paillier_prvkey_t *priv;
 paillier_get_rand_t get_rand;
// pairing_init_set_str(pairing, param_str);
 
 mpz_t           randNum, rnd,rnd_sum, c, cn;      /* Hold our random numbers */
 mpz_t           rndBnd, temp;       /* Bound for mpz_urandomm */
 mpz_t key, key1;		//key for PRF
 gmp_randstate_t gmpRandState; /* Random generator state object */
 mpz_init(rnd);
 //mpz_init(rndno);
 mpz_init(rndBnd);
 mpz_init(randNum);
 mpz_init(rnd_sum);
 mpz_init(key);
 mpz_init(c);
 mpz_init(temp);
 mpz_set_ui(c, val);
 mpz_set(rndBnd, dval);
 //gmp_randinit_default(gmpRandState);
 
 mpz_init(pub_n);
 mpz_set_str(rnd_sum, "0", 10);
 cipher = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t)); 
 cipher_test = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));
 plain = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
 //element_init_G1(tag_prod, pairing);
 len = (char *)malloc(2048*sizeof(char));
 //setting already known pairing parameters
 
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
  fcipher = fopen("./result/cipher_result.txt", "r");
  fgets(len, 1000, fcipher);
  mpz_init_set_str(cipher->c, len, 10);
  fclose(fcipher);
  mpz_init(plain->m);
  
  
  ftag = fopen("./result/rsa_tag_result.txt", "r");
  fgets(len, 1000, ftag);
 // element_printf("\nsig from file %s\n", len);
  mpz_init_set_str(tag, len, 10);
  fclose(ftag);
  //element_printf("\nsignature %B", sig);
  fkey = fopen("prf_key.txt", "r");
  fgets(len, 1000, fkey);
  //fgets(len, 1000, fkey);
  fclose(fkey);
  //printf("\n orig key %s\n", len);
  mpz_set_str(key, len, 10);
  gmp_randseed(gmpRandState, key);
  int i;
  mpz_init(cn);
  mpz_mul(cn, c, pub->n);
  mpz_t temp_rnd, tmp, prod, pw;
  mpz_init(temp_rnd);
  mpz_init(tmp);
 // mpz_init(prod);
  mpz_init(pw);
  mpz_init_set_str(prod, "1", 10);
  mpz_init(cipher_test->c);
  frand = fopen("rand.txt", "r");
  for(i = 0; i< no_copies; i++)
   {
	fgets(len,1000, frand);
        mpz_set_str(tmp, len, 10);
        mpz_powm(tmp, tmp, pub->n, pub->n_squared);
        mpz_mul(prod, prod, tmp);
       
   }
  for(i = 0; i< no_copies; i++)
   {
       // fgets(len,1000, frand);
       // mpz_set_str(tmp, len, 10);
      //  mpz_powm(tmp, tmp, pub->n, pub->n_squared);
       // mpz_invert(tmp, tmp, pub->n);
       // mpz_mod(temp, cipher->c,tmp);
        //element_printf("\n val %Zd\n", temp);
	mpz_urandomm(randNum, gmpRandState, pub->n);
      //  mpz_mul(temp_rnd, cn, randNum);
       // mpz_powm(pw, tmp , temp_rnd, pub->n);
       // mpz_mul(prod, prod, tmp);
       // mpz_mod(prod, prod, pub->n_squared);
	mpz_add(rnd_sum, rnd_sum, randNum);
   }
   mpz_t t;
   mpz_init(t);
  // mpz_add_ui(t, c, 10000000); */
   mpz_powm(prod, prod, cn, pub->n);
   mpz_mod(t, cipher->c, prod);
   //element_printf("\n mod value %Zd \n", t); 
   mpz_invert(prod, prod, pub->n_squared);
   mpz_mul(cipher_test->c, cipher->c, prod);
   mpz_mod(cipher_test->c, cipher->c, pub->n_squared);
   if(!mpz_cmp(cipher_test->c, cipher->c))
   {
     printf("\n Test1 - verified");   
   } 
  // paillier_dec(plain, pub, priv, cipher);
  // element_printf("\nprod value %Zd\n", plain->m);
  fclose(frand);
  mpz_mod(rnd_sum, rnd_sum, pub->n);
  plain = paillier_dec_nomod(plain, pub, priv, cipher, rnd_sum);

  mpz_t user_tag;
  mpz_init(user_tag);
  if((fpub = fopen("generator.txt", "r")))
   {
     fgets(len, 1000, fpub);
     mpz_set_str(g, len, 10);
   }
  fclose(fpub);
  mpz_powm(user_tag, g, plain->m, pub->n);
  printf("\n");
   mpz_out_str(stdout, 10, user_tag);
  printf("\n tag: ");
      mpz_out_str(stdout, 10, tag);
 if(mpz_cmp(user_tag, tag))
  {
   printf("\nTest 2 --  Signature verifies\n");
  }
 else
  {
   printf("\n Test 2 Failed");
  }
  
}
