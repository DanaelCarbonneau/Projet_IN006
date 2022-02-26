/*--- Préambule ---*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"tests_primalite.h"
#include"gestion_cryptage.h"

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


long* encrypt(char* chaine, long s, long n){
    //On va chercher la taille de la chaîne
    int taille_message = strlen(chaine);
    //On alloue le tableau qui réceptionnera le message codé
    long* coded = (long*) malloc(taille_message*sizeof(long));
    //On parcourt la chaîne pour la coder
    int i = 0;
    long m;
    for(i = 0; i < taille_message ; i++){
        m = (long)chaine[i];
        coded[i] = modpow(m,s,n);        //On code chaque lettre du message

    }
    //On peut alors retourner le message codé
    return coded;
}


char* decrypt(long* crypted, int size, long u, long n){
    //On alloue la chaîne qui sera retounée
    char* decoded = (char*) malloc((size+1)*sizeof(char));

    //On décode chaque lettre du tableau de long
    long cour;
    for(int i = 0; i < size ; i++){
        cour = crypted[i];
        decoded[i] = (char) modpow(cour,u,n); //formule donnée dans l'énoncé
    }
    printf("\n");

    //On met le caractère d'arret
    decoded[size] = '\0';

    //On peut retourner le message décodé.
    return decoded;
}

void print_long_vector(long* result, int size){
    printf("Vector : [");
    for (int i = 0; i < size ; i++){
        printf("%ld \t",result[i]);
    }
    printf("]\n");
}


