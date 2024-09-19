#ifndef __Listes__
#define __Listes__

#include <stdio.h>

typedef struct cellule {
    char * mot;
    struct cellule * suivant;
} Cellule, * Liste;

Cellule * allouer_Cellule(char * mot);
int inserer_en_tete(Liste * L, char * mot);
void liberer_Liste(Liste * L);
void afficher_Liste(Liste L);
Liste parcourir(FILE * f, char * mot);

#endif