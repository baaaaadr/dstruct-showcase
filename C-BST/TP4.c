#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TP4.h"

T_noeud *creer_noeud(int id_entr, char *objet, T_inter intervalle){
    T_noeud *nouveau = (T_noeud *)malloc(sizeof(T_noeud));

    if (nouveau==NULL){
        printf("Erreur allocation mémoire.\n");
        return NULL;
    }

    nouveau->id = id_entr;
    nouveau->objet = strdup(objet); //!Il est impératif de libérer cette zone de mémoire après utilisation de strdup (malloc inclus)

    if (nouveau->objet == NULL) {
        free(nouveau); // On free si la duplication avec strdup n'aboutit pas
        return NULL;
    }

    nouveau->date = intervalle;
    nouveau->fils_d=NULL;
    nouveau->fils_g=NULL;

    return nouveau;
}

void ajouter(T_arbre *abr, int id_entr, char *objet, T_inter intervalle){

    printf("\nDebut de la fonction ajouter.\n");
    if (*abr == NULL){ //arbre vide
        *abr=creer_noeud(id_entr, objet, intervalle);
        printf("Arbre cree, racine: [%d, %d]\n",intervalle.borne_inf, intervalle.borne_sup);

        if (*abr == NULL) {
            printf("Erreur lors de la création du nœud.\n");
        }
        return;
    }

    printf("Intervalle a ajouter : [%d, %d]\n", intervalle.borne_inf, intervalle.borne_sup);

    if(verifier_chevauchement(*abr, intervalle)){
        printf("Erreur : chevauchement detecte avec un intervalle existant dans l'arbre.\n");
        return;
    }

    T_noeud *parkour = *abr;
    T_noeud *pere = NULL;
    int estFilsGauche=0;//pour suivre si parkour sera fils droit ou gauche

    //On parcourt l'arbre pour trouver l'emplacement convenable de l'intervalle
    while ( parkour!=NULL ){
        //printf("Parcours en cours : noeud [%d, %d]\n", parkour->date.borne_inf, parkour->date.borne_sup);

        estFilsGauche=0;//reset
        pere=parkour;

        if (intervalle.borne_inf < parkour->date.borne_inf){
            parkour=parkour->fils_g;
            estFilsGauche=1;
        }else if (intervalle.borne_inf > parkour->date.borne_inf){
            parkour=parkour->fils_d;
        }
    }
    //ajouter à l'arbre
    printf("Ajout du noeud comme fils %s.\n", (estFilsGauche ? "gauche" : "droit"));

    if (estFilsGauche==1){
            pere->fils_g = creer_noeud(id_entr, objet, intervalle);
    }else{
            pere->fils_d = creer_noeud(id_entr, objet, intervalle);
    }
}


T_noeud *rechercher(T_arbre abr, T_inter intervalle, int id_entr) {
    //cas trivial 1 : arbre vide
    if (abr == NULL) {
        printf ("Arbre vide ou noeud/reservation non trouve(e).\n");
        return NULL;
    }

    //cas trivial 2 : la racine est la réservation recherchée
    if (abr->id == id_entr &&
        abr->date.borne_inf == intervalle.borne_inf &&
        abr->date.borne_sup == intervalle.borne_sup) {
        printf("Noeud trouve : [%d, %d], ID : %d.\n", abr->date.borne_inf, abr->date.borne_sup, abr->id);
        return abr;
    }

    //récursivité
    if (intervalle.borne_inf < abr->date.borne_inf) {
        return rechercher(abr->fils_g, intervalle, id_entr);
    } else {
        return rechercher(abr->fils_d, intervalle, id_entr);
    }
}
void supprimer(T_arbre *abr, T_inter intervalle, int id_entr) {
    if (*abr == NULL) {
        printf("L'arbre est vide ou le noeud n'existe pas.\n");
        return;
    }

    //chercher le noeud à supprimer
    T_noeud *noeud=rechercher(*abr, intervalle, id_entr);
        // Si le nOeud n'est pas trouvé
    if (noeud == NULL) {
        printf("Le noeud a supprimer est introuvable.\n");
        return;
    }
    T_noeud *pere= trouve_pere(*abr, noeud);
    //printf("Papa in supprimer : [%d, %d], ID : %d, Objet : %s\n", pere->date.borne_inf, pere->date.borne_sup, pere->id, pere->objet);

    // Cas 1 : pas de fils
    if (noeud->fils_g == NULL && noeud->fils_d == NULL) {
        if (pere == NULL) {
            *abr = NULL;  // L'arbre entier devient vide
        } else if (pere->fils_g == noeud) {
            pere->fils_g = NULL;
        } else {
            pere->fils_d = NULL;
        }
        free(noeud->objet);
        free(noeud);
    }
    // Cas 2 : un seul fils
    else if (noeud->fils_g == NULL || noeud->fils_d == NULL) {
        T_noeud *fils = (noeud->fils_g != NULL) ? noeud->fils_g : noeud->fils_d;

        if (pere == NULL) {
            *abr = fils;  // Le fils devient la nouvelle racine
        } else if (pere->fils_g == noeud) {
            pere->fils_g = fils;
        } else {
            pere->fils_d = fils;
        }
        free(noeud->objet);
        free(noeud);
    }
    // Cas 3 :deux fils
    else {
        T_noeud *succ = successeur(abr, noeud);

        free(noeud->objet);// Libérer l'ancien objet avant de copier le succ (re allouer de la mémoire)

        T_noeud temp;
        temp.date=succ->date;
        temp.id=succ->id;
        temp.objet=strdup(succ->objet);

        //supprimer le succ
        supprimer(abr,succ->date, succ->id);

        // Remplacer les données du noeud à supprimé par celles du successeur
        noeud->id = temp.id;
        noeud->date = temp.date;
        noeud->objet = strdup(temp.objet);  // attention à bien dupliquer une chaîne
        free(temp.objet);


    }
}

void modifier(T_arbre abr, int id_entr, T_inter actuel, T_inter nouveau) {
    if (abr == NULL) { //arbre vide
        printf("Erreur : Il n'existe aucune reservation.\n");
        return;
    }

    // Rechercher la réservation à modifier
    T_noeud *reservation = rechercher(abr, actuel, id_entr);
    if (reservation == NULL) {
        printf("Erreur : La reservation n'existe pas.\n");
        return;
    }

    //printf("\nverifier_chevauchement_sauf: %d\n\n",verifier_chevauchement_sauf(abr, nouveau, reservation->date));

    // Vérification de chevauchement avec d'autres réservations, on vérifie avant de supprimer quoique ce soit pour ne pas perdre des données
    if (verifier_chevauchement_sauf(abr, nouveau,reservation->date)) {
        //si le nouveau intervalle chevauche un intervalle de l'arbre et ce n'est pas celui qu'il va remplacer, alors on arrête

            printf("Erreur : Le nouvel intervalle chevauche une autre reservation.\n");
            return;

    }

    // Modification de la réservation
    T_noeud temp;
    temp.id=reservation->id;
    temp.objet=strdup(reservation->objet);

    supprimer(&abr, actuel, id_entr);
    T_noeud *nouvelle_reservation= creer_noeud(id_entr,temp.objet,nouveau);
    ajouter(&abr, nouvelle_reservation->id, nouvelle_reservation->objet, nouvelle_reservation->date);

    printf("Reservation modifiee avec succes.\n");
    printf("Voici la nouvelle reservation : [%d, %d] : Entreprise %d ; %s\n\n",
           nouvelle_reservation->date.borne_inf, nouvelle_reservation->date.borne_sup,
           nouvelle_reservation->id, nouvelle_reservation->objet);
    free(temp.objet);
}

void afficher_abr(T_arbre abr) {
    if (abr == NULL) {
        return; //arbre vide oui c'est finis, rien à afficher
    }
    // Parcours en ordre infixe
    afficher_abr(abr->fils_g);// Parcourir le sous-arbre gauche

    afficher_date(abr->date.borne_inf);
    printf("au");
    afficher_date(abr->date.borne_sup);
    printf(": Entreprise %d ; %s\n", abr->id, abr->objet);

    afficher_abr(abr->fils_d);// Parcourir le sous-arbre droit
}


void afficher_entr (T_arbre abr, int id_entr){
    if (abr == NULL){
        return NULL;
    }

    afficher_entr(abr->fils_g, id_entr);

    if (abr->id == id_entr){
        afficher_date(abr->date.borne_inf);
        printf("au");
        afficher_date(abr->date.borne_sup);
        printf(": Entreprise %d ; %s\n", abr->id, abr->objet);
    }

    afficher_entr(abr->fils_d, id_entr);
}


void afficher_periode(T_arbre abr, T_inter periode) {
    if (abr == NULL) {
        return; // arbre vide ou fin
    }

    afficher_periode(abr->fils_g, periode);

    if (chevauchement(abr->date,periode)) { //on affiche si chevauchement
        afficher_date(abr->date.borne_inf);
        printf(" au ");
        afficher_date(abr->date.borne_sup);
        printf(" : entr. %d ; %s\n", abr->id, abr->objet);
    }

    afficher_periode(abr->fils_d, periode);
}

void detruire_arbre(T_arbre *arbre) {
    if (*arbre == NULL) return;

    // Détruire les sous-arbres gauche et droit
    detruire_arbre(&(*arbre)->fils_g);
    detruire_arbre(&(*arbre)->fils_d);

    // Libérer le nœud actuel
    free((*arbre)->objet);
    free(*arbre);
    *arbre = NULL;
}


//=================================FONCTIONS SUPPLEMENTAIRES=================================

int chevauchement(T_inter a, T_inter b) {
    //pour que a et b ne se touchent pas et ne se chevauchent pas
    return !(a.borne_sup < b.borne_inf || b.borne_sup < a.borne_inf );
    /*Comment ça marche :
        en ignorant le !, on regarde l'équation entre parenthèse au début,
        cette expression vérifie si des intervalles ne se chevauchent pas
        (1 si pas de chevauchement). Si on trouve un des sup de a ou b qui est
        < que l'inf de l'autre intervalle, alors les intervalles ne se chevauchent pas.
    */
}

//fct récursive pour vérifier qu'il n'y a pas de chevauchement à partir d'un certain noeud de l'arbre
int verifier_chevauchement(T_noeud *noeud, T_inter intervalle) {
    if (noeud == NULL) {
        return 0; // Aucun chevauchement
    }

     //printf("Verification de chevauchement avec l'intervalle [%d, %d] et le noeud [%d, %d]\n",intervalle.borne_inf, intervalle.borne_sup, noeud->date.borne_inf, noeud->date.borne_sup);

    // Vérifier le chevauchement avec le noeud actuel
    if (chevauchement(noeud->date, intervalle)) {

         printf("Chevauchement detecte avec le noeud [%d, %d]\n",
               noeud->date.borne_inf, noeud->date.borne_sup);

        return 1; // Chevauchement détecté
    }
    // Vérifier dans les sous-arbres gauche et droit
    return verifier_chevauchement(noeud->fils_g, intervalle) || verifier_chevauchement(noeud->fils_d, intervalle);
}

//fct implémenté pour la fonction modifier, pour vérifier si il y a un chevauchement dans l'arbre sauf à un noeud précis
int verifier_chevauchement_sauf(T_noeud *noeud, T_inter intervalle, T_inter sauf) {
    if (noeud == NULL) {
        return 0; // Aucun chevauchement
    }

    printf("Verification de chevauchement avec l'intervalle [%d, %d] et le noeud [%d, %d]\n",
           intervalle.borne_inf, intervalle.borne_sup, noeud->date.borne_inf, noeud->date.borne_sup);

    // Vérifier le chevauchement avec le noeud actuel
    if (chevauchement(noeud->date, intervalle)) {
        printf("Comparaison avec sauf : [%d, %d]\n", sauf.borne_inf, sauf.borne_sup);
        if (noeud->date.borne_inf == sauf.borne_inf && noeud->date.borne_sup == sauf.borne_sup) {
            printf("On ignore ce chevauchement avec l'intervalle sauf.\n");
        } else {
            printf("Chevauchement detecte avec le noeud [%d, %d]\n",
                   noeud->date.borne_inf, noeud->date.borne_sup);
            return 1; // Chevauchement détecté
        }
    }

    // Vérifier dans les sous-arbres gauche et droit
    return verifier_chevauchement_sauf(noeud->fils_g, intervalle, sauf) ||
           verifier_chevauchement_sauf(noeud->fils_d, intervalle, sauf);
}

T_noeud* trouve_pere(T_arbre abr, T_noeud* noeud) {
    if (abr == NULL || noeud == NULL) return NULL;

    T_noeud* courant = abr;

    // Parcours de l'arbre pour trouver le père
    while (courant != NULL) {
        // Vérifier si le noeud courant est le père du noeud recherché
        if (courant->fils_g == noeud || courant->fils_d == noeud) {
            //printf("Papa trouvé : [%d, %d], ID : %d.\n", courant->date.borne_inf, courant->date.borne_sup, courant->id);
            return courant;
        }

        // Parcours en fonction de la borne_inf du noeud recherché
        if (noeud->date.borne_inf < courant->date.borne_inf) {
            courant = courant->fils_g;
        } else {
            courant = courant->fils_d;
        }
    }

    // Si le noeud n'est pas trouvé dans l'arbre
    return NULL;
}

T_noeud *successeur(T_arbre abr, T_noeud* noeud){
    if (noeud == NULL) return NULL;

    T_noeud *succ=NULL;

    // Cas 1 : Le noeud a un sous-arbre droit
    if (noeud->fils_d != NULL){
        succ=noeud->fils_d;

        // Trouver le noeud le plus à gauche dans le sous-arbre droit
        while (succ->fils_g != NULL){
            succ=succ->fils_g;
        }

    // Cas 2 : Le noeud n’a pas de sous-arbre droit: alors on remonte dans l'arbre et c'est le premier pere d'un fils gauche
    }else{
        succ=trouve_pere(abr, noeud);
        while (succ!=NULL && noeud==succ->fils_d){
            noeud= succ;
            succ= trouve_pere(abr,noeud);
        }
    }
    printf("Successeur trouve : [%d, %d], ID : %d.\n", succ->date.borne_inf, succ->date.borne_sup, succ->id);
    return succ;
}

void afficher_date(int date) {// afficher une date sous le format MM/JJ/AA
    int mois = date / 100;      // Les deux premiers chiffres correspondent au mois
    int jour = date % 100;      // Les deux derniers chiffres correspondent au jour
    printf(" %02d/%02d/%d ", jour, mois, ANNEE);//largeur minimum du champ 2carac
}

// fonction qui permet de vider le buffer d'entrée clavier
void viderBuffer (){
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

//Entrer un entier (Boucle pour assurer une saisie valide d'un nombre)
void entrerEntier(int adresse_valeur){
    while (1) {
        // Tenter de lire un entier
        if (scanf("%d", adresse_valeur) == 1) {
            break; // Saisie valide, sortir de la boucle
        } else {
            // Saisie invalide
            printf(" Erreur: veuillez entrer un nombre entier.\n");
            // Nettoyer le buffer d'entrée
            while (getchar() != '\n'); // éliminant ainsi tous les caractères restants dans le buffer, ce qui évite de boucler indéfiniment sur une mauvaise saisie.
        }
    }
}


int saisir_date() {
    int mois, jour;

    // Demander le mois
    do {
        printf("Entrez le mois (1-12) : ");
        scanf("%d", &mois);
        if (mois < 1 || mois > 12) {
            printf("Mois invalide. Veuillez entrer un nombre entre 1 et 12.\n");
        }
    } while (mois < 1 || mois > 12);

    // Demander le jour
    do {
        printf("Entrez le jour (1-31) : ");
        scanf("%d", &jour);

        // Vérifier les jours valides en fonction du mois
        if ((mois == 4 || mois == 6 || mois == 9 || mois == 11) && jour > 30) {
            printf("Mois %d ne peut pas avoir plus de 30 jours. Réessayez.\n", mois);
        } else if (mois == 2 && jour > 29) {
            printf("Février ne peut pas avoir plus de 29 jours. Réessayez.\n");
        } else if (jour < 1 || jour > 31) {
            printf("Jour invalide. Veuillez entrer un nombre entre 1 et 31.\n");
        } else {
            break; // Le jour est valide
        }
    } while (1);

    // Combiner mois et jour au format MMJJ
    return mois * 100 + jour;
}
