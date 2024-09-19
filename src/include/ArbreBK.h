#ifndef __ArbreBK__
#define __ArbreBK__

#include "Listes.h"
#include <stdio.h>

typedef struct noeudBK {
    char * mot;
    int valeur;
    struct noeudBK * filsG;
    struct noeudBK * frereD;
} NoeudBK, * ArbreBK;

int inserer_dans_ArbreBK(ArbreBK * A, char * mot);
NoeudBK * creer_noeud(char * mot, int taille);
Liste rechercher_dans_ArbreBK(ArbreBK A, char * mot);
void recherche_aux(ArbreBK A, Liste * L, char * mot, int * seuil);
char * prendre_mot(FILE * dico, int * ok);
ArbreBK creer_ArbreBK(FILE * dico);
void liberer_ArbreBK(ArbreBK * A);
void afficher_ArbreBK(ArbreBK A);
void afficher_ArbreBK_aux(ArbreBK A, int nb_tab);
int dans_ArbreBK(ArbreBK A, char * mot);

#endif