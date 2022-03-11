#ifndef GESTION_VOTANTS_CANDIDATSH
#define GESTION_VOTANTS_CANDIDATSH

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"gestion_clef.h"
#include"signature.h"

/*Structure représentant un votant par sa clé et un flag indiquant s'il est candidat*/
typedef struct _votant{
    Key* pKey;
    Key* sKey;
    int est_candidat;
}Votant;



/*Fonction permettant de générer un fichier avec nv votants ainsi qu'un tableau les listant*/
Votant* generation_fichier_votants(int nv);

/*Fonction permettant de libérer un tableau de votants*/
void liberer_votants(Votant* tabV, int nv);


/*Fonction générant un fichier, et un tableau de nc votants à partir d'un tableau de candidats. Un candidat est représenté
par une clé, chaque case du tableau pointe donc sur un candidat*/
Key** generation_fichier_candidats(int nc, Votant*tabV,int nv);

/*Fonction émettant un protected représentant le vote d'un Votant electeur pour un candidat tiré aléatoirement dans tabC*/
Protected* emission_vote(Votant electeur, Key** tabC,int nc);



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

#endif
