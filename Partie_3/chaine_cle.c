
#include"chaine_cle.h"



void print_list_keys(CellKey* LCK){
    CellKey* courant = LCK;
    while (courant){
        printf("%s",key_to_str(courant->data));
        courant = courant->next;
    }
}



void delete_cell_key(CellKey* c){
    free(c->data);
    free(c);
}



/*Fonction qui supprime une liste chainée de clées LCK*/
void delete_list_keys(CellKey*LCK){
    CellKey* courant = LCK;
    while (courant){
        courant = LCK;
        LCK = LCK->next;
        delete_cell_key(courant);
    }    
}
