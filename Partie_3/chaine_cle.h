#ifndef CHAINE_CLEH
#define CHAINE_CLEH

#include<stdio.h>
#include<stdlib.h>


#include"../Partie_2/gestion_clef.h"


//Structure utilisée
typedef struct cellKey {
    Key * data ;
    struct cellKey * next ;
} CellKey ;


/*Fonction créant une cellule de la liste chaînée à partir d'une clé Key*/
CellKey* create_cell_key(Key* key);

/*Fonction ajoutant une cellule contenant la clé key en tête de la liste chainée liste*/
CellKey* ajoutEnTete(Key* key, CellKey* liste);


/*Fonction permettant de lire dans un fichier des clés et d'en créer une liste chainée*/
CellKey* read_public_keys(char* nom_fichier);


/* ́fonction permettant d’afficher une liste chainée de cles LCK*/
void print_list_keys(CellKey* LCK);

/*Fonction  qui supprime une cellule de liste c*/
void delete_cell_key(CellKey* c);

/*Fonction qui supprime une liste chainée de clées LCK*/
void delete_list_keys(CellKey*LCK);




#endif