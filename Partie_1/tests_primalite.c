/*--- Préambule ---*/
#include "tests_primalite.h"
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define M_MAX 1000
#define A 10
#define N 3


/*Implémentation par une méthode naive*/
/*Test naif de primalité*/
int is_prime_naive(long p){
    int i;
    for(i = 3 ; i < p ; i++){
        if(p%i==0){         //un i compris entre 3 et p-1 divise p, donc il n'est pas premier
            return 0;        //Donc on retourne 0
        }
    }
    return 1;               //On n'a trouvé aucun diviseurs, p est donc premier.
}

/*Exponentiation modulaire rapide*/

/*Version naïve, de grande complexité*/

long modpow_naive(long a, long m, long n){
	long res = 1;
	for (int i=0; i<m; i++){
		res *= a;
		res = res%n;
	}
	return res;
}

/*Version plus efficace de modpow, récursive, procédant par élévation au carré*/


long modpow(long a, long m, long n){
	if (m==0){
		printf("Valeur de m non possible ! m > 0");
		return 1%n;
	}
	if (m == 1){
		return a%n;
	}else{
		if (m%2 == 0){
			long b = modpow(a,m/2,n);
            printf("Valeur de b à l'étape %ld : %ld\n",m,b);
			return (b*b)%n;
		}else{
			long b = modpow(a, ((m-1)/2) , n);
            printf("Valeur de b à l'étape %ld : %ld\n",m,b);
			return ((a*b%n)*b)%n;
		}
	}
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
    return rand() % ( up - low +1 ) + low ;
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
        a = rand_long (2 , p -1) ;
        if ( witness (a ,b ,d , p ) ) {
            return 0;
        }
    }
    return 1;
}

/*Génération de nombres premiers*/
long pow_2(int pow){
	long res = 1;
	for (int i = 1; i<=pow; i++){
		res = res*2;
	}return res;
}

long random_prime_number(int low_size, int up_size, int k){
	long low = pow_2(low_size);
	long up = pow_2(up_size)-1;

	long p = rand_long(low,up);
	int cpt = 0;
	while (!is_prime_miller(p,k) && cpt<1000){
		p = rand_long(low,up);
		cpt++;
	}
	if (is_prime_miller(p,k)){
		return p;
	}else{
		printf("Aucun nombre premier pour %d essais",cpt);
		return -1;
	}

}
