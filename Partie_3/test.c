#include<stdio.h>
#include"chaine_cle.h"
#include"chaine_protected.h"

/*==========================ATTENTION==========================

Les fuites mémoires subsitant dans le code de ce test proviennent du même problème que celui énoncé dans le fichier test.c
de la partie 2 (se référer aux explications précédentes).


===============================================================*/

int main(){
    /*Création des listes chainées selon fichiers de la partie 2*/
    CellKey* chaine_cle_candidats = read_public_keys("../Partie_2/candidates.txt");
    CellKey* chaine_cle_votants = read_public_keys("../Partie_2/declarations.txt");
    CellProtected* chaine_pr = read_protected();
    
    /*Affichage si besoin*/
    #if 0
    print_list_keys(chaine_cle_candidats);
    print_list_protected(chaine_pr);
    #endif

    print_list_protected(chaine_pr);

     /*Affichage si besoin*/
    #if 0
    print_list_protected(chaine_pr);
    #endif
    
    /*Liberer la mémoire*/
    delete_list_keys(chaine_cle_candidats);
    delete_list_keys(chaine_cle_votants);
    delete_list_protected(chaine_pr);
    
}
