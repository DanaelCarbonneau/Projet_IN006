#include "block_tree.h"


CellTree* create_node(Block* b){
    CellTree* res = (CellTree*) malloc(sizeof(CellTree));

    if(res == NULL){
        printf("Erreur à l'allocation de la cellule de l'arbre\n");
        return NULL;
    }

    res->block = b;
    res->height = 0;
    res->father = NULL;
    res->firstChild = NULL;
    res->nextBro = NULL;

    return res;
}

void add_child(CellTree* father, CellTree* child){
    child->father = father;

    if(father->firstChild == NULL){
        father->firstChild = child;
    }
    else{
        child->nextBro = father->firstChild;
        father->firstChild = child;
    }

    CellTree* father_cour = father;
    CellTree* child_cour = child;

    while( (father_cour) && (update_height(father_cour,child_cour)) ){
        child_cour = father_cour;
        father_cour = father_cour->father;
    }
}


void delete_node(CellTree* node){
    delete_block(node->block);
    free(node);
}



CellTree* highest_child(CellTree* cell){

    CellTree* cour = cell->firstChild;
    CellTree* res = cour;

    while(cour){
        if(res->height < cour->height){
            res = cour;
        }
        cour = cour->nextBro;
    }
    return res;
}

CellTree* last_node(CellTree* tree){

    if(tree->firstChild==NULL){     //Cas d'arrêt, on est à la feuille
        return tree;
    }
    else{
        return last_node(highest_child(tree));          //Fonction récursive terminale
    }
}


CellProtected* fusion_arbre(CellTree* tree){
    CellProtected* res = tree->block->votes;

    CellTree* courant = highest_child(tree);

    while(courant != NULL){
        res = fusion_liste_protected(courant->block->votes,res);            //Souvent, la liste de déclarations signées sera plus courte que res, donc on est potentiellement plus efficaces
        courant = highest_child(courant);       //Highest child nous permet de choisir le bon suivant dans le parcours, sa complexité dépend du nombre de frères
    }

    return res;
}

