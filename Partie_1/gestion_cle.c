/*--- Préambule ---*/
#include<stdio.h>
#include<math.h>
#include<tests_primalite.h>
#include<gestion_cle.h>

/*Fonction calculant PGDC(s,t) et les deux long u, v tels que s ×u + t × v = PGCD(s, t)*/
long extended_gcd ( long s , long t , long *u , long * v ) {
    if ( t == 0) {
        * u = 1;
        * v = 0;
        return s ;
    }
    long uPrim , vPrim ;
    long gcd = extended_gcd (t , s % t , & uPrim , & vPrim ) ;
    *u = vPrim;
    *v = uPrim - (s/t)*vPrim;
    return gcd;
}

/*Fonction générant la clé publique pkey(s,n) et la clé secrète skey(u,n) 
à partir des deux longs premiers p et q (valeurs de s,u,n changées par adresse*/
void generate_key_values(long p, long q, long* n, long* s, long* u){
    *n = p * q;
    long t = (p-1)*(q-1);
    long v;
    *s = rand()%t;
    while(extended_gcd(*s,t,u,&v)!=1){
        *s = rand()%t;
    }
}


