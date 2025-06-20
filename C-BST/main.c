#include <stdio.h>
#include <stdlib.h>
#include "TP4.h"


int main() {
    // ============= MENU UTILISATEUR =============
    T_arbre *arbre = NULL;
    int id, borne_inf, borne_sup;
    char objet[100];
    T_inter intervalle;
    T_inter actuel, nouveau;

    char choix = '0';
    while (choix != '7') {
        printf("\n================ MENU ================\n");
        printf("======================================");
        printf("\n1. Afficher toutes les reservations");
        printf("\n2. Afficher les reservations d'une entreprise");
        printf("\n3. Afficher les reservations sur une periode");
        printf("\n4. Ajouter une reservation");
        printf("\n5. Modifier une reservation");
        printf("\n6. Supprimer une reservation");
        printf("\n7. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");

        viderBuffer();
        choix=getchar();

        switch (choix) {
            case '1' :
                printf("\n\n========Liste des reservations :\n");
                afficher_abr(arbre);
                break;

            case '2' :
                printf("\n\nEntrez l'identifiant de l'entreprise : ");
                entrerEntier(&id);
                printf("========Reservations pour l'entreprise %d :\n", id);
                afficher_entr(arbre, id);
                break;

            case '3' :
                //saisie
                printf(" Entrez la date de debut de la reservation :\n");
                borne_inf=saisir_date();
                do {
                printf(" Entrez la date de fin de la reservation :\n");
                borne_sup = saisir_date();

                if (borne_sup < borne_inf) {
                    printf("Erreur : La date de fin doit etre apres la date de début. Reessayez.\n");
                }
                } while (borne_sup < borne_inf);
                //affichage
                printf("========Reservations du");
                afficher_date(borne_inf);
                printf("au");
                afficher_date(borne_sup);
                printf("\n");

                // Créer l'intervalle
                intervalle.borne_inf=borne_inf;
                intervalle.borne_sup=borne_sup;

                afficher_periode(arbre,intervalle);
                break;

            case '4' :
                // Demander l'ID de l'entreprise
                printf("\n\nEntrez l'ID de l'entreprise : ");
                entrerEntier(&id);

                // Demander l'objet
                printf("Entrez l'objet de la reservation : ");
                scanf(" %[^\n]", objet); // lire une chaîne avec des espaces

                // Saisir la date de début (borne inférieure)
                printf(" Entrez la date de debut de la reservation :\n");
                borne_inf=saisir_date();

                 // Saisir la date de fin (borne supérieure)
                do {
                printf("Entrez la date de fin de la reservation :\n");
                borne_sup = saisir_date();

                if (borne_sup < borne_inf) {
                    printf("Erreur : La date de fin doit etre apres la date de debut. Reessayez.\n");
                }
                } while (borne_sup < borne_inf);

                // Créer l'intervalle
                intervalle.borne_inf=borne_inf;
                intervalle.borne_sup=borne_sup;

                //ajouter
                ajouter(&arbre, id, objet, intervalle);
                break;

            case '5' :

                printf("Entrez l'ID de l'entreprise a modifier : ");
                entrerEntier(&id);

                printf(" Entrez les dates actuelles de la reservation.\n");
                printf("  Borne inferieure actuelle : ");
                actuel.borne_inf=saisir_date();
                do {
                printf("  Borne superieure actuelle : ");
                actuel.borne_sup=saisir_date();
                if (actuel.borne_sup < actuel.borne_inf) {
                    printf("  Erreur : La date de fin doit etre apres la date de debut. Reessayez.\n");
                }
                } while (actuel.borne_sup < actuel.borne_inf);

                printf(" Entrez les nouvelles dates de la reservation.\n");
                printf("  Nouvelle borne inferieure : ");
                nouveau.borne_inf=saisir_date();
                do{
                printf("  Nouvelle borne superieure : ");
                nouveau.borne_sup=saisir_date();
                if (nouveau.borne_sup < nouveau.borne_inf) {
                    printf("  Erreur : La date de fin doit etre apres la date de debut. Reessayez.\n");
                }
                } while (nouveau.borne_sup < nouveau.borne_inf);

                modifier(arbre, id, actuel, nouveau);
                break;

            case '6' :
                printf("Entrez l'ID de l'entreprise qui a une reservation a supprimer : ");
                entrerEntier(&id);

                // Saisir la date de début (borne inférieure)
                printf(" Entrez la date de début de la reservation :\n");
                borne_inf=saisir_date();

                 // Saisir la date de fin (borne supérieure)
                do {
                printf("Entrez la date de fin de la reservation :\n");
                borne_sup = saisir_date();

                if (borne_sup < borne_inf) {
                    printf("Erreur : La date de fin doit etre apres la date de debut. Reessayez.\n");
                }
                } while (borne_sup < borne_inf);

                // Créer l'intervalle
                intervalle.borne_inf=borne_inf;
                intervalle.borne_sup=borne_sup;

                //supprimer
                supprimer(&arbre,intervalle,id);

                break;

            case '7' :
                // Libération de la mémoire
                printf("\n=== Liberation de l'arbre restant ===\n");
                detruire_arbre(&arbre);
                printf("\n========= PROGRAMME TERMINE =========\n");
                break;

            default :
                printf("\n\nERREUR : votre choix n'est valide ! ");
                viderBuffer();
                break;

        }
        printf("\n\n\n");
    }

    return 0;
}
