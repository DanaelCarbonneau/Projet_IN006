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

/*Fonction qui affiche un arbre, pour chaque nœud, elle affiche la hauteur et la valeur hachée du block*/
void print_tree(CellTree* ab);

/*Fonction qui supprime le nœud node en utilisant la fonction delete_block (voir block.c)*/
void delete_node(CellTree* node);

/*Fonction qui supprime un arbre ab*/
void delete_tree(CellTree* ab);


#endif
