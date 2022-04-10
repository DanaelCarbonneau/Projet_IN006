#ifndef BLOCKEH
#define BLOCKEH
#include<openssl/sha.h>
#include<stdio.h>
#include<string.h>
#include"../Partie_3/chaine_protected.h"
#include<time.h>

typedef struct block {
    Key * author ;
    CellProtected * votes ;
    unsigned char * hash ;
    unsigned char * previous_hash ;
    int nonce ;
} Block ;

/*Fonction permettant d'écrire dans un fichier un block*/
void write_block(char* nom_fichier,Block*b);

/*Fonction permettant de lire un block dans un fichier. Attention : lorsqu'on lit le block, la mémoire est dynamique pour 
les valeurs de hachage, il faut donc ne pas oublier de les libérer !*/
Block* read_block(char*nom_fichier);

/*Fonction permettant d'obtenir une chaîne de caractères au bon format (hexadécimal) pour nos valeurs de hachage*/
char* hash_to_str(unsigned char * hash);

/*Fonction permettant de transformer une chaîne de caractères contenant la valeur de hachage au format hexadécimal
en une valeur de hachage dans un tableau de unsigned char*/
unsigned char * str_to_hash(char* st);

/*Fonction retournant la valeur hashée correspondant à la chaîne s selon le protocole SHA256*/
unsigned char* hash_function_SHA256(const char* s);

/*Fonction transformant un block en chaîne de caractères*/
char* block_to_str(Block* B);

/*Fonction qui vérifie qu'il y a d 0 successifs au début de la valeur hachée passée en paramètre*/
int verifie_nb_d(unsigned char* hash,int d);

/*Fonction qui incrémente l'attribut nonce de B jusqu'à ce que la valeur hashée commence par d 0 successifs*/
void compute_proof_of_work(Block *B, int d);

/*Fonction qui vérifie qu'un block est valide, c'est à dire ???*/
int verify_block(Block* b, int d);

/*Fonction qui permet de générer un fichier donnant pour chaque d entre 0 et nb_max_d le temps nécessaire pour obtenir une valeur hachée avec d 0*/
void generate_fichier_comparaison(Block* b,int nb_d_max);

#endif
