

#include"gestion_votants_candidats.h"


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
    FILE* fichier_candidat = fopen("candidates.txt","w");

    Key** tabC = (Key**) malloc(nc * sizeof(Key*));

    for(int i = 0 ; i < nc ; i++){
        tirage = rand()%nv;             //On va sur une case aléatoire du tableau
        Votant candidat_potentiel = tabV[tirage];

        while(candidat_potentiel.est_candidat!=0){      //On vérifie que le votant choisi aléatoirement n'est pas déjà candidat
            tirage = rand()%nv;             //nc <= nv, il n'est donc pas possible que tous les votants soient déjà candidats lorsqu'on passe dans la boucle
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

void generate_random_data(int nv, int nc){
    
    if(nv < nc){
        printf("Trop de candidats demandés par rapport aux votants, il y aura donc nv candidats.\n");
        nc = nv;
    }
    Votant* tabv = generation_fichier_votants(nv); 
    Key** tabc = generation_fichier_candidats(nc,tabv,nv);

    FILE* fichier_votes = fopen("declarations.txt","w");

    for(int i = 0; i < nv ; i++){
        Protected * vote = emission_vote(tabv[i],tabc,nc);
        char* chaine = protected_to_str(vote);
        fprintf(fichier_votes,"%s",chaine);

        free(vote->mess);
        free(vote);
        free(chaine);
    }

    fclose(fichier_votes);

    liberer_votants(tabv,nv);
    free(tabc);                 //La mémoire allouée aux clés a été libérée dans liberer_votants



}