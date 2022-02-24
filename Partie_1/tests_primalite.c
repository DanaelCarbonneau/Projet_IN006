/*--- Préambule ---*/
#include <stdio.h>
#include <math.h>


int is_prime_naive(long p){
    int i;
    for(i = 3 ; i < p ; i++){
        if(i%p==0){         //un i compris entre 3 et p-1 divise p, donc il n'est pas premier
            return 0;        //Donc on retourne 0
        }
    }
    return 1;               //On n'a trouvé aucun diviseurs, p est donc premier.
}