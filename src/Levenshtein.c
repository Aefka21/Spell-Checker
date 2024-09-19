#include "include/Levenshtein.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int Levenshtein(char * un, char * deux) {
    /*Nous avons suivi l'algorithme de Wikipedia comme énoncé dans le sujet*/
    int D[strlen(un) + 1][strlen(deux) + 1];
    int i, j, coutSubstitution;
    /*On initialise la première ligne*/
    for (i = 0; i < strlen(un) + 1; i++) {
        D[i][0] = i;
    }
    /*On initialise la première colonne*/
    for (j = 0; j < strlen(deux) + 1; j++) {
        D[0][j] = j;
    }
    /*On compare et calcule la distance entre deux cases*/
    for (i = 1; i < strlen(un) + 1; i++) {
        for (j = 1; j < strlen(deux) + 1; j++) {
            if (un[i - 1] == deux[j - 1]) {
                coutSubstitution = 0;
            } else {
                coutSubstitution = 1;
            }
            D[i][j] = min(D[i - 1][j] + 1, D[i][j - 1] + 1, D[i - 1][j - 1] + coutSubstitution);
        }
    }
    return D[strlen(un)][strlen(deux)];
}

/*
Fonction qui calcul le minimun entre 3 entiers
*/
int min(int i, int j, int k) {
    if (i <= j && i <= k) {
        return i;
    }
    if (j <= i && j <= k) {
        return j;
    }
    if (k <= i && k <= j) {
        return k;
    }
    return i;
}