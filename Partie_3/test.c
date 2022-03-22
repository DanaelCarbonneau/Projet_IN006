#include<stdio.h>
#include"chaine_cle.h"

int main(){

    printf("c'est la 1 ?\n");
    CellKey* chaine = read_public_keys("../Partie_2/candidates.txt");

    printf("C'et la 2 ?\n");
    print_list_keys(chaine);

    printf("C'est la 3?\n");
    delete_list_keys(chaine);
}