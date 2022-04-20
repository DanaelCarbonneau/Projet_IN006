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

    char*s = hash_to_str(ab->block->hash);
    printf("%s\thauteur = %d\n",s,ab->height);
    free(s);

    print_tree(ab->firstChild);
    print_tree(ab->nextBro);
}





void delete_node(CellTree* node){
    /*On ajoute ici les libérations qu'on ne peut pas faire quand le block n'est pas lu car ce n'est jamais le cas pour des arbres (dans nos tests, et 
    en pratique, c'est la manière à privilégier pour de la saisie*/
    free(node->block->author);
    free(node->block->hash);
    free(node->block->previous_hash);
    delete_block(node->block);
    free(node);
}




void delete_tree(CellTree* ab){
    if(ab==NULL){
        return;
    }

    
    

    delete_tree(ab->firstChild);
    delete_tree(ab->nextBro); 
    delete_node(ab);
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

