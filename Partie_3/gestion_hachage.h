#ifndef GESTION_HACHAGEH
#define GESTION_HACHAGEH

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

/*Fonction permettant de comparer deux clés*/
int compare_cles(Key* k1, Key* k2);

/*Fonction permettant de trouver la position où se situe l'élément de clé donnée, ou la position où il aurait du être*/
int find_position(HashTable* t, Key* key);

/*Fonction permettant de créer une table de hachage de taille donnée et d'y placer les clés de la liste donnée*/
HashTable* create_hashtable(CellKey* keys, int size);

/*Fonction permettant de libérer toute la mémoire associée à une table de hachage*/
void delete_hashtable(HashTable* t);

/*Fonction qui va calculer, selon une table de hachage, qui est le candidat ayant le plus de voix (en cas d'égalité, ce sera le
premier candidat dans la table*/
Key* find_winner(HashTable* H_c);

/*Fonction calculant le vainqueur de l'élection étant donnés une liste de déclarations avec des signatures valides (decl),
une liste de candidats (candidates) et une liste de personnes autorisées à voter (voters)*/

Key* compute_winner(CellProtected* decl, CellKey* candidates, CellKey* voters, int sizeC, int sizeV);


#endif
