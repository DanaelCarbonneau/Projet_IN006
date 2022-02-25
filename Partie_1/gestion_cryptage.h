/*--- Préambule ---*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"tests_primalite.h"

#ifndef GESTION_CLEH
#define GESTION_CLEH

/*Fonction calculant PGDC(s,t) et les deux long u, v tels que s ×u + t × v = PGCD(s, t)*/
long extended_gcd ( long s , long t , long *u , long * v );


/*Fonction générant la clé publique pkey(s,n) et la clé secrète skey(u,n) 
à partir des deux longs premiers p et q (valeurs de s,u,n changées par adresse*/
void generate_key_values(long p, long q, long* n, long* s, long* u);

/*Fonction générant un tableau de long contenant la version codée du message m en fonction de la clé publique pkey(s,n)*/
long* encrypt(char* chaine, long s, long n);

/*Fonction permettant de décrypter un message passé en paramètre dans un tableau de long à partir de la clé privée skey(u,n)*/
char* decrypt(long* crypted, int size, long u, long n);

/*Fonction permettant d'afficher un tableau de long*/
void print_long_vector(long* result, int size);



#endif