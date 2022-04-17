#include "block_tree.h"


int main(){
    Block* lu = read_block("ecriture_bloc.txt");
    Block* fils_ajoute =(Block*) malloc(sizeof(Block));
    CellTree* noeud = create_node(lu);
    fils_ajoute->author = NULL;
    fils_ajoute->hash = "fuck";
    fils_ajoute->previous_hash = lu->hash;
    fils_ajoute->votes = NULL;

    CellTree* nf = create_node(fils_ajoute);
    add_child(noeud, nf);
    
    CellTree* nf2 = create_node(lu);
    CellTree* nf3 = create_node(lu);

    add_child(noeud,nf2);
    add_child(nf,nf3);
   
    print_tree(noeud);

    

    printf("Highest_child = %s, sa hauteur : %d\n",hash_to_str(nf->firstChild->block->hash),nf->firstChild->height);

    printf("Highest_child = %s\n",hash_to_str(highest_child(noeud)->block->hash));


    delete_tree(noeud);


}

    