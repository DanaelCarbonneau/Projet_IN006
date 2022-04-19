#include <stdio.h>
#include <stdlib.h>

#include "block.h"
#include "../Partie_2/gestion_clef.h"
#include"../Partie_3/chaine_protected.h"

#define D_MAX 3


int main(){
  /*Creer le bloc*/
  Block* b = (Block*)malloc(sizeof(Block));
  Key* pkey_author = (Key*)malloc(sizeof(Key));
  Key* skey_author = (Key*) malloc(sizeof(Key));

  init_pair_keys(pkey_author,skey_author,10,12); //on se donne une clé dont on se fiche des valeurs ? 
  b->author = pkey_author;
  b->votes = read_protected("../Partie_2/declarations.txt");
  b->previous_hash = "J«»áÑyÂ«_y6{VÚÝºn³­öÏS";      //On a calculé une valeur de hachage précédemment qu'on a converti en chaîne de caractères
  b->nonce = 0;


  /*Comparer le temps mis pour lui donner une proof of work de 0 à D_MAX*/
  //generate_fichier_comparaison(b,D_MAX);
  compute_proof_of_work(b,D_MAX);

  /*Test d'écriture et lecture dans un fichier*/
  write_block("ecriture_bloc.txt",b);

  Block* b_bis = read_block("ecriture_bloc.txt");

  if (b_bis == NULL){
    printf("Erreur de lecture du bloc!");
  }else{
    char * s_hash = hash_to_str(b_bis->hash);
    char * s_prev = hash_to_str(b_bis->previous_hash);    
    char * kts = key_to_str(b_bis->author);
    
    printf("La clé : %s \nLe hash : %s \nLe previous hash : %s \nLe nonce : %d \tLes votes : \n",kts,s_hash,s_prev,b_bis->nonce);
    free(s_hash);
    free(s_prev);
    free(kts);
    print_list_protected(b_bis->votes);
  }
  printf("Validité du bloc bis : %d\n",verify_block(b_bis,D_MAX-1));
  free(b_bis->author);
  delete_block(b_bis);      //Fuites mémoires issues du fait que le block ne supprime pas les valeurs des protected, volontaire pour nos tests


  /*Libération mémoire*/

  free(b->author);

 // free(b->hash);
  delete_list_protected(b->votes);
  free(b);
}

