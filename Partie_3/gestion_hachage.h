#ifndef GESTION_HACHAGE
#define GESTION_HACHAGE

#include<stdio.h>
#include<stdlib.h>


#include"../Partie_2/signature.h"
#include"../Partie_2/gestion_clef.h"
#include"chaine_cle.h"
#include"chaine_protected.h"

typedef struct hashcell {
    Key * key ;
    int val ;
} HashCell ;

typedef struct hashtable {
    HashCell ** tab ;
    int size ;
} HashTable ;

/*Fonction qui alloue une cellule de la table de hachage et initialise ses champs aux valeurs key et 0*/

HashCell* create_hashcell(Key* key);


/*Fonction qui retourne la position d'un élément dans la table de hachage*/
int hash_function(Key* key, int size);



#endif