#ifndef GESTION_V_BLOCKH
#define GESTION_V_BLOCKH

#include<dirent.h>
#include<string.h>
#include"block_tree.h"


#include"../Partie_3/gestion_hachage.h"
#include"../Partie_3/chaine_cle.h"

/*Fonction qui permet d'ajouter le vote déclaré par p à la fin du fichier Pending_votes.txt*/
void submit_vote(Protected* p);

/*Fonction qui lit tous les blocks contenus dans un répertoire, et les stocke dans un tableau de CellTree, puis reconstruit l'arbre*/
CellTree* read_tree();

/*Fonction qui créé un block avec les informations passées en paramètres*/
void create_block(CellTree* tree, Key* author, int d);

/*Fonction qui vérifie que le bloc représenté par le fichier ”Pending block” est valide. Si c’est le cas, la fonction 
crée un fichier appelé name représentant le bloc, puis l’ajoute dans le répertoire ”Blockchain”*/
void add_block(int d, char* name);

/*Fonction qui vérifie si un nœud a bien pour père pere vis à vis des valeurs de hachage (previous_hash et hash)*/
int estFils(CellTree* noeud, CellTree* pere);

/*Fonction qui permet de  lire un répertoire contenant des fichiers .txt contenant des blocks et le transforme en un
arbre*/
CellTree* read_tree();

/*Fonction qui permet d'extraire d'un arbre la liste des déclarations protected contenues dans la plus longue chaîne*/
CellProtected* extraction_protected(CellTree* ab);


/*Fonction permettant de délibérer sur le résultat de l'élection correspondant aux données passées en paramètres*/
Key* compute_winner_BT(CellTree* tree, CellKey* candidates, CellKey* voters, int sizeC, int sizeV);



#endif
