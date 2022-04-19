#include "block_tree.h"


int main(){
    Block* tab[6];
    CellTree* nodes[6];
    int i;
    for(i = 0 ; i < 6 ; i ++){
        char name[256];
        sprintf(name,"ecriture_bloc_%d.txt",i);
        tab[i] = read_block(name);
        nodes[i] =  create_node(tab[i]);
    }

    CellTree* racine = nodes[0];
    add_child(racine,nodes[1]);
    add_child(racine,nodes[2]);
    add_child(nodes[2],nodes[3]);
    add_child(nodes[2],nodes[4]);
    add_child(nodes[4],nodes[5]);

   
    print_tree(racine);

    CellTree* lastNode = last_node(racine);
    char* tmp = hast_to_str(nodes[5]->block->hash);
    printf("Résultat attendu\nLast_node = %d\n",tmp);
    
    tmp = lastNode->block->hash;
    printf("Résultat obtenu\nLast_node = %d\n",tmp);


    CellProtected* liste = fusion_arbre(racine);
    printf("Liste la plus longue obtenue dans l'abre : \n");
    print_list_protected(liste);

    delete_tree(racine);      
}

    
