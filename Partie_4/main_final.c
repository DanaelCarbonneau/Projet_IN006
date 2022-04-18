#include <stdio.h>
#include <stdlib.h>
#include<dirent.h>
#include<openssl/sha.h>



/* IDENFITIFICATION ACTUELLE DU PROBLÈME : DANS ADD CHILD LE PÈRE NE BOUCLE PAS*/
#include "block.h"
#include "gestion_vote_block.h"


#include "../Partie_2/gestion_votants_candidats.h"
#include "../Partie_2/gestion_clef.h"
#include "../Partie_3/chaine_cle.h"
#include "../Partie_3/chaine_protected.h"


#define D 2
#define VOTANTS 50
#define CANDIDATS 5
#define NB_VOTE_PAR_BLOCK 5

int main(){
    
        DIR * rep = opendir ( "../Blockchain/") ;
    if ( rep != NULL ) {
        struct dirent * dir ;

        while (( dir = readdir ( rep ) ) ) {
            
            if ( strcmp( dir->d_name, "." ) !=0 && strcmp(dir->d_name , ".." ) !=0) {
                remove(dir->d_name);
            }
        }
        closedir ( rep ) ;
    }


    generate_random_data(VOTANTS, CANDIDATS);
    CellProtected* liste_decl = read_protected("declarations.txt");
    CellKey* liste_cles_c = read_public_keys("candidates.txt");
    CellKey* liste_cles_v = read_public_keys("keys.txt");

    //print_list_keys(liste_cles_c);
    //print_list_keys(liste_cles_v);
    //print_list_protected(liste_decl);

    /*Soumission des votes et création des blocks*/
    CellProtected* cour_pr = liste_decl;
    int cpt = 1;
    CellTree* res_tree = NULL;
    Key* k_auteur_public = (Key*) malloc(sizeof(Key));
    Key* k_auteur_prive = (Key*) malloc(sizeof(Key));
    init_pair_keys(k_auteur_public,k_auteur_prive,3,7);

    while (cour_pr){
        submit_vote(cour_pr->data);
        
        if (cpt%NB_VOTE_PAR_BLOCK == 0){
            create_block(res_tree, k_auteur_public,2);
            char name[256];
            sprintf(name,"B%d.txt",cpt/NB_VOTE_PAR_BLOCK);
            add_block(2, name);
        }

        
            res_tree = read_tree();
        
      
        cpt++;
        cour_pr = cour_pr->next;
    }

printf("\n\n================\n\nAffichage final de l'arbre\n");

    print_tree(res_tree);
    

    Key* gagnant = compute_winner_BT(res_tree,liste_cles_c,liste_cles_v,CANDIDATS,VOTANTS);
    printf("\n\n====\nLe gagnant est : %s\n", key_to_str(gagnant));

    


    free(k_auteur_public);
    free(k_auteur_prive);
}
