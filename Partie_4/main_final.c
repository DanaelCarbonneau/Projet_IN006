#include <stdio.h>
#include <stdlib.h>
#include<openssl/sha.h>



/* IDENFITIFICATION ACTUELLE DU PROBLÈME : DANS ADD CHILD LE PÈRE NE BOUCLE PAS*/
#include "block.h"
#include "gestion_vote_block.h"


#include "../Partie_2/gestion_votants_candidats.h"
#include "../Partie_2/gestion_clef.h"
#include "../Partie_3/chaine_cle.h"
#include "../Partie_3/chaine_protected.h"


#define D 2
#define VOTANTS 5
#define CANDIDATS 2

int main(){
    generate_random_data(VOTANTS, CANDIDATS);
    CellProtected* liste_decl = read_protected("declarations.txt");
    CellKey* liste_cles_c = read_public_keys("candidates.txt");
    CellKey* liste_cles_v = read_public_keys("keys.txt");

    printf("Affichage des clés \n");
    print_list_keys(liste_cles_c);
    print_list_keys(liste_cles_v);
    printf("Passage\n");
    print_list_protected(liste_decl);
    printf("Sortie_print\n");

    /*Soumission des votes et création des blocks*/
    CellProtected* cour_pr = liste_decl;
    int cpt = 1;
    CellTree* res_tree = NULL;
    Key* k_auteur_public = (Key*) malloc(sizeof(Key));
    Key* k_auteur_prive = (Key*) malloc(sizeof(Key));
    init_pair_keys(k_auteur_public,k_auteur_prive,3,7);

    printf("Avant parcourt des décla\n");
    while (cour_pr){
        submit_vote(cour_pr->data);
        
        
        if (cpt%10 == 0){
            create_block(res_tree, k_auteur_public, D);
            char name[256];
            sprintf(name,"B%d.txt",cpt/10);
            add_block(D, name);         
        }
        
        cpt++;
        cour_pr = cour_pr->next;
        printf("Passage dans la boucle\n");
    }
    printf("Avant read_tree\n");
    CellTree* tree_commun = read_tree();
    printf("Après read_tree\n");
    print_tree(tree_commun);

    Key* gagnant = compute_winner_BT(tree_commun,liste_cles_c,liste_cles_v,CANDIDATS,VOTANTS);
    printf("Le gagnant est : %s", key_to_str(gagnant));

    free(k_auteur_public);
    free(k_auteur_prive);
}
