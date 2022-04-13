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

int update_height(CellTree* father, CellTree* child){
	if ((child->height + 1) > father->height){
		father->height = child->height + 1;
		return 1;
	} return 0;
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

void print_tree(CellTree* ab){
	if (ab == NULL){
		printf("L'arbre est vide !");
	}	
	printf("hauteur = %d, hash = %s", ab->height, hash_to_str(ab->block->hash));
	CellTree* fils_courant = ab->firstChild;
	CellTree* frere_courant;
	while (fils_courant){
		printf("hauteur = %d, hash = %s", fils_courant->height, hash_to_str(fils_courant->block->hash));
		frere_courant = fils_courant->nextBro;
		while (frere_courant){
			printf("hauteur = %d, hash = %s", frere_courant->height, hash_to_str(frere_courant->block->hash));
			frere_courant = frere_courant->nextBro;
		}
		fils_courant = fils_courant->firstChild;
	}
}

void delete_node(CellTree* node){
    delete_block(node->block);
    free(node);
}

void delete_tree(CellTree* ab){
	if (ab != NULL){	
		CellTree* fils_courant = ab->firstChild;
		CellTree* frere_courant;
		CellTree* tmp;
		delete_node(ab);
		while (fils_courant){
			tmp = fils_courant->firstChild;
			frere_courant = fils_courant->nextBro;
			delete_node(fils_courant);
			fils_courant = tmp;
			while (frere_courant){
				tmp = frere_courant->nextBro;	
				delete_node(frere_courant);
				frere_courant = tmp;
			}
		}
	}	
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



CellProtected* fusion_liste_protected(CellProtected* l1, CellProtected* l2){
	if (l1 == NULL){
		return l2;
	}
	CellProtected* cour = l1;
	while (cour->next){
		cour = cour->next;
	}
	cour->next = l2;
	return l1;
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

