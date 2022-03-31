#include<stdio.h>
#include"chaine_cle.h"
#include"chaine_protected.h"
#include"gestion_hachage.h"

/*Taille des tables de hachage*/
#define SIZE_C 20
#define SIZE_V 2000


int main(){
    /*Création des listes chainées selon fichiers de la partie 2*/
    CellKey* chaine_cle_candidats = read_public_keys("../Partie_2/candidates.txt");
    CellKey* chaine_cle_votants = read_public_keys("../Partie_2/keys.txt");
    CellProtected* chaine_pr = read_protected("../Partie_2/declarations.txt");

    /*Affichage si besoin*/
    #if 0
    print_list_keys(chaine_cle_candidats);
    print_list_protected(chaine_pr);
    #endif

    supprimer_fausses_declarations(chaine_pr);

     /*Affichage si besoin*/
    #if 0
    print_list_protected(chaine_pr);
    #endif

    /*trouver le gagnant de l'élection*/
    Key* gagnant = compute_winner(chaine_pr, chaine_cle_candidats, chaine_cle_votants, SIZE_C, SIZE_V);
    char* kts = key_to_str(gagnant);
    printf("Le gagnant est : %s\n",kts);

    /*Liberer la mémoire*/
    free(kts);
    delete_list_keys(chaine_cle_candidats);
    delete_list_keys(chaine_cle_votants);
    delete_list_protected(chaine_pr);
    
}
