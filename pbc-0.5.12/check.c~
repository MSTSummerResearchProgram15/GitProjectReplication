#include "include/pbc.h"
#include "include/pbc_test.h"

static const char* param_str = "type f \
q 205523667896953300194896352429254920972540065223 \
r 205523667896953300194895899082072403858390252929 \
b 40218105156867728698573668525883168222119515413 \
beta 115334401956802802075595682801335644058796914268 \
alpha0 191079354656274778837764015557338301375963168470 \
alpha1 71445317903696340296199556072836940741717506375";

int main() {
    // declaring pairing parameters
    pairing_t p;
    pairing_init_set_str(p, param_str);
    FILE *pf;
    char *len;
    mpz_t n, a, b;
    // declaring elements
    element_t C, g1, g2, u, h, g, secret_key, temp_pow, public_key, sig1, sig2;
   // element_init_G1(C, p);
    mpz_init(n);
    mpz_init(a);
    mpz_init(b);
    element_init_G1(g1, p);
    element_init_G1(sig1, p);
    element_init_G1(sig2, p);
    element_init_G1(u, p);
    element_init_G1(h, p);
    element_init_G2(g, p);
    element_init_G1(temp_pow, p);
   // element_init_G1(sig, p);
    element_init_G1(g2, p);
    element_init_G2(public_key, p);
    //element_init_G1(g3, p);
     element_init_Zr(secret_key, p);
    len = (char *) malloc(1000 * sizeof(char));
    
   
        char buf[element_length_in_bytes(g1)];
        
        pf = fopen("./tag/output5.txt", "r");
        fgets(buf, 1000, pf);
      //  element_from_bytes(g1, buf);
        element_set_str(g1, buf, 10);
        element_printf("g1 = %B\n", g1);
        fclose(pf);
	//char buf1[element_length_in_bytes(g2)];
        
        pf = fopen("./tag/output6.txt", "r");
        fgets(buf, 1000, pf);
        element_set_str(g2, buf, 10);
        element_printf("g2 = %B\n", g2);
        fclose(pf);

	element_mul(g2, g2, g1);
	element_printf("g2 = %B\n", g2);

	pf = fopen("pairing.txt", "r");
	fgets(len, 1000, pf);
	//printf("\n %s\n", len);
   	element_set_str(g, len, 10);
	element_printf(" g = %B\n", g);
	fgets(len, 1000, pf);
	//printf("\n %s\n", len);
   	element_set_str(u, len, 10);
	element_printf("\n u= %B\n", u);
	fgets(len, 1000, pf);
	element_set_str(secret_key, len, 10);
	element_printf(" secretkeuy %B\n",secret_key);
	fgets(len, 1000, pf);
	//element_set_str(public_key, len, 10);
  //      element_printf(" publickey %B\n", public_key);
	fgets(len, 1000, pf);
	element_set_str(h, len, 10);
        element_printf(" \nh = %B\n", h);
	fgets(len, 1000, pf);
	mpz_init_set_str(n, len, 10); 
        printf(" \n n = ");
        mpz_out_str(stdout, 10, n);
	fclose(pf);
 
	pf = fopen("./split/output5.txt", "r");
        fgets(len, 1000, pf);
        mpz_set_str(a, len, 10);
       	mpz_mul(a, a, n);
	element_pow_mpz(temp_pow,u, a);
	element_mul(temp_pow, h, temp_pow);
	element_pow_zn(sig1, temp_pow, secret_key);
	element_printf(" \n signature of a %B \n",temp_pow);
 fclose(pf);
	//char buf1[element_length_in_bytes(g2)];
        
       /* pf = fopen("./split/output6.txt", "r");
        fgets(len, 1000, pf);
        mpz_set_str(b, len, 10);
        fclose(pf);
        */
        //element_from_bytes(C, buf);
        //element_printf("C = %B\n\n", C);
   // }
   
   
   // element_clear(C);
    element_clear(g1);
   // element_clear(g2);
    //element_clear(g3);
    //element_clear(a);
    //element_clear(b);
   
    pairing_clear(p);
   
    return 0;
}
