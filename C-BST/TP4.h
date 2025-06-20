#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED

#define ANNEE 2024
typedef struct Intervalle{
    int borne_inf;//format MMJJ
    int borne_sup;
}T_inter;

typedef struct Noeud {
    int id;//identifiant de l'entreprise
    char* objet;//objet de la réservation
    T_inter date;
    struct Noeud *fils_g;
    struct Noeud *fils_d;
}T_noeud;

typedef T_noeud* T_arbre;


//=================================FONCTIONS=================================
T_noeud *creer_noeud(int id_entr, char *objet, T_inter intervalle);
void ajouter(T_arbre *abr, int id_entr, char *objet, T_inter intervalle);
T_noeud *rechercher(T_arbre arbre, T_inter intervalle, int id_entr);
void supprimer(T_arbre *abr, T_inter intervalle, int id_entr);
void modifier(T_arbre abr, int id_entr, T_inter actuel, T_inter nouveau);
void afficher_abr(T_arbre abr);
void afficher_entr (T_arbre abr, int id_entr);
void afficher_periode(T_arbre abr, T_inter periode);
void detruire_arbre(T_arbre *arbre);

//========FCTS SUPP========
int chevauchement(T_inter a, T_inter b);
int verifier_chevauchement(T_noeud *noeud, T_inter intervalle);
int verifier_chevauchement_sauf(T_noeud *noeud, T_inter intervalle, T_inter sauf);
T_noeud* trouve_pere(T_arbre abr, T_noeud* noeud);
T_noeud *successeur(T_arbre abr, T_noeud* noeud);
void afficher_date(int date);
void entrerEntier(int adresse_valeur);
int saisir_date();
void viderBuffer();

#endif // TP4_H_INCLUDED
