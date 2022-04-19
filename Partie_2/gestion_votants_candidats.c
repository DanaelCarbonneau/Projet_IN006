#include"gestion_votants_candidats.h"



Votant* generation_fichier_votants(int nv){
    FILE* fichier_votant = fopen("keys.txt","w");

    if(fichier_votant==NULL){
        printf("Erreur à l'ouverture du fichier\n");
        return NULL;
    }

    /*On créé un tableau de nv couples de clés représentant nos nv votans*/

    Votant* tabV = (Votant*) malloc(nv* sizeof(Votant));

    /*remplissage du tableau et écriture dans le fichier*/
    for(int i = 0; i < nv ; i++){
        tabV[i].pKey = (Key*) malloc(sizeof(Key));
        tabV[i].sKey = (Key*) malloc(sizeof(Key));
        tabV[i].est_candidat = 0;
        init_pair_keys(tabV[i].pKey,tabV[i].sKey,10,12);                //On a augmenté la taille des clés afin d'éviter les doublons (plus de valeurs possibles) !

        char * ktsp = key_to_str(tabV[i].pKey);                         //Permet de gérer les fuites mémoires
        char * kt2s = key_to_str(tabV[i].sKey);

        fprintf(fichier_votant,"pKey : %s, sKey : %s\n",ktsp,kt2s);

        free(kt2s);
        free(ktsp);
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

    if(fichier_candidat==NULL){
        printf("Erreur à l'ouverture du fichier\n");
        return NULL;
    }

    Key** tabC = (Key**) malloc(nc * sizeof(Key*));

    if(tabC==NULL){
        printf("Erreur à l'allocation");
        return NULL;
    }

    for(int i = 0 ; i < nc ; i++){
        tirage = rand()%nv;             //On va sur une case aléatoire du tableau
        Votant candidat_potentiel = tabV[tirage];

        while(candidat_potentiel.est_candidat!=0){      //On vérifie que le votant choisi aléatoirement n'est pas déjà candidat
            tirage = rand()%nv;             //nc <= nv, il n'est donc pas possible que tous les votants soient déjà candidats lorsqu'on passe dans la boucle
            candidat_potentiel = tabV[tirage];
        }
        tabV[tirage].est_candidat = 1;           //Désormais le votant est candidat, on met à jour ses infos dans tabV.

        tabC[i] = candidat_potentiel.pKey;      //On stocke la clé publique du candidat

        char * kts = key_to_str(tabC[i]);               //Gestion de la mémoire

        fprintf(fichier_candidat,"pKey : %s\n",kts);

        free(kts);
    }

    fclose(fichier_candidat);
    return tabC;
}

Protected* emission_vote(Votant electeur, Key** tabC,int nc){
    /*On tire un vote au hasard*/
    int tirage = rand()%nc;
    char* declaration = key_to_str(tabC[tirage]);

    Protected* declaration_vote;

    /*On initialise tous les champs de notre protected*/

    Signature* sgn = sign(declaration,electeur.sKey);           //Gestion de la mémoire

    declaration_vote = init_protected(electeur.pKey,declaration,sgn);
    liberer_signature(sgn);    
    free(declaration);
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

    if(fichier_votes==NULL){
        printf("Erreur à l'ouverture du fichier\n");
        return;
    }
    
    char* pts;
    for(int i = 0; i < nv ; i++){
        Protected * vote = emission_vote(tabv[i],tabc,nc);

        pts = protected_to_str(vote);         //Gestion de la mémoire

        fprintf(fichier_votes,"%s\n",pts);

        free(pts);
        liberer_protected(vote);
    }

    fclose(fichier_votes);

    liberer_votants(tabv,nv);
    free(tabc);               //La mémoire allouée aux clés a été libérée dans liberer_votants


}
