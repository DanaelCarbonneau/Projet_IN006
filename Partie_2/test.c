#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"gestion_clef.h"
#include"signature.h"

#include"../Partie_1/gestion_cryptage.h"
#include"../Partie_1/tests_primalite.h"


int main ( void ) {

    srand ( time ( NULL ) ) ;

    //Testing Init Keys
    Key * pKey = malloc ( sizeof ( Key ) ) ;
    Key * sKey = malloc ( sizeof ( Key ) ) ;
    init_pair_keys ( pKey , sKey ,3 ,7) ;
    printf ("pKey : %lx , %lx \n" , pKey-> val , pKey->n ) ;
    printf (" sKey : %lx , %lx \n" , sKey-> val , sKey->n ) ;
    //Testing Key Serialization

    char * chaine = key_to_str ( pKey ) ;
        
    printf (" k e y t o s t r : %s \n" , chaine ) ;
    Key * k = str_to_key ( chaine ) ;
    printf (" s t r t o k e y : %lx , %lx \n" , k-> val , k-> n ) ;

    //Testing signature
    //Candidate keys:

    Key * pKeyC = malloc ( sizeof ( Key ) ) ;
    Key * sKeyC = malloc ( sizeof ( Key ) ) ;
    init_pair_keys ( pKeyC , sKeyC ,3 ,7) ;
    //Declaration:
    char * mess = key_to_str ( pKeyC ) ;
    printf ("%s v o t e pour %s \n" , key_to_str ( pKey ) , mess ) ;
    Signature * sgn = sign ( mess , sKey ) ;
    printf (" s i g n a t u r e :" ) ;
    print_long_vector ( sgn-> contenu , sgn-> longueur ) ;
    chaine = signature_to_str ( sgn ) ;
    printf (" s i g n a t u r e t o s t r : %s \n" , chaine ) ;
    sgn = str_to_signature ( chaine ) ;
    printf (" s t r t o s i g n a t u r e :" ) ;
    print_long_vector ( sgn-> contenu , sgn-> longueur ) ;

    //Testing protected:

    Protected * pr = init_protected ( pKey , mess , sgn ) ;
    //Verification:
    if ( verify ( pr ) ) {
        printf (" S i g n a t u r e v a l i d e \n" ) ;
    } else {
        printf (" S i g n a t u r e non v a l i d e \n" ) ;
    }

    chaine = protected_to_str ( pr ) ;
    printf (" p r o t e c t e d t o s t r : %s \n" , chaine ) ;
    pr = str_to_protected ( chaine ) ;
    printf (" s t r t o p r o t e c t e d : %s %s %s \n" , key_to_str ( pr-> pKey ) ,pr-> mess ,
    signature_to_str ( pr-> sgn ) ) ;

    free ( pKey ) ;
    free ( sKey ) ;
    free ( pKeyC ) ;
    free ( sKeyC ) ;
    return 0;

}


