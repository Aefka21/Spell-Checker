#include "include/ATR.h"
#include "include/Listes.h"
#include <stdio.h>


int main(int argc, char * argv[]) {
    ATR A;
    FILE * fichier, * texte;
    Liste erreur;
    int test_valeur, i;
    char *mot;
    char c;
    fichier = NULL;
    A = NULL;
    erreur = NULL;
    i = 0;
    if (argc != 3) {
        printf("Veuillez mettre des arguments valides\n");
    }
    /*Ouverture du texte à corriger*/
    texte = fopen(argv[1], "r");
    if (texte == NULL) {
        printf("Veuillez entrer un texte\n");
        return 0;
    }
    /*Ouverture du dictionnaire de référence*/
    fichier = fopen(argv[2], "r");
    if (fichier == NULL) {
        printf("Veuillez entrer un dictionnaire\n");
        return 0;
    }
    /*Allocation de mémoire pour la chaine de caractère*/
    mot = malloc(100 * sizeof(char));
    /*On insère tous les mots du dictionnaire dans l'ATR*/
    do {
        test_valeur = fscanf(fichier, "%s\n", mot);
        inserer_dans_ATR(&A, mot);
    } while (test_valeur != EOF);
    afficher_ATR(A);
    /*On réinitialise mot*/
    strcpy(mot, "");
    
    /*On regarde les mots du texte à corriger*/
    do {
        c = fgetc(texte);
        if (c == ' ' || c == '\n') {
            mot[i] = '\0';
            /*Si il ne sont pas dans le dictionnaire, on l'insère dans la liste des mots à corriger*/
            if (!dans_ATR(A, mot)) {
                inserer_en_tete(&erreur, mot);
            }
            i = 0;
        } else {
            mot[i] = c;
            i++;
        }
    } while (c != EOF);

    afficher_Liste(erreur);

    return 0;
}
