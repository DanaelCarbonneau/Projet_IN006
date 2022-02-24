/*--- Préambule ---*/
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include"tests_primalite.h"

#define OCCURENCE_TEST_TEMPS 1000000000

void menu(){
	printf("0 - Sortie du programme\n");
	printf("1 - Quel est le plus grand nombre premier que vous arrivez `a tester en moins de 2 milliemes de seconde avec la fonction is_prime_naive(long p) ?\n");
	printf("2 - Comparer les performances des deux m ́ethodes d’exponentiation modulaire en traçant des courbes de temps en fonction de m\n");
	printf("3 - Retourner un nombre premier de taille comprise entre low_size et up_size en utilisant le test de Miller-Rabin\n");
}

int main(){
	char entree[256];
	do{
		/*Affichage du menu et récupération de la réponse*/
		menu();
		fgets(entree, 10,stdin);
		rep = atoi(entree);
		/*Réalisation de l'action souhaitée*/
		switch(rep){
			case 1:
				/*Variables pour le temps*/
				clock_t temps_initial;
				clock_t temps_final;
				double temps_intervalle;


    				/*Temps de calcul pour le test naïf de primalité*/

			    	for(long i = 1000000; i < OCCURENCE_TEST_TEMPS ; i+=50){

					/*On prend la mesure du temps d'opérations pour la valeur de i*/
					temps_initial = clock();
					is_prime_naive(i);
					temps_final = clock();

					/*On regarde si la durée dépasse les 0.002 secondes, si oui, on affiche la valeur et on arrête la boucle*/
					temps_intervalle = (temps_final-temps_initial)/CLOCKS_PER_SEC;
					if(temps_intervalle > 0.002){
					    printf("Le temps de calcul dépasse les 2 milièmes de secondes pour p = %ld\n",i);
					    break;
				}				
				break;
			case 2:
				/*Ouverture du fichier où stocker les résultats*/
				FILE* f_comp_modpow = fopen("ComparaisonModPow.txt","w");

			    /*Variables pour le temps*/
				clock_t temps_initial;
				clock_t temps_final;
				double temps_v1;
				double temps_v2;

				/*et pour le calcul*/
				long a = A;
				long n = N;

				for (int i = 1; i <= M_MAX; i++){

					fprintf(f_comp_modpow, "%d\t", i);

					/*Calcul temps version naive*/
					temps_initial = clock();
					modpow_naive(a,i,n);
					temps_final = clock();
					temps_v1 = (double)(temps_final - temps_initial)/(CLOCKS_PER_SEC);

					/*Calcul temps version améliorée*/
					temps_initial = clock();
					modpow(a,i,n);
					temps_final = clock();
					temps_v2 = (double)(temps_final - temps_initial)/(CLOCKS_PER_SEC);

					/*écriture*/
					fprintf(f_comp_modpow, "%f\t",temps_v1);
					fprintf(f_comp_modpow,"%f\n",temps_v2);
				}

				fclose(f_comp_modpow);
				break;
			case 3:
				int low_size = 10;
				int up_size = 20;
				int k = 100;
				long res = random_prime_number(low_size,up_size,k);
				if (res != -1){
					printf("Nous avons trouvé p = %ld premier, entre les tailles %d et %d\n",res,low_size,up_size);
				}
				
			
			
	}while (rep != 0);
	printf("Merci et au revoir!\n");
        
    return 0;
}



