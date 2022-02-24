/*--- Préambule ---*/
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include"tests_primalite.h"

#define OCCURENCE_TEST_TEMPS 1000000

int main(){

    /*Variables pour le temps*/
	clock_t temps_initial;
	clock_t temps_final;
	double temps_intervalle;


    /*Temps de calcul pour le test naïf de primalité*/

    for(long i = 100000; i < OCCURENCE_TEST_TEMPS ; i+=50){

        /*On prend la mesure du temps d'opérations pour la valeur de i*/
        temps_initial = clock();
        is_prime_naive(i);
        temps_final = clock();

        /*On regarde si la durée dépasse les 0.002 secondes, si oui, on affiche la valeur et on arrête la boucle*/
        temps_intervalle = (temps_final-temps_initial)/CLOCKS_PER_SEC;
        if(temps_intervalle > 0.002){
            printf("Le temps de calcul dépasse les 2 milièmes de secondes pour p = %ld\n",i);
            return 0;
        }
        
    }
    return 0;
}



