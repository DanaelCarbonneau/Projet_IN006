#include <stdio.h>
#include <stdlib.h>
#include<dirent.h>
#include<openssl/sha.h>
#include <time.h>


#include "gestion_vote_block.h"


#include "../Partie_2/gestion_votants_candidats.h"
#include "../Partie_2/gestion_clef.h"
#include "../Partie_3/chaine_cle.h"
#include "../Partie_3/chaine_protected.h"
#include "../Partie_4/block.h"

#define D 2
#define VOTANTS 1000
#define CANDIDATS 5
#define NB_VOTE_PAR_BLOCK 50

int main(){

    srand(time(NULL));
    int choix;
    printf("Voulez vous tous les affichages ?\n");
    scanf("%d",&choix);
    
    DIR * rep = opendir ( "../Blockchain/") ;

    if(rep == NULL){
        printf("Erreur d'ouverture du dossier\n");
        return 0;
    }

    struct dirent * dir ;

        while (( dir = readdir ( rep ) ) ) {
            
            if ( strcmp( dir->d_name, "." ) !=0 && strcmp(dir->d_name , ".." ) !=0) {
                remove(dir->d_name);
            }
        }
   
    generate_random_data(VOTANTS, CANDIDATS);
    CellProtected* liste_decl = read_protected("declarations.txt");
    CellKey* liste_cles_c = read_public_keys("candidates.txt");
    CellKey* liste_cles_v = read_public_keys("keys.txt");

    if(choix){
        printf("\nAffichage des clés des candidats\n");
        print_list_keys(liste_cles_c);
        printf("\nAffichage des clés des votants\n");
        print_list_keys(liste_cles_v);
        printf("\nAffichage des déclarations\n");
        print_list_protected(liste_decl);
    }
    /*Soumission des votes et création des blocks*/
    CellProtected* cour_pr = liste_decl;
    int cpt = 1;
    CellTree* res_tree = NULL;
    Key* k_auteur_public = (Key*) malloc(sizeof(Key));
    Key* k_auteur_prive = (Key*) malloc(sizeof(Key));
    init_pair_keys(k_auteur_public,k_auteur_prive,3,7);

    CellTree* tempo;
    int cpt_b = 0;
    char name[256];
    while (cour_pr){
        submit_vote(cour_pr->data);
        
        if (cpt%NB_VOTE_PAR_BLOCK == 0){
            create_block(res_tree, k_auteur_public,D);
            sprintf(name,"B%d.txt",cpt_b);
            add_block(D, name);
            tempo = res_tree;
            delete_tree(tempo);
            res_tree = read_tree();
            cpt_b++;
            
        }

        cpt++;
        cour_pr = cour_pr->next;
    }

    if(fopen("Pending_votes.txt","r")){       //Cas où il reste des voix dans pending votes (pas un multiple du nombre de voix par blocs)
        create_block(res_tree,k_auteur_public,D);
        sprintf(name,"B%d.txt",cpt_b);
        add_block(D, name);
        tempo = res_tree;
            delete_tree(tempo);
            res_tree = read_tree();
    }
    
            


printf("\n\n================\n\nAffichage final de l'arbre\n");

    print_tree(res_tree);
   

    Key* gagnant = compute_winner_BT(res_tree,liste_cles_c,liste_cles_v,CANDIDATS,VOTANTS);
    char * s = key_to_str(gagnant);
    printf("\n\n====\nLe gagnant avec l'utilisation d'une blockchain est : %s\n", s);
    free(s);


    printf("\n====\nVérification de notre résultat\n");
   
    Key* gagnant_2 = compute_winner(liste_decl,liste_cles_c,liste_cles_v,CANDIDATS,VOTANTS);
    s = key_to_str(gagnant_2);
    printf("Le gagnant selon la méthode centralisée est : %s\n",s);
    free(s);
    
    

    
    delete_list_keys(liste_cles_c);
    delete_list_keys(liste_cles_v);
    delete_list_protected(liste_decl);




    closedir(rep);
    free(k_auteur_public);
    free(k_auteur_prive);
}
