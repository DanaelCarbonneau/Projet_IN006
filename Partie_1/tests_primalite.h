#include <stdio.h>
#include <math.h>

/*Fonction calculant de manière naïve si p est est premier (en testant s'il est divisible par tous les entiers inférieurs)*/
int is_prime_naive(long p);

/*retourne si a est un témoin de p (test de Miller)*/
int witness ( long a , long b , long d , long p );

/*retourne si p est un nombre premier (test de Miller)*/
int is_prime_miller ( long p , int k );