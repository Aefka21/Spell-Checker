#ifndef __ATR__
#define __ATR__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Listes.h"

typedef struct noeud {
    char c;
    struct noeud * gauche;
    struct noeud * droit;
    struct noeud * fils;
} Noeud, * ATR;


ATR creer_ATR_vide();
void liberer_ATR(ATR * A);
int inserer_dans_ATR(ATR * A, char * mot);
int dans_ATR(ATR A, char * mot);
void supprimer_dans_ATR(ATR * A, char * mot);
void afficher_ATR_auxiliaire(ATR A, char * mot, int i);
void afficher_ATR(ATR A);

#endif