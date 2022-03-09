#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"gestion_clef.h"
#include"Signature.h"

typedef struct _votant{
    Key* pKey;
    Key* sKey;
    int est_candidat;
    Protected* declaration_signee;
}Votant;




Votant* generation_fichier_votants(int nv){
    FILE* fichier_votant = fopen("keys.txt","w");

    /*On créé un tableau de nv couples de clés représentant nos nv votans*/

    Votant* tabV = (Votant*) malloc(nv* sizeof(Votant));

    /*remplissage du tableau et écriture dans le fichier*/
    for(int i = 0; i < nv ; i++){
        tabV[i].pKey = (Key*) malloc(sizeof(Key));
        tabV[i].sKey = (Key*) malloc(sizeof(Key));
        tabV[i].est_candidat = 0;
        init_pair_keys(tabV[i].pKey,tabV[i].sKey,3,7);
        fprintf(fichier_votant,"pKey : %s, sKey : %s\n",key_to_str(tabV[i].pKey),key_to_str(tabV[i].sKey));
    }

    fclose(fichier_votant);
    return tabV;
}

void liberer_votants(Votant* tabV, int nv){
    for(int i = 0 ; i < nv ; i++){
        free(tabV[i].pKey);
        free(tabV[i].sKey);        
    }
    free(tabV);
}

Key** generation_fichier_candidats(int nc, Votant*tabV,int nv){
    int tirage;
    
    if(nc > nv){
        printf("Il y a plus de candidats que de votants ! erreur ! Nous ne prendrons que nv candidats.\n");
        nc = nv;
    }
    FILE* fichier_candidat = fopen("candidates.txt","w");

    Key** tabC = (Key**) malloc(nc * sizeof(Key*));

    for(int i = 0 ; i < nc ; i++){
        tirage = rand()%nv;             //On va sur une case aléatoire du tableau
        Votant candidat_potentiel = tabV[tirage];

        while(candidat_potentiel.est_candidat!=0){      //On vérifie que le votant choisi aléatoirement n'est pas déjà candidat
            tirage = rand()%nv;             //La boucle termine bien car nc <= nv, il n'est donc pas possible que tous les votants soient déjà candidats lorsqu'on passe dans la boucle
            candidat_potentiel = tabV[tirage];
        }
        tabV[tirage].est_candidat = 1;           //Désormais le votant est candidat, on met à jour ses infos dans tabV.

        tabC[i] = &candidat_potentiel.pKey;      //On stocke la clé publique du candidat
        fprintf(fichier_candidat,"pKey : %s\n",key_to_str(tabC[i]));
    }

    fclose(fichier_candidat);
    return tabC;
}

Protected* emission_vote(Votant electeur, Key** tabC,int nc){
    /*On tire un vote au hasard*/
    int tirage = rand()%nc;
    char* declaration = key_to_str(tabC[tirage]);

    Protected* declaration_vote = (Protected*) malloc(sizeof(Protected));

    /*On initialise tous les champs de notre protected*/

    declaration_vote = init_protected(electeur.pKey,declaration,sign(declaration,electeur.sKey));
    return declaration_vote;
}



/*Fonction qui :
— génère nv couples de clés (publique, secrète) différents représentant les nv citoyens,
— crée un fichier keys.txt contenant tous ces couples de clés (un couple par ligne),
— sélectionne nc clés publiques aléatoirement pour définir les nc candidats,
— crée un fichier candidates.txt contenant la clé publique de tous les candidats (une clé publique
par ligne),
— génère une déclaration de vote signée pour chaque citoyen (candidat choisi aléatoirement),
— crée un fichier declarations.txt contenant toutes les déclarations signées (une déclaration
par ligne).*/
void generate_random_data(int nv, int nc);