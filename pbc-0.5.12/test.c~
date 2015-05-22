#include <pbc/pbc.h>

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
    // declaring elements
    element_t C, g1, g2, g3;
   // element_init_G1(C, p);
    element_init_G1(g1, p);
    element_init_G1(g2, p);
    char *len;
    len = (char *) malloc(1000*sizeof(char));
    //element_init_G1(g3, p);
    pf = fopen("comp.txt", "r");
    fgets(len, 1000,pf);
    element_set_str(g1, len, 10);	
    fclose(pf);
    element_printf("g1 = %B\n\n", g1);
     pf = fopen("comp1.txt", "r");
    fgets(len, 1000,pf);
    element_set_str(g2, len, 10);	
    fclose(pf);
    element_printf("g2 = %B\n\n", g2);
    element_mul(g2, g2, g1);
    element_printf("prod = %B\n\n", g2);
    ///element_t a, b;
    //element_init_Zr(a, p);
    //element_init_Zr(b, p);
   
    //int i;
   // for(i = 0; i < 10; i++) {
        // randomizing elements
       // element_random(g1);
       // element_random(g2);
       // element_random(g3);
   
        //element_random(a);
        //element_random(b);
   
        // g1 <- g1 ^ a
        //element_pow_zn(g1, g1, a);
        // g2 <- g2 ^ b
        //element_pow_zn(g2, g2, b);
   
        // C <- g1^a  *  g2^b
        //element_mul(C, g1, g2);

        // C <- g1^a  *  g2^b  * g3
        //element_mul(C, C, g3);
   /*
        element_printf("g1 = %B\n", g1);
        element_printf("g2 = %B\n", g2);
	
        char buf1[element_length_in_bytes(g1)], buf2[element_length_in_bytes(g2)];
        element_to_bytes(buf1, g1);
	element_to_bytes(buf2, g2);
        pf = fopen("comp.txt", "w");
        
        element_fprintf(pf, "%s", buf1);
        fclose(pf); 
         pf = fopen("comp1.txt", "w");
        
        element_fprintf(pf, "%s", buf2);
        fclose(pf);
	element_mul(g2, g2, g1);
         element_printf("prod = %B\n", g2);
       // element_from_bytes(C, buf);
        //element_printf("C = %B\n\n", C);
   // }
   
   */   
   // element_clear(C);
    element_clear(g1);
   // element_clear(g2);
    //element_clear(g3);
    //element_clear(a);
    //element_clear(b);
   
    pairing_clear(p);
   
    return 0;
}
