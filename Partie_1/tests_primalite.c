/*--- Préambule ---*/
#include <stdio.h>
#include <math.h>
#include "tests_primalite.h"

/*Test naif de primalité*/
int is_prime_naive(long p){
    int i;
    for(i = 3 ; i < p ; i++){
        if(i%p==0){         //un i compris entre 3 et p-1 divise p, donc il n'est pas premier
            return 0;        //Donc on retourne 0
        }
    }
    return 1;               //On n'a trouvé aucun diviseurs, p est donc premier.
}




/*Test de Rabin-Miller*/

/*Teste si a est un témoin de Miller de p*/
int witness ( long a , long b , long d , long p ) {
    long x = modpow (a ,d , p ) ;
    if ( x == 1) {
        return 0;
    }
    for ( long i = 0; i < b ; i ++) {
        if ( x == p -1) {
            return 0;
        }
        x = modpow (x ,2 , p ) ;
    }
    return 1;
}

long rand_long ( long low , long up ) {
    return rand () % ( up - low +1) + low ;
}

int is_prime_miller ( long p , int k ) {
    if ( p == 2) {
        return 1;
    }
    if (!( p & 1) || p <= 1) { //on verifie que p est impair et different de 1
        return 0;
    }
    //on determine b et d :
    long b = 0;
    long d = p - 1;
    while (!( d & 1) ) { //tant que d n’est pas impair
        d = d /2;
        b = b +1;
    }
    // On genere k valeurs pour a, et on teste si c’est un temoin :
    long a ;
    int i ;
    for ( i = 0; i < k ; i ++) {
        a = randlong (2 , p -1) ;
        if ( witness (a ,b ,d , p ) ) {
            return 0;
        }
    }
    return 1;
}
