/*
	libpaillier - A library implementing the Paillier cryptosystem.

	Copyright (C) 2006 SRI International.

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful, but
	WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	General Public License for more details.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include "paillier.h"
#include <time.h>
clock_t startm, stopm;
#define START if ( (startm = clock()) == -1) {printf("Error calling clock");exit(1);}
#define STOP if ( (stopm = clock()) == -1) {printf("Error calling clock");exit(1);}
#define PRINTTIME printf( "%6.3f seconds used by the processor.", ((double)stopm-startm)/CLOCKS_PER_SEC);


void
init_rand( gmp_randstate_t rand, paillier_get_rand_t get_rand, int bytes )
{
	void* buf; 
        FILE *fp;
      	mpz_t s;

	buf = malloc(bytes);
	paillier_get_rand_devurandom(buf, bytes);

	gmp_randinit_default(rand);
	mpz_init(s);
	mpz_import(s, bytes, 1, 1, 0, 0, buf);
	gmp_randseed(rand, s);
        mpz_clear(s);

	free(buf);
}

void
complete_pubkey( paillier_pubkey_t* pub )
{
	mpz_mul(pub->n_squared, pub->n, pub->n);
	mpz_add_ui(pub->n_plusone, pub->n, 1);
}

void
complete_pubkey1( paillier_pubkey_t* pub )
{
	mpz_mul(pub->n_squared, pub->n, pub->n);
//	mpz_add_ui(pub->n_plusone, pub->n, 1);
}
void
complete_prvkey( paillier_prvkey_t* prv, paillier_pubkey_t* pub )
{
	mpz_powm(prv->x, pub->n_plusone, prv->lambda, pub->n_squared);
	mpz_sub_ui(prv->x, prv->x, 1);
	mpz_div(prv->x, prv->x, pub->n);
	mpz_invert(prv->x, prv->x, pub->n);
}

void
paillier_keygen( paillier_pubkey_t** pub,
								 paillier_prvkey_t** prv,
								 paillier_get_rand_t get_rand, int modulusbits)
{
	mpz_t p;
	mpz_t q;
	gmp_randstate_t rand;
	mpz_init(p);
	mpz_init(q);
	/* allocate the new key structures */
        if(modulusbits != 0)
        {		
	 *pub = (paillier_pubkey_t*) malloc(sizeof(paillier_pubkey_t));
	 *prv = (paillier_prvkey_t*) malloc(sizeof(paillier_prvkey_t));
	  mpz_init((*pub)->n_plusone);
	}
	else
	{
		mpz_init_set(p,(*pub)->p);
		mpz_init_set(q,(*pub)->q);
	}

	/* initialize our integers */

	mpz_init((*pub)->n);
	mpz_init((*pub)->n_squared);
	mpz_init((*prv)->lambda);
	mpz_init((*prv)->x);
	

	/* pick random (modulusbits/2)-bit primes p and q */
      if(modulusbits != 0)
       {		
		init_rand(rand, get_rand, modulusbits / 8 + 1);
		do
		{
			do
				mpz_urandomb(p, rand, modulusbits / 2);
			while( !mpz_probab_prime_p(p, 10) );

			do
				mpz_urandomb(q, rand, modulusbits / 2);
			while( !mpz_probab_prime_p(q, 10) );

			/* compute the public modulus n = p q */
			
			mpz_mul((*pub)->n, p, q);
			mpz_init_set((*pub)->p, p);
			mpz_init_set((*pub)->q, q);
		 } while( !mpz_tstbit((*pub)->n, modulusbits - 1) );
		complete_pubkey(*pub);
		(*pub)->bits = modulusbits;
	}
	else
	{
	       //printf("inside else part");
		mpz_mul((*pub)->n, (*pub)->p, (*pub)->q);
		mpz_mul((*pub)->n_squared, (*pub)->n, (*pub)->n);
	}

	/* compute the private key lambda = lcm(p-1,q-1) */
     	
	mpz_sub_ui(p, p, 1);
	mpz_sub_ui(q, q, 1);
	mpz_lcm((*prv)->lambda, p, q);
 	complete_prvkey(*prv, *pub);
	/* clear temporary integers and randstate */

	mpz_clear(p);
	mpz_clear(q);
	if(modulusbits != 0)
	gmp_randclear(rand);
}

paillier_ciphertext_t*
paillier_enc(paillier_tag* tag, paillier_ciphertext_t* res,
							paillier_pubkey_t* pub,
							paillier_plaintext_t* pt,
							paillier_get_rand_t get_rand, int no_copies, mpz_t* rand_prf)
{
	mpz_t r;
	gmp_randstate_t rand;
	mpz_t x, one;
       // char val = '1';  
	/* pick random blinding factor */

	mpz_init(r);
        mpz_init_set_str(one, "1", 10);
	//printf("\npubbits : %d \n", pub->bits);
 	init_rand(rand, get_rand, pub->bits / 8 + 1);
	

	/* compute ciphertext */
	
	/*if( !res )
	{
		res = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));
		mpz_init(res->c);
	} */
	//printf("\n calculating enc");
        mpz_t t;
    	mpz_init(x);
        mpz_init(t);
        mpz_set(tag->t, pt->m);
         mpz_mul(t, pub->n, pt->m);

	int j;
      for(j=0; j < no_copies; j++)
       {  
        do
		mpz_urandomb(r, rand, pub->bits);
	while( mpz_cmp(r, pub->n) >= 0 );
        mpz_mul(r, r, rand_prf[j]);
        mpz_mod(r, r, pub->n);
	mpz_powm(x, r, pub->n, pub->n_squared);
	mpz_init(res[j].c);
	//printf("\n power %d", j );
        mpz_add(res[j].c, one, t);
	//mpz_powm(res[j].c, pub->n_plusone, pt->m, pub->n_squared);
	mpz_mul(res[j].c, res[j].c, x);
//printf("\n multiply");
	mpz_mod(res[j].c, res[j].c, pub->n_squared);
       }	
//printf("\n mod");
     	mpz_clear(x);
//printf("\n clear");
	mpz_clear(r);
        gmp_randclear(rand);
	return res;
}


paillier_ciphertext_t*
paillier_enc_orig( paillier_ciphertext_t* res,
							paillier_pubkey_t* pub,
							paillier_plaintext_t* pt,
							paillier_get_rand_t get_rand )
{
	mpz_t r;
	gmp_randstate_t rand;
	mpz_t x;

	/* pick random blinding factor */

	mpz_init(r);
 	init_rand(rand, get_rand, pub->bits / 8 + 1);
	do
		mpz_urandomb(r, rand, pub->bits);
	while( mpz_cmp(r, pub->n) >= 0 );

	/* compute ciphertext */
	
	if( !res )
	{
		res = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));
		mpz_init(res->c);
	}

	mpz_init(x);
	mpz_powm(res->c, pub->n_plusone, pt->m, pub->n_squared);
	mpz_powm(x, r, pub->n, pub->n_squared);

	mpz_mul(res->c, res->c, x);
	mpz_mod(res->c, res->c, pub->n_squared);

	mpz_clear(x);
	mpz_clear(r);
  gmp_randclear(rand);

	return res;
}



paillier_plaintext_t*
paillier_dec( paillier_plaintext_t* res,
							paillier_pubkey_t* pub,
							paillier_prvkey_t* prv,
							paillier_ciphertext_t* ct )
{
	if( !res )
	{
		res = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
		mpz_init(res->m);
	}
//	mpz_out_str(stdout, 10, ct->c);
	mpz_powm(res->m, ct->c, prv->lambda, pub->n_squared);
//	printf("\ndecryption\n");
//	mpz_out_str(stdout, 10, res->m);
	mpz_sub_ui(res->m, res->m, 1);
//	printf("\ndecryption\n");
//	mpz_out_str(stdout, 10, res->m);
	mpz_div(res->m, res->m, pub->n);
//	printf("\ndecryption\n");
//	mpz_out_str(stdout, 10, res->m);
	mpz_mul(res->m, res->m, prv->x);
//	printf("\ndecryption\n");
//	mpz_out_str(stdout, 10, res->m);
	//mpz_mod(res->m, res->m, pub->n);
//	printf("\ndecryption\n");
//	mpz_out_str(stdout, 10, res->m);
	return res;
}

paillier_plaintext_t*
paillier_dec_nomod( paillier_plaintext_t* res,
							paillier_pubkey_t* pub,
							paillier_prvkey_t* prv,
							paillier_ciphertext_t* ct, mpz_t inv)
{
	if( !res )
	{
		res = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
		mpz_init(res->m);
	}
         mpz_invert(inv, inv, pub->n);
         mpz_powm(res->m, ct->c, inv, pub->n_squared);

	mpz_powm(res->m, res->m, prv->lambda, pub->n_squared);
	mpz_sub_ui(res->m, res->m, 1);
        mpz_div(res->m, res->m, pub->n);
    //    mpz_div(res->m, res->m, prv->lambda);
        mpz_mul(res->m, res->m, prv->x);
        mpz_mod(res->m, res->m, pub->n);   
       // mpz_mul(res->m, res->m, inv);
       // mpz_mod(res->m, res->m, pub->n);    
	return res;
}


void
paillier_mul( paillier_pubkey_t* pub,
						 	paillier_ciphertext_t* res,
						 	paillier_ciphertext_t* ct0,
						 	paillier_ciphertext_t* ct1 )
{
	mpz_mul(res->c, ct0->c, ct1->c);
	mpz_mod(res->c, res->c, pub->n_squared);
}

void
paillier_exp( paillier_pubkey_t* pub,
							paillier_ciphertext_t* res,
							paillier_ciphertext_t* ct,
							paillier_plaintext_t* pt )
{
	mpz_powm(res->c, ct->c, pt->m, pub->n_squared);
}

paillier_plaintext_t*
paillier_plaintext_from_ui( unsigned long int x )
{
	paillier_plaintext_t* pt;
	
	pt = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
	mpz_init_set_ui(pt->m, x);
	
	return pt;
}

paillier_plaintext_t*
paillier_plaintext_from_bytes( void* m, int len )
{
	paillier_plaintext_t* pt;

	pt = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
	mpz_init(pt->m);
	mpz_import(pt->m, len, 1, 1, 0, 0, m);

	return pt;
}

void*
paillier_plaintext_to_bytes( int len,
														 paillier_plaintext_t* pt )
{
	void* buf0;
	void* buf1;
	size_t written;

	buf0 = mpz_export(0, &written, 1, 1, 0, 0, pt->m);

 	if( written == len )
 		return buf0;

	buf1 = malloc(len);
	memset(buf1, 0, len);

	if( written == 0 )
		/* no need to copy anything, pt->m = 0 and buf0 was not allocated */
		return buf1;
	else if( written < len )
		/* pad with leading zeros */
		memcpy(buf1 + (len - written), buf0, written);
	else
		/* truncate leading garbage */
		memcpy(buf1, buf0 + (written - len), len);

	free(buf0);

	return buf1;
}

paillier_plaintext_t*
paillier_plaintext_from_str( char* str )
{
	return paillier_plaintext_from_bytes(str, strlen(str));
}

char*
paillier_plaintext_to_str( paillier_plaintext_t* pt )
{
	char* buf;
	size_t len;

	buf = (char*) mpz_export(0, &len, 1, 1, 0, 0, pt->m);
	buf = (char*) realloc(buf, len + 1);
	buf[len] = 0;

	return buf;
}

paillier_ciphertext_t* 
paillier_ciphertext_from_bytes( void* c, int len )
{
	paillier_ciphertext_t* ct;

	ct = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));
	mpz_init(ct->c);
	mpz_import(ct->c, len, 1, 1, 0, 0, c);

	return ct;
}

void* 
paillier_ciphertext_to_bytes( int len,
															paillier_ciphertext_t* ct )
{
	void* buf;
	int cur_len;

	cur_len = mpz_sizeinbase(ct->c, 2);
	cur_len = PAILLIER_BITS_TO_BYTES(cur_len);
	buf = malloc(len);
	memset(buf, 0, len);
	mpz_export(buf + (len - cur_len), 0, 1, 1, 0, 0, ct->c);

	return buf;
}

char*
paillier_pubkey_to_hex( paillier_pubkey_t* pub )
{
	return mpz_get_str(0, 16, pub->n);
}

char*
paillier_prvkey_to_hex( paillier_prvkey_t* prv )
{
	return mpz_get_str(0, 16, prv->lambda);
}

paillier_pubkey_t*
paillier_pubkey_from_hex( char* str )
{
	paillier_pubkey_t* pub;

	pub = (paillier_pubkey_t*) malloc(sizeof(paillier_pubkey_t));
	mpz_init_set_str(pub->n, str, 16);
	pub->bits = mpz_sizeinbase(pub->n, 2);
	mpz_init(pub->n_squared);
	mpz_init(pub->n_plusone);
	complete_pubkey(pub);

	return pub;
}

paillier_prvkey_t*
paillier_prvkey_from_hex( char* str, paillier_pubkey_t* pub )
{
	paillier_prvkey_t* prv;

	prv = (paillier_prvkey_t*) malloc(sizeof(paillier_prvkey_t));
	mpz_init_set_str(prv->lambda, str, 16);
	mpz_init(prv->x);
	complete_prvkey(prv, pub);

	return prv;
}

void
paillier_freepubkey( paillier_pubkey_t* pub )
{
	mpz_clear(pub->n);
	mpz_clear(pub->n_squared);
	mpz_clear(pub->n_plusone);
	free(pub);
}

void
paillier_freeprvkey( paillier_prvkey_t* prv )
{
	mpz_clear(prv->lambda);
	mpz_clear(prv->x);
	free(prv);
}

void
paillier_freeplaintext( paillier_plaintext_t* pt )
{
	mpz_clear(pt->m);
	free(pt);
}

void
paillier_freeciphertext( paillier_ciphertext_t* ct )
{
	mpz_clear(ct->c);
	free(ct);
}

void
paillier_get_rand_file( void* buf, int len, char* file )
{
	FILE* fp;
	void* p;

	fp = fopen(file, "r");

	p = buf;
	while( len )
	{
		size_t s;
		s = fread(p, 1, len, fp);
		p += s;
		len -= s;
	}

	fclose(fp);
}

void
paillier_get_rand_devrandom( void* buf, int len )
{
	paillier_get_rand_file(buf, len, "/dev/random");
}

void
paillier_get_rand_devurandom( void* buf, int len )
{
	paillier_get_rand_file(buf, len, "/dev/urandom");
}

paillier_ciphertext_t* 
paillier_create_enc_zero()
{
	paillier_ciphertext_t* ct;

	/* make a NON-RERANDOMIZED encryption of zero for the purposes of
		 homomorphic computation */

	/* note that this is just the number 1 */

	ct = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));
	mpz_init_set_ui(ct->c, 1);

	return ct;
}

/*int main(int argc, char *argv[])
{	
	FILE *fp1, *fp2, *fp3, *fp4;//, *fp5, *fp6, *fp7;
	paillier_pubkey_t *pub;
	paillier_prvkey_t *priv;
	paillier_get_rand_t get_rand;
	paillier_plaintext_t *plain, *pt;
	paillier_ciphertext_t *cipher;
	plain = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
	pt = (paillier_plaintext_t*) malloc(sizeof(paillier_plaintext_t));
	cipher = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));
	mpz_init(plain->m);
	mpz_init(cipher->c);
	mpz_init(pt->m);
	paillier_keygen(atoi(argv[2]), &pub, &priv, get_rand);
	
	if(!(fp1 = fopen(argv[3], "w"))) 
	{
			fputs("not possible to write to ciphertext file!\n", stderr);
			exit(1);
	}
	if(!(fp2 = fopen(argv[4], "r"))) 
	{
			fputs("not possible to read from plaintext file!\n", stderr);
			exit(1);
	}
	gmp_fscanf(fp2, "%Zd\n", plain->m);
	if(!(fp3 = fopen(argv[5], "w"))) 
	{
			fputs("not possible to read from public key file!\n", stderr);
			exit(1);
	}
	if(!(fp4 = fopen(argv[6], "w"))) 
	{
			fputs("not possible to read from public key file!\n", stderr);
			exit(1);
	}

	
	paillier_enc( cipher, pub,plain,get_rand);
	pt = paillier_dec(pt, pub,priv, cipher);
	gmp_fprintf(fp1, "%Zd\n", cipher->c);
	gmp_fprintf(fp3, "%Zd\n", pt->m);
	gmp_fprintf(fp4, "%Zd\n", pub->n);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
        

  return 0;
}
*/
