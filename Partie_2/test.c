#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"gestion_clef.h"
#include "gestion_votants_candidats.h"
#include"signature.h"

#include"../Partie_1/gestion_cryptage.h"
#include"../Partie_1/tests_primalite.h"



int main ( void ) {

    srand ( time ( NULL ) ) ;

    //Testing Init Keys
    Key* pKey = (Key*) malloc ( sizeof ( Key ) ) ;
    Key* sKey = (Key*) malloc ( sizeof ( Key ) ) ;
    init_pair_keys( pKey , sKey ,3 ,7) ;
    printf("pKey : %lx , %lx \n" , pKey-> val , pKey->n ) ;
    printf("sKey : %lx , %lx \n" , sKey-> val , sKey->n ) ;
    //Testing Key Serialization

    char * chaine = key_to_str( pKey ) ;
    
    printf("key_to_str : %s \n" , chaine ) ;
    Key * k = str_to_key( chaine ) ;
    printf("str_to_key : (%lx , %lx) \n" , k-> val , k-> n ) ;

    //Testing signature
    //Candidate keys:

    Key * pKeyC = malloc ( sizeof ( Key ) ) ;
    Key * sKeyC = malloc ( sizeof ( Key ) ) ;
    init_pair_keys( pKeyC , sKeyC ,3 ,7) ;
    //Declaration:
    char * mess = key_to_str( pKeyC ) ;
    printf ("%s vote pour %s \n" , key_to_str ( pKey ) , mess ) ;
    Signature * sgn = sign( mess , sKey ) ;
    printf ("signature :" ) ;
    print_long_vector( sgn-> contenu , sgn-> longueur ) ;
    chaine = signature_to_str( sgn ) ;
    printf ("signature_to_str : %s \n" , chaine ) ;
    sgn = str_to_signature( chaine ) ;
    printf ("str_to_signature :" ) ;
    print_long_vector( sgn-> contenu , sgn-> longueur ) ;

    //Testing protected:

    Protected * pr = init_protected( pKey , mess , sgn ) ;
    //Verification:

    
    if ( verify (pr) ) {
        printf("Signature valide \n" ) ;
    } else {
        printf("Signature non valide \n" ) ;
    }

    chaine = protected_to_str( pr ) ;
    printf ("protected_to_str : %s \n" , chaine ) ;
    pr = str_to_protected( chaine ) ;
    printf ("str_to_protected : %s %s %s \n" , key_to_str ( pr-> pKey ) ,pr-> mess ,signature_to_str( pr-> sgn ) ) ;

    free ( pKey ) ;
    free ( sKey ) ;
    free ( pKeyC ) ;
    free ( sKeyC ) ;

    printf("\n\n\n~~~~~~~~~~~~~~~\nEssais sur la gestion de candidats\n");

    generate_random_data(1000,10);


    return 0;

}


