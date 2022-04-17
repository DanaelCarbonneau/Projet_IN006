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

    
    child->nextBro = father->firstChild;
    father->firstChild = child;

    CellTree* father_cour = father;
    CellTree* child_cour = child;
    
    while( (father_cour) && (update_height(father_cour,child_cour)) ){
        child_cour = father_cour;
        father_cour = father_cour->father;
        
    }
    
}


void print_tree(CellTree* ab){
    if(ab==NULL){
        return;
    }

    char* s = hash_to_str(ab->block->hash);
    printf("\n%s\t hauteur : %d\n",s,ab->height);
    free(s);
    print_tree(ab->firstChild);

    CellTree* courant = ab->nextBro;
    while(courant){
        s = hash_to_str(courant->block->hash);
        printf("\n%s\t hauteur : %d\n",s,courant->height);
        free(s);

        print_tree(courant->firstChild);
        courant = courant->nextBro;
    }

}





void delete_node(CellTree* node){
    delete_block(node->block);
    free(node);
}




void delete_tree(CellTree* ab){
    printf("====\nAppel avec %d\n", ab);
    if(ab==NULL){
        return;
    }

    CellTree* tmp = ab->firstChild;
    CellTree* courant = ab->nextBro;
    CellTree* a_supprimer;

    delete_node(ab);
    delete_tree(tmp);
    while(courant){
        a_supprimer = courant;
        tmp = courant->firstChild;
        courant = courant->nextBro;
        
        delete_node(a_supprimer);
        delete_tree(tmp);
    }

}



#if 0
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
                delete_tree(frere_courant->firstChild);
				delete_node(frere_courant);
				frere_courant = tmp;
			}
		}
	}	
}
#endif 






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

