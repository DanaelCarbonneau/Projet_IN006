#ifndef GESTION_CLEH
#define GESTION_CLEH

#include<stdio.h>
#include<stdlib.h>

typedef struct _key{
    long val;
    long n;
}Key;

/*Fonction permettant d'initaliser les valeurs d'une clé déjà allouée*/
void init_key(Key* key, long val, long n);

/*Fonction permettant d'initialiser une paire de clés pKey et sKey (déjà allouées) à l'aide du protocole RSA 
(entre les dimensions de low_size et up_size*/
void init_pair_keys(Key* pKey, Key* sKey, int low_size, int up_size);

/*Fonction qui permet de passer d'une variable de type Key à sa représentation sous forme de chaîne de caractères de forme 
(x,y) où x et y sont les deux entiers de la clé exprimés en hexadécimal*/
char* key_to_str(Key* key);

/*Fonction qui permet de passer d'une chaîne de caractères de forme (x,y) à une variable de type Key où les champs val et n
sont initialisés aux valeurs x et y*/
Key* str_to_key(char* str);


#endif