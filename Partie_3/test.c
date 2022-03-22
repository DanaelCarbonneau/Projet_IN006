#include<stdio.h>
#include"chaine_cle.h"

int main(){

    CellKey* chaine = read_public_keys("../Partie_2/candidates.txt");

    print_list_keys(chaine);

    delete_list_keys(chaine);
}
