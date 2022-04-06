#ifndef BLOCKEH
#define BLOCKEH
#include<openssl/sha.h>
#include<stdio.h>
#include<string.h>
#include"../Partie_3/chaine_protected.h"

typedef struct block {
    Key * author ;
    CellProtected * votes ;
    unsigned char * hash ;
    unsigned char * previous_hash ;
    int nonce ;
} Block ;

/*Fonction permettant d'écrire dans un fichier un block*/
void write_block(char* nom_fichier,Block*b);

/*Fonction permettant de lire un block dans un fichier*/
Block* read_block(char*nom_fichier);

/*Fonction retournant la valeur hashée correspondant à la chaîne s selon le protocole SHA256*/
unsigned char* hash_function_SHA256(const char* s);

/*Fonction transformant un block en chaîne de caractères*/
char* block_to_str(Block* B);

/*Fonction qui vérifie qu'il y a d 0 successifs au début de la valeur hachée passée en paramètre*/

int verifie_nb_d(unsigned char* hash,int d);

/*Fonction qui incrémente l'attribut nonce de B jusqu'à ce que la valeur hashée commence par d 0 successifs*/
void compute_proof_of_work(Block *B, int d);


#endif