#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

int main() {

    // ============= MENU UTILISATEUR ============= */
    char choix = '0';
    matrice_creuse m1, m2; // déclaration des matrices pour qu'elles oient accessibles dans tout le programme
    while (choix != '8') {
        printf("\n================ MENU ================\n");
        printf("======================================");
        printf("\n1. Remplir une matrice creuse");
        printf("\n2. Afficher une matrice creuse sous forme de tableau");
        printf("\n3. Afficher une matrice creuse sous forme de listes");
        printf("\n4. Donner la valeur d'un element d'une matrice creuse");
        printf("\n5. Affecter une valeur a un element d'une matrice creuse (ou supprimer un element)");
        printf("\n6. Additionner deux matrices creuses");
        printf("\n7. Calculer le gain");
        printf("\n8. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");

        scanf(" %c", &choix);
        /*
        viderBuffer();
        choix = getchar();
        */

        switch (choix) {
            case '1' :
                //remplirMatrice
                printf("Souhaitez vous remplir la premiere ou la deuxieme matrice?(Tapez 1 pour m1, 2 pour m2)\n La matrice choisie: ");
                int choix_matrice;
                scanf("%d", &choix_matrice);

                int N = 0, M = 0; // Initialisation des dimensions
                if (choix_matrice == 1){
                    printf("\n======== PREMIERE MATRICE ========\n");
                    printf ("Entrez le nombre de lignes pour m1:");
                    entrerEntier(&N);
                    printf ("Entrez le nombre de colonnes pour m1:");
                    entrerEntier(&M);
                    remplirMatrice (&m1, N, M);
                    printf("Matrice remplie");
                } else if (choix_matrice == 2){
                    printf("\n======== DEUXIEME MATRICE ========\n");
                    printf ("Entrez le nombre de lignes pour m2:");
                    entrerEntier(&N);
                    printf ("Entrez le nombre de colonnes pour m2:");
                    entrerEntier(&M);
                    remplirMatrice (&m2, N, M);
                    printf("Matrice remplie\n");
                } else {
                    printf("Choix de matrice invalide!\n");
                    viderBuffer();
                }
                break;

            case '2' :
                //afficherMatrice
                printf("Souhaitez vous afficher la premiere ou la deuxieme matrice?(Tapez 1 pour m1, 2 pour m2)\n La matrice choisie: ");
                choix_matrice = 0;
                scanf("%d", &choix_matrice);

                if (choix_matrice == 1){
                    afficherMatrice(m1);
                } else if (choix_matrice == 2){
                    afficherMatrice(m2);
                } else {
                    printf("Choix de matrice invalide!\n");
                    viderBuffer();
                }
                break;

            case '3' :
                //afficherMatriceListes
                printf("Souhaitez vous afficher la premiere ou la deuxieme matrice?(Tapez 1 pour m1, 2 pour m2)\n La matrice choisie: ");
                choix_matrice = 0;
                scanf("%d", &choix_matrice);

                if (choix_matrice == 1){
                    afficherMatriceListes(m1);
                } else if (choix_matrice == 2){
                    afficherMatriceListes(m2);
                } else {
                    printf("Choix de matrice invalide!\n");
                    viderBuffer();
                }
                break;

            case '4' :
                //rechercherValeur
                printf("Souhaitez vous le rechercher dans la premiere ou la deuxieme matrice?(Tapez 1 pour m1, 2 pour m2)\n La matrice choisie: ");
                choix_matrice = 0;
                scanf("%d", &choix_matrice);
                printf("\n");

                printf("Entrez la ligne de l'element recherche (nb: numerotation commence a zero): ");
                int i;
                entrerEntier(&i);

                printf("Entrez la colonne de l'element recherche: (nb: numerotation commence a zero):");
                int j;
                entrerEntier(&j);
                printf("\n");



                if (choix_matrice == 1){
                    rechercherValeur(m1,i,j);
                } else if (choix_matrice == 2){
                    rechercherValeur(m2,i,j);
                } else {
                    printf("Choix de matrice invalide!\n");
                    viderBuffer();
                }
                break;

            case '5' :
                //affecterValeur
                printf("\nSouhaitez vous l'ajouter dans la premiere ou la deuxieme matrice?(Tapez 1 pour m1, 2 pour m2)\n La matrice choisie: ");
                choix_matrice = 0;
                scanf("%d", &choix_matrice);

                printf("\nEntrez la valeur de l'element a ajouter, (zero si vous souhaitez supprimer un element): ");
                int val;
                entrerEntier(&val);

                printf("Entrez la ligne de l'element a ajouter (nb: numerotation commence a zero): ");
                int ligne;
                entrerEntier(&ligne);

                printf("Entrez la colonne de l'element a ajouter (nb: numerotation commence a zero): ");
                int colonne;
                entrerEntier(&colonne);


                if (choix_matrice == 1){
                    affecterValeur(m1,ligne,colonne,val);
                } else if (choix_matrice == 2){
                    affecterValeur(m2,ligne,colonne,val);
                } else {
                    printf("Choix de matrice invalide!\n");
                    viderBuffer();
                }
                break;

            case '6' :
                //additionerMatrices
                printf("Les matrices m1 et m2 seront additionnees, le resultat stocke dans m1.\n");
                additionerMatrices(m1,m2);
                break;

            case '7' :
                //nombreOctetsGagnes
                printf("Souhaitez vous calculer le gain de la premiere ou la deuxieme matrice?(Tapez 1 pour m1, 2 pour m2)\n La matrice choisie: ");
                choix_matrice = 0;
                scanf("%d", &choix_matrice);

                if (choix_matrice == 1){
                    nombreOctetsGagnes(m1);
                } else if (choix_matrice == 2){
                    nombreOctetsGagnes(m2);
                } else {
                    printf("Choix de matrice invalide!\n");
                    viderBuffer();
                }
                break;

            case '8' :
                printf("\n======== PROGRAMME TERMINE ========\n");
                // Libération de la mémoire
                libererMatrice(&m1);
                libererMatrice(&m2);
                break;

            default :
                printf("\n\nERREUR : votre choix n'est valide ! ");
                viderBuffer();
        }
        printf("\n\n\n");
    }

    return 0;
}
