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

/* ́fonction permettant d’afficher une liste chainée de cles LCK*/
void print_list_keys(CellKey* LCK);

/*Fonction  qui supprime une cellule de liste c*/
void delete_cell_key(CellKey* c);

/*Fonction qui supprime une liste chainée de clées LCK*/
void delete_list_keys(CellKey*LCK);


#endif