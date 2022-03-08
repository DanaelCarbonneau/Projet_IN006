#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"gestion_clef.h"
#include "tests_primalite.h"


void init_key(Key* key, long val, long n){
    /*Vérification de l'allocation*/
    if(key == NULL){
        printf("Erreur, la clé n'a pas été allouée !\n");
        return;
    }

    /*Initialisation des champs*/
    key->val = val;
    key->n = n;
}

void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size){
    /*On déclare les variables qui iront dans les clés*/
    long u;
    long s; 
    long n;

    /*Variables pour la génération de clés*/
    long p = random_prime_number(low_size,up_size,5000);        //test de miller répété 5000 fois
    long q = random_prime_number(low_size,up_size,5000);
    while ( p == q ) {
        q = random_prime_number (3 ,7 , 5000);
    }

    generate_keys_values (p ,q ,&n ,&s ,&u) ;               //On génère les valeurs des clés selon le protocole RSA
    //Pour avoir des cles positives :
    if (u <0) {
        long t = (p -1) *( q -1) ;                      //(lignes 33 à 36 directement tirés du main fourni dans l'énoncé de la partie 1)
        u = u + t ; //on aura toujours s*u mod t = 1
    }

    /*On peut maintenant intialiser les valeurs de nos deux clés*/
    init_key(pKey,s,n);
    init_key(pKey,u,n);

}

char* key_to_str(Key* key){

    if(key = NULL){
        printf("Erreur : clé vide!\n");
        return NULL;
    }

    int taille_chaine;
    int taille_val;
    int taille_n;
    long val = key->val;        //On récupère les valeurs de la clé afin de savoir la taille nécessaire pour la chaîne à allouer
    long n = key->n;

    while ((val >0) || (n>0)){
        
        if(val>0){
            taille_val++;
            val = val/10;           //Division par 10 pour savoir combien de chiffres sont présents dans val
        }
        
        if (n>0){
            taille_n++;
            n = n/10;               //Division par 10 pour savoir combien de chiffres sont présents dans val
        }
        
    }

    /*On peut calculer la taille de la chaine (x,y) et l'allouer : trois caractères, le caractère d'arrêt, et les chiffres de x et y*/
    taille_chaine = 4 + taille_val + taille_n;
    char* chaine_res = malloc(taille_chaine*sizeof(char));

    /*On écrit au bon format dans chaine_res*/
    sprintf(chaine_res,"(%lx,%lx)",key->val,key->n);

    /*On peut retourner la chaîne*/
    return chaine_res;    
}

Key* str_to_key(char* str){
    /*On déclare les deux variables servant à récupérer nos valeurs*/
    long val;
    long n;

    /*On récupère et vérifie le formattage*/

    if(sscanf(str,"(%lx,%lx)",&val,&n)!=2){
        printf("Erreur d'affichage !!\n");
    }

    /*On alloue la clé et on intialise ses valeurs*/
    Key* cle_res = malloc(sizeof(cle_res));
    init_key(cle_res,val,n);

    return cle_res;
}