#include "include/ArbreBK.h"
#include "include/Listes.h"
#include "include/Levenshtein.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*Alloue un noeud pour un arbre BK*/
NoeudBK * creer_noeud(char * mot, int taille) {
    NoeudBK * noeud = NULL;
    noeud = (NoeudBK *) malloc(sizeof(NoeudBK));
    if (noeud) {
        noeud->mot = mot;
        noeud->valeur = taille;
        noeud->filsG = NULL;
        noeud->frereD = NULL;
    }
    return noeud;
}

/*Inserer un noeud dans un arbre BK au bon endroit*/
int inserer_dans_ArbreBK(ArbreBK * A, char * mot){
    ArbreBK noeud;
    ArbreBK fils;
    ArbreBK nouveau_fils;
    ArbreBK tmp, tmp2;
    int val, test;

    /*Si l'arbre est vide*/
    if (*A == NULL){
        *A = creer_noeud(mot, 0);
        return 1;
    }

    noeud = *A;
    test = 1;
    
    while (1) {
        val = Levenshtein(noeud->mot, mot);
        fils = noeud->filsG;
        while (fils) {
            /*Si un des fils a la meme distance que la distance recherche*/
            if (fils->valeur == val) {
                noeud = fils;
                break;
            }
            fils = fils->frereD;
        }
        if (!fils) {
            nouveau_fils = creer_noeud(mot, val);
            tmp = noeud->filsG;
            tmp2 = NULL;
            while (tmp && tmp->valeur < val) {
                tmp2 = tmp;    /*On garde le noeud precedant*/
                tmp = tmp->frereD;    /*On prend le noeud suivant*/
                test = 0;
            }
            if (tmp) {    /*Si la distance du dernier noeud est inferieur a la distance recherche*/
                if (!test) {    /*Si le noeud a deja un fils*/
                    nouveau_fils->frereD = tmp2->frereD;
                } else {
                    nouveau_fils->frereD = tmp;
                }
            } else {
                nouveau_fils->frereD = NULL;
            }
            if (!tmp2) {    /*Si le noeud n'a pas de fils*/
                noeud->filsG = nouveau_fils;
            } else {
                tmp2->frereD = nouveau_fils;
            }
            
            break;
        }
    }
    return 0;
}

/*Ajoute dans une liste les mots les plus proche du mot recherche*/
Liste rechercher_dans_ArbreBK(ArbreBK A, char * mot) {
    Liste L;
    int seuil;
    L = NULL;
    seuil = Levenshtein(mot, A->mot);
    recherche_aux(A, &L, mot, &seuil);
    return L;
}

void recherche_aux(ArbreBK A, Liste * L, char * mot, int * seuil) {
    ArbreBK frere;
    int lev;
    if (!A) {    /*Si l'arbre est vide*/
        return;
    }
    lev = Levenshtein(mot, A->mot);
    if (lev == * seuil) {    /*Si la distance entre le mot recherche et le noeud est egal au seuil*/
        inserer_en_tete(&(*L), A->mot);
    }
    if (lev < * seuil) {    /*Si cette distance est inferieur au seuil*/
        liberer_Liste(&(*L));
        inserer_en_tete(&(*L), A->mot);
        * seuil = lev;
    }
    frere = A->filsG;
    while (frere) {
        recherche_aux(frere, &(*L), mot, seuil);
        frere = frere->frereD;
    }
}

/*Renvoie un mot dans un fichier*/
char * prendre_mot(FILE * dico, int * ok) {
    char * mot;
    char c;
    int cmpt;
    cmpt = 0;
    mot = malloc(100 * sizeof(char));
    c = fgetc(dico);
    if (c == EOF) {
        * ok = 0;
        return mot;
    }
    while (c != EOF && c != '\n' && c != ' ') {
        mot[cmpt++] = c;
        c = fgetc(dico);
    }
    * ok = 1;
    return mot;
}

/*Creer un arbre BK a partir d'un fichier*/
ArbreBK creer_ArbreBK(FILE * dico) {
    ArbreBK A;
    int ok;
    char * mot;
    A = NULL;
    mot = malloc(100 * sizeof(char));
    mot = prendre_mot(dico, &ok);
    while (ok) {
        inserer_dans_ArbreBK(&A, mot);
        mot = prendre_mot(dico, &ok);
    }
    return A;
}

/*Affiche tous les mots de l'arbre BK*/
void afficher_ArbreBK(ArbreBK A) {
    afficher_ArbreBK_aux(A, -1);
}

void afficher_ArbreBK_aux(ArbreBK A, int nb_tab) {
    int i;
    if (A) {
        for (i = 0; i < nb_tab; i++) {
            printf("       ");
        }
        if (nb_tab != -1) {
            printf("|--%d-->", A->valeur);
        }
        printf("%s\n", A->mot);
        afficher_ArbreBK_aux(A->filsG, nb_tab + 1);
        afficher_ArbreBK_aux(A->frereD, nb_tab);
    }
}

/*Libere l'arbre BK*/
void liberer_ArbreBK(ArbreBK * A) {
    ArbreBK tmp;
    if (!(*A)) {
        return;
    }
    tmp = * A;
    liberer_ArbreBK(&(*A)->filsG);
    liberer_ArbreBK(&(*A)->frereD);
    /*On libere l'espace memoire*/
    free(tmp);
    *A = NULL;
}

/*Verifie si un mot est dans l'arbre BK*/
int dans_ArbreBK(ArbreBK A, char * mot) {
    ArbreBK fils;
    int lev;
    if (A) {
        if (!Levenshtein(mot, A->mot)) {
            return 1;
        }
        lev = Levenshtein(mot, A->mot);
        fils = A->filsG;
        while (fils) {
            if (fils->valeur == lev) {
                return dans_ArbreBK(fils, mot);
            }
            fils = fils->frereD;
        }
    }
    return 0;
}