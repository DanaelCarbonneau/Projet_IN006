#ifndef CHAINE_PRH
#define CHAINE_PRH

#include<stdio.h>
#include<stdlib.h>


#include"../Partie_2/signature.h"


//Structure utilisée
typedef struct cellProtected {
    Protected * data ;
    struct cellProtected * next ;
} CellProtected ;


/*Fonction créant une cellule de la liste chaînée à partir d'un protected pr*/
CellProtected* create_cell_protected(Protected* protected);

/*Fonction ajoutant une cellule contenant le protected pr en tête de la liste chainée liste*/
CellProtected* ajoutEnTete_protected(Protected* pr, CellProtected* liste);


/*Fonction permettant de lire dans un fichier des protected et d'en créer une liste chainée*/
CellProtected* read_protected(char* name);


/* ́fonction permettant d’afficher une liste chainée de protected LCP*/
void print_list_protected(CellProtected* LCP);

/*Fonction  qui supprime une cellule de liste de protected c*/
void delete_cell_protected(CellProtected* c);

/*Fonction qui supprime une liste chainée de protected LCP*/
void delete_list_protected(CellProtected* LCP);

/*Fonction qui supprime les fausses déclarations présentes dans une liste chainée de protected LCP*/
CellProtected* supprimer_fausses_declarations(CellProtected* LCP);





#endif
