#include<stdio.h>
#include"chaine_cle.h"

int main(){

    CellKey* chaine_cle = read_public_keys("../Partie_2/candidates.txt");

    print_list_keys(chaine_cle);

    delete_list_keys(chaine_cle);
    
    CellProtected* chaine_pr = read_protected();
    
    print_list_protected(chaine_pr);
    
    delete_list_protected(chaine_pr);
    
}
