#ifndef BLOCK_TREEH
#define BLOCK_TREEH

#include "block.h"

typedef struct block_tree_cell {
    Block * block ;
    struct block_tree_cell * father ;
    struct block_tree_cell * firstChild ;
    struct block_tree_cell * nextBro ;
    int height ;
} CellTree ;


/*Fonction permettant de créer un noeud et de l'initialiser avec une hauteur égale à 0 et une valeur égale à b*/
CellTree* create_node(Block* b);

/*Fonction permettant de mettre à jour la hauteur du nœud father quand un de ses fils a été modifié : la hauteur du nœud doit 
être égale au max entre sa hauteur courante et la hauteur du nœud son + 1. Elle retourne 1 si la hauteur a été changée, 0 sinon*/
int update_height(CellTree* father, CellTree* child);

/*Fonction qui ajoute un fils à un nœud en mettant à jour la hauteur de tous les ascendants*/
void add_child(CellTree* father, CellTree* child);

/*Fonction qui affiche un arbre, pour chaque nœud, elle affiche la hauteur et la valeur hachée du block
Le parcours est fait en profondeur. La fonction est à la fois récursive et itérative pour accéder à tout l'arbre.*/
void print_tree(CellTree* ab);

/*Fonction qui supprime le nœud node en utilisant la fonction delete_block (voir block.c)*/
void delete_node(CellTree* node);

/*Fonction qui supprime un arbre ab*/
void delete_tree(CellTree* ab);


/*Fonction qui retourne un pointeur vers le noeud fils avec la plus grande hauteur*/
CellTree* highest_child(CellTree* cell);


/*Fonction qui retourne la cellule du dernier nœud de la plus longue branche de tree*/
CellTree* last_node(CellTree*tree);



/*Fonction permettant de fusionner deux listes simplement chaînées de protected l1 et l2*/
CellProtected* fusion_liste_protected(CellProtected* l1, CellProtected* l2);

/*Fonction qui retourne la liste chaînée de déclarations chaînées obtenue en fusionnant celles de tous les blocks du plus long fils*/
CellProtected* fusion_arbre(CellTree* tree);

#endif