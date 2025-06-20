#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

/*==============  FONCTIONS DEMANDEES ===============*/

// 1.	Ecrire une fonction qui permet de remplir une matrice creuse
void remplirMatrice(matrice_creuse *m, int N, int M) {
    int i,j,valeur;
    // Allouer de la mémoire pour les lignes de la matrice
    m->Nlignes = N;
    m->Ncolonnes = M;
    m->tab_lignes = (liste_ligne *)malloc(N * sizeof(liste_ligne)); //le cast est optionnel, que pour indiquer que le malloc renvoie un pointeur de type liste_ligne

    if (m->tab_lignes == NULL) {//vérification si allocation réussit
        perror("Erreur d'allocation mémoire pour tab_lignes");
        exit(EXIT_FAILURE);
    }

    for (i=0; i<N; i++){
        m->tab_lignes[i] = NULL ; //Initialisation de chaque pointeur de chaque ligne
    }

    for (i=0;i<N;i++){
        for (j=0; j<M;j++){
            printf ("Entrez une valeur pour la position %d,%d: ",i,j);

            // Boucle pour assurer une saisie valide
            entrerEntier(&valeur);


            if (valeur != 0){ //On ne traite que les valeurs non nulles

                //Création d'un nouvel élément
                element *nouveau = creerElement(j, valeur);

                //Insertion du nouvel élément dans la ligne
                if (m->tab_lignes[i] == NULL) { //si la liste est vide
                    m->tab_lignes[i]=nouveau;
                } else {
                    //la liste n'est pas vide, on parcourt la liste pour ajouter à la fin
                    element *temp = m->tab_lignes[i];
                    while (temp->suivant != NULL){
                        temp = temp->suivant;
                    }
                    temp->suivant = nouveau; //ajout de l'élément à la fin
                }
            }
        }
    }
}

// 2.	Ecrire une fonction qui permet d’afficher une matrice creuse sous forme de tableau
void afficherMatrice(matrice_creuse m){
    //vérifier si la matrice existe
    if (m.tab_lignes == NULL || m.Nlignes <= 0 || m.Ncolonnes <= 0) {
        printf("\nErreur d'affichage: La matrice n'existe pas ou n'a pas de dimensions valides.\n");
        return;
    }

        // Affichage de la matrice
    printf("\nVoici la matrice: \n");
    for (int i = 0; i < m.Nlignes; i++) {
        for (int j = 0; j < m.Ncolonnes; j++) {
            // Initialiser une valeur par défaut à 0, si il n'y a pas de valeur, valeur = 0 et on affichera ce 0
            int valeur = 0;

            // Pointeur vers l'element tete de la liste dans la ligne courante
            element *courant = m.tab_lignes[i];

            while (courant != NULL) { //si tete est vide (ou qu'on atteint la fin de la liste), courant sera NULL est donc la liste ne contient pas (ou plus) d'éléments
                if (courant->col == j) {
                    valeur = courant->val; // Si l'élément existe, on prend sa valeur
                    break;
                }
                courant = courant->suivant;
            }

            printf("%d ", valeur); // Afficher la valeur
        }
        printf("\n"); // Nouvelle ligne après chaque ligne de la matrice
    }
}


// 3.	Ecrire une fonction qui permet d�afficher toutes les listes cha�n�es
void afficherMatriceListes(matrice_creuse m) {
    // V�rifier si la matrice existe
    if (m.tab_lignes == NULL|| m.Nlignes <= 0 || m.Ncolonnes <= 0) {
        printf("\nErreur d'affichage: La matrice n'existe pas ou n'a pas de dimensions valides.\n");
        return;
    }

    // Affichage des listes pour chaque ligne
    for (int i = 0; i < m.Nlignes; i++) {
        printf("Ligne %d: ", i); //pour chaque ligne de la matrice, on affiche le num�mro de la ligne
        element *courant = m.tab_lignes[i]; //initialisation pointeur pour parcourir la liste cha�n�e

        if (courant == NULL) { //si le pointeur est null alors il n'y a aucune valeur dans la liste
            printf("Ligne vide");
        } else {
            while (courant != NULL) { //sinon, on parcourt la liste cha�n�e et on affiche chaque �l�ment
                printf("(col %d, val %d) ", courant->col, courant->val);
                courant = courant->suivant;

                if (courant != NULL) printf(", ");
            }
        }
        printf("\n"); // Nouvelle ligne apr�s chaque ligne de la matrice
    }
}

//  4.	Ecrire une fonction qui renvoie la valeur de l'�l�ment de la ligne i et la colonne j
int rechercherValeur(matrice_creuse m, int i, int j) {
    int result = 0;
    //check si la matrice existe
    if (m.tab_lignes == NULL || i < 0 || i >= m.Nlignes || j < 0 || j >= m.Ncolonnes) {
        printf("Erreur de recherche: indices invalides ou matrice inexistante.\n");
        return -1; // Indiquer une erreur
    }

    element *courant = m.tab_lignes[i];

    while (courant != NULL){ //parcourir la liste chainee
        if (courant->col == j){
            printf("La valeur recherchee est: %d \n", courant->val);
            result = courant->val;
            return result;
        }
        courant = courant->suivant;
    }

    printf("Un zero est trouve a la position (%d, %d).\n", i, j); //pour les zéros
    result=0;
    return result;
}

// 5.	Ecrire une fonction qui affecte une valeur donn�e � l'�l�ment de la ligne i et la colonne j
void affecterValeur(matrice_creuse m, int i, int j, int val) {

    //cas en dehors de la matrice
    if ( i < 0 || i >= m.Nlignes || j < 0 || j >= m.Ncolonnes) {
        printf("\nErreur de recherche pour affectation: indices invalides ou matrice inexistante.\n");
        return;
    }

    element *courant = m.tab_lignes[i];
    element *precedent = NULL;

    // Parcourir la liste pour trouver la bonne position d'insertion
    while (courant != NULL && courant->col < j) {
        precedent = courant;
        courant = courant->suivant;
    }

    //cas valide quand la colonne existe
    if (courant != NULL && courant->col == j){ //parcourir la liste chainee
            if (val==0) { // il faut donc supprimer l'élément
                if (precedent == NULL){
                    //si l'élément est tête
                    m.tab_lignes[i] = courant->suivant;
                } else {
                    // si l'élément n'est pas tete
                    precedent->suivant = courant->suivant; // Relier le précédent au suivant
                }
                free(courant); // Libérer la mémoire de l'élément
            } else {
                courant->val = val; //mettre à jour la valeur
            }
            return;
    } else if (val != 0){ //cas quand la colonne n'existe pas

        // création d'un nouvel élément
        element *nouveau = creerElement(j, val);

        //Insertion du nouvel élément dans la liste
        if (precedent == NULL) {
            // Insertion en tête de la liste (marche dans les 2 cas si la liste est vide ou pas)
            nouveau->suivant = m.tab_lignes[i];
            m.tab_lignes[i] = nouveau;
        } else {
            // Insertion au milieu ou à la fin de la liste
            nouveau->suivant = courant;
            precedent->suivant = nouveau;
        }

    }
}


// 6.	Ecrire une fonction qui réalise la somme de deux matrices

void additionerMatrices(matrice_creuse m1, matrice_creuse m2) {
    // Vérification des dimensions
    if (m1.Nlignes != m2.Nlignes || m1.Ncolonnes != m2.Ncolonnes) {
        printf("\nErreur : Les dimensions des matrices ne correspondent pas.\n");
        return;
    }

    // Parcourir chaque ligne des deux matrices
    for (int i = 0; i < m1.Nlignes; i++) {
        liste_ligne l1 = m1.tab_lignes[i]; // liste de la ligne i de m1
        liste_ligne l2 = m2.tab_lignes[i];

        element *prev_l1 = NULL; // pour garder une trace du précédent élément dans m1
        element *current_l1 = l1;
        element *current_l2 = l2;

        while (current_l2 != NULL) {
            while (current_l1 != NULL && current_l1->col < current_l2->col) {
                // Avancer dans la liste de m1 si la colonne est avant celle de m2
                prev_l1 = current_l1;
                current_l1 = current_l1->suivant;
            }

            if (current_l1 != NULL && current_l1->col == current_l2->col) {
                // Additionner les valeurs
                current_l1->val += current_l2->val;

                // Supprimer l'élément si la valeur est 0
                if (current_l1->val == 0) {
                    if (prev_l1 == NULL) {
                        // Tête de liste, on pointe vers l'élément après la tete
                        m1.tab_lignes[i] = current_l1->suivant;
                    } else {
                        // Éléments après le premier, on relie l'élément précédent au suivant
                        prev_l1->suivant = current_l1->suivant;
                    }
                    free(current_l1);
                }

                current_l1 = (prev_l1 == NULL) ? m1.tab_lignes[i] : prev_l1->suivant; //Cette ligne assure que l'itération dans la liste chaînée continue correctement, que ce soit en revenant à la tête si le premier élément a été supprimé, ou en passant au suivant de l'élément précédemment traité
            } else {
                // Ajouter l'élément de m2 dans m1
                element *nouveau = creerElement(current_l2->col, current_l2->val);

                if (prev_l1 == NULL) {
                    // Insérer au début
                    nouveau->suivant = m1.tab_lignes[i];
                    m1.tab_lignes[i] = nouveau;
                } else {
                    // Insérer après prev_l1
                    nouveau->suivant = prev_l1->suivant;
                    prev_l1->suivant = nouveau;
                }
                prev_l1 = nouveau;
            }

            current_l2 = current_l2->suivant;
        }
    }
    printf("\nAddition completee.");
}

// 7.	Ecrire une fonction qui retourne le nombre d’octets gagnés
int nombreOctetsGagnes(matrice_creuse m) {
    int result = 0;
    int taille_int = sizeof(int);         // Taille d'un entier (4 octets)
    int taille_pointeur = sizeof(element*); // Taille d'un pointeur (8 octets)


    // Dimensions de la matrice
    printf("Dimensions de la matrice : %d lignes, %d colonnes\n", m.Nlignes, m.Ncolonnes);



    // Calcul de la taille mémoire de la matrice dense (Nlignes x Ncolonnes éléments)
    int octets_dense = m.Nlignes * m.Ncolonnes * taille_int;

    // Calcul de la taille mémoire utilisée par la matrice creuse
    int octets_creux = 0;  // Mémoire utilisée par la représentation creuse

    element *courant = NULL;
    for (int i = 0; i < m.Nlignes; i++) {
        courant = m.tab_lignes[i];
        while (courant != NULL) {
            // Chaque élément non nul dans la représentation creuse utilise :
            // - 4 octets pour la colonne (entier)
            // - 4 octets pour la valeur (entier)
            // - 8 octets pour le pointeur suivant (pointeur)
            octets_creux += (taille_int + taille_int + taille_pointeur); // 16 octets par élément non nul
            courant = courant->suivant;
        }
    }
    printf("\n\noctets dense: %d\n", octets_dense);
    printf("octets creux: %d\n",octets_creux);

    // Calcul du gain d'espace mémoire
    result = octets_dense - octets_creux;
    if (result < 0) printf("On perd donc %d octets.\n", result);
    if (result > 0) printf("On gagne donc %d octets.\n", result);

    return result;
}

/*==============  FONCTIONS SUPPLEMENTAIRES ===============*/

// fonction qui permet de vider le buffer d'entrée clavier
void viderBuffer (){
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

//fonction qui crée un nouvel élément
element *creerElement(int colonne, int valeur){

    element *nouveau = (element*)malloc(sizeof(element));
    if (nouveau == NULL) { //vérification si l'allocation a réussit
        perror("Erreur d'allocation mémoire pour nouveau");
        exit(EXIT_FAILURE);
    }

    nouveau->col = colonne; //indice colonne
    nouveau->val = valeur; //valeur
    nouveau->suivant = NULL; //initialisation pointeur suivant

return nouveau;
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



//on n'oublie pas de free les matrices
void libererMatrice(matrice_creuse *m) {
    for (int i = 0; i < m->Nlignes; i++) {
        element *temp = m->tab_lignes[i];
        while (temp != NULL) {
            element *suivant = temp->suivant; // Sauvegarder le pointeur vers le suivant
            free(temp); // Libérer l'élément actuel
            temp = suivant; // Passer à l'élément suivant
        }
    }
    free(m->tab_lignes); // Libérer le tableau de pointeurs
}
