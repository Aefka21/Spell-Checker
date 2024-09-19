#include "include/Listes.h"
#include "include/Levenshtein.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Liste allouer_Cellule(char * mot) {
    Liste cell;
    /*On alloue la place mémoire pour la liste*/
    cell = (Cellule *)malloc(sizeof(Cellule));
    if (cell) {
        cell->mot = malloc(strlen(mot) * sizeof(char));
        strcpy(cell->mot, mot);
        cell->suivant = NULL;
    }
    return cell;
}

int inserer_en_tete(Liste * L, char * mot) {
    Liste tmp;
    tmp = allouer_Cellule(mot);
    if (!tmp) {
        return 0;
    }
    /*On place la liste dans le champs suivant de tmp*/
    tmp->suivant = *L;
    /*On fait pointer la liste vers tmp*/
    *L = tmp;
    return 1;
}

void liberer_Liste(Liste * L) {
    Liste tmp, suivant;
    tmp = * L;
    while (tmp != NULL) {
        suivant = tmp->suivant;
        /*On libere la place mémoire utilisé par la cellule*/
        free(tmp);
        tmp = suivant;
    }
    * L = NULL;
}

void afficher_Liste(Liste L) {
    if (L == NULL) {
        printf("La liste est vide\n");
        return;
    }
    while (L != NULL) {
        printf("%s ", L->mot);
        L = L->suivant;
    }
}

/*
Fonction qui parcours le fichier et place les mots avec la plus petite distance du mot choisi dans une liste
Nous avons suivi l'algorithme de l'énoncé
*/
Liste parcourir(FILE * f, char * mot) {
    Liste correction;
    int test_valeur, d, dmin;
    char * tmp_mot;
    tmp_mot = malloc(100 * sizeof(char));
    dmin = 999999999;
    correction = NULL;
    rewind(f);
    do {
        test_valeur = fscanf(f, "%s\n", tmp_mot);
        d = Levenshtein(tmp_mot, mot);
        if (d <= dmin) {
            if (d < dmin) {
                dmin = d;
                liberer_Liste(&correction);
            }
            inserer_en_tete(&correction, tmp_mot);
        }
    } while (test_valeur != EOF);
    return correction;
}