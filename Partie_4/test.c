#include <stdio.h>
#include <stdlib.h>

#include "block.h"
#include "../Partie_2/gestion_clef.h"
#include"../Partie_3/chaine_protected.h"

#define D_MAX 5

int main(){
  /*Creer le bloc*/
  Block* b = (Block*)malloc(sizeof(Block));
  Key* key_author = (Key*)malloc(sizeof(Key));

  init_key(key_author,3,7); //on se donne une clé dont on se fiche des valeurs ? 
  b->author = key_author;
  b->votes = read_protected("../Partie_2/declarations.txt");
  b->previous_hash = "0";

  /*Comparer le temps mis pour lui donner une proof of work de 0 à D_MAX*/
  generate_fichier_comparaison(b,D_MAX);
  
  #if 0
  /*Test d'écriture et lecture dans un fichier*/
  write_block("ecriture_bloc.txt",b);
  
  Block* b_bis = read_block("ecriture_bloc.txt");
  if (b_bis == NULL){
    printf("Erreur de lecture du bloc!");
  }else{
    printf("La clé : %s \tLe hash : %d \tLe previous hash : %d \tLe nonce : %d \tLes votes : \n",key_to_str(b_bis->author),b_bis->hash,b_bis->previous_hash,b_bis->nonce);
    print_list_protected(b_bis->votes);
  }
  free(b_bis->author);
  delete_list_protected(b_bis->votes);
  free(b_bis);
  #endif 
  
  /*Libération mémoire*/

  free(b->author);
  delete_list_protected(b->votes);
  free(b);
}

