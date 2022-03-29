#include<stdio.h>
#include"chaine_cle.h"


/*==========================ATTENTION==========================

Les fuites mémoires subsitant dans le code de ce test proviennent du même problème que celui énoncé dans le fichier test.c
de la partie 2 (se référer aux explications précédentes).


===============================================================*/

int main(){
    CellKey* chaine_cle = read_public_keys("../Partie_2/candidates.txt");

   
    
    print_list_keys(chaine_cle);

    delete_list_keys(chaine_cle);
   
    CellProtected* chaine_pr = read_protected();
    
    print_list_protected(chaine_pr);

    chaine_pr = supprimer_fausses_declarations(chaine_pr);
    

    print_list_protected(chaine_pr);
    
    delete_list_protected(chaine_pr);
    
}
