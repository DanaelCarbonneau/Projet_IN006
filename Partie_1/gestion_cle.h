#ifndef GESTION_CLEH
#define GESTION_CLEH

/*Fonction calculant PGDC(s,t) et les deux long u, v tels que s ×u + t × v = PGCD(s, t)*/
long extended_gcd ( long s , long t , long *u , long * v );


/*Fonction générant la clé publique pkey(s,n) et la clé secrète skey(u,n) 
à partir des deux longs premiers p et q (valeurs de s,u,n changées par adresse*/
void generate_key_values(long p, long q, long* n, long* s, long* u);



#endif