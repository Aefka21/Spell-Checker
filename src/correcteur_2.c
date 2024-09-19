#include <stdio.h>
#include "include/ArbreBK.h"
#include "include/ATR.h"
#include "include/Levenshtein.h"
#include "include/Listes.h"

int main(int argc, char ** argv) {
    ArbreBK A;
    Liste correction, erreur;
    FILE * dico, * texte;
    char * mot;
    int ok;
    correction = NULL;
    erreur = NULL;
    A = NULL;
    /*On teste si il y a le bon nombre d'argument*/
    if (argc != 3) {
        printf("Veuillez entrer un texte et un dictionnaire\n");
        return 0;
    }
    /*Ouverture du texte a corriger*/
    texte = fopen(argv[1], "r");
    if (!texte) {
        printf("Veuillez entrer un texte valide\n");
        return 0;
    }
    /*Ouverture du dictionnaire de reference*/
    dico = fopen(argv[2], "r");
    if (!dico) {
        printf("Veuillez entrer un dictionnaire valide\n");
        return 0;
    }
    A = creer_ArbreBK(dico);

    /*On prend les mots mal orthographies*/

    /*Allocation de memoire pour la chaine de caractere*/
    mot = malloc(100 * sizeof(char));
    mot = prendre_mot(texte, &ok);
    while (ok) {
        if (!dans_ArbreBK(A, mot)) {
            inserer_en_tete(&erreur, mot);
        }
        mot = prendre_mot(texte, &ok);
    }

    /*Pour chaque mot mal orthographie, on recherche ses corrections les plus proches*/
    while (erreur) {
        correction = rechercher_dans_ArbreBK(A, erreur->mot);
        printf("mot mal orthographie : %s\n", erreur->mot);
        printf("Proposition : ");
        afficher_Liste(correction);
        printf("\n");
        liberer_Liste(&correction);
        erreur = erreur->suivant;
    }
    

    return 0;
}