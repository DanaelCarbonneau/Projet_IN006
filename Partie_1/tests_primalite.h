#ifndef TEST_PRIMALITEH
#define TEST_PRIMALITEH

#include <stdio.h>
#include <math.h>

/*Fonction calculant de manière naïve si p est est premier (en testant s'il est divisible par tous les entiers inférieurs)*/
int is_prime_naive(long p);

/*Fonction calculant (a^m)%n de manière naïve*/
long modpow_naive(long a, long m, long n);

/*Fonction calculant (a^m)%n*/
unsigned long modpow(long a, long m, long n);

/*retourne si a est un témoin de p (test de Miller)*/
int witness ( long a , long b , long d , long p );

/*retourne si p est un nombre premier (test de Miller)*/
int is_prime_miller ( long p , int k );

/*Fonction permettant de se donner 2^pow*/
long pow_2(int pow);

/*Fonction tentant de trouver un nombre premier d'une certaine taille*/
long random_prime_number(int low_size, int up_size, int k);

#endif
