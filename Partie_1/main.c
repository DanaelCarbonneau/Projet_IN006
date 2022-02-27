/*--- Préambule ---*/
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include"tests_primalite.h"

#define OCCURENCE_TEST_TEMPS 1000000000
#define A 11
#define N 3
#define M_MAX 5000

void menu(){
	printf("0 - Sortie du programme\n");
	printf("1 - Quel est le plus grand nombre premier que vous arrivez `a tester en moins de 2 milliemes de seconde avec la fonction is_prime_naive(long p) ?\n");
	printf("2 - Comparer les performances des deux m ́ethodes d’exponentiation modulaire en traçant des courbes de temps en fonction de m\n");
	printf("3 - Retourner un nombre premier de taille comprise entre low_size et up_size en utilisant le test de Miller-Rabin\n");
}

int main(){
	char entree[256];
	int rep = 0;
	do{
		/*Affichage du menu et récupération de la réponse*/
		menu();
		fgets(entree, 10,stdin);
		rep = atoi(entree);

		/*Variables nécessaires*/
			clock_t temps_initial;
			clock_t temps_final;
			double temps_intervalle;
			double temps_v1;
			double temps_v2;
			long a;
			long n;
			int low_size;
			int up_size;
			int k;
			long res;
			FILE* f_comp_modpow;

		/*Réalisation de l'action souhaitée*/
		switch(rep){
			case 1:


    				/*Temps de calcul pour le test naïf de primalité*/

			    	temps_intervalle = 0;
			    	a = 10000;
			    	printf("%d\n\n",is_prime_naive(a));
			    	n = a;
			    	while (temps_intervalle < 0.002){
			    		/*On prend la mesure du temps d'opérations pour la valeur de i*/
						temps_initial = clock();
						res = is_prime_naive(a);
						temps_final = clock();
						if (res){ 
							n = a;
							temps_intervalle = (double)(temps_final - temps_initial)/(CLOCKS_PER_SEC);
							printf("%ld : %f\n", n, temps_intervalle);
						}
						a++;

			    	}
					printf("Le temps de calcul dépasse les 2 milièmes de secondes pour p = %ld\n",n);			
					break;
			case 2:
				/*Ouverture du fichier où stocker les résultats*/
				f_comp_modpow = fopen("ComparaisonModPow.txt","w");
				

				/*et pour le calcul*/
				a = A;
				n = N;

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
				low_size = 10;
				up_size = 20;
				k = 100;
				res = random_prime_number(low_size,up_size,k);
				if (res != -1){
					printf("Nous avons trouvé p = %ld premier, entre les tailles %d et %d\n",res,low_size,up_size);
				}break;
		}			
			
			
	}while (rep != 0);
	printf("Merci et au revoir!\n");
        
    return 0;
}
