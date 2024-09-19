#include "include/ATR.h"
#include "include/Listes.h"

ATR creer_ATR_vide() {
    ATR tmp;
    /*On alloue l'espace memoire*/
    tmp = malloc(sizeof(Noeud));
    if (tmp) {
        /*On initialise les valeur à NULL*/
        tmp->c = '\0';
        tmp->droit = NULL;
        tmp->fils = NULL;
        tmp->gauche = NULL;
    }
    return tmp;
}

void liberer_ATR(ATR * A) {
    ATR tmp;
    if (!(*A)) {
        return;
    }
    tmp = * A;
    liberer_ATR(&(*A)->gauche);
    liberer_ATR(&(*A)->fils);
    liberer_ATR(&(*A)->droit);
    /*On libere l'espace mémoire*/
    free(tmp);
    *A = NULL;
}

int inserer_dans_ATR(ATR * A, char * mot) {
    if (!(*A)) {
        *A = creer_ATR_vide();
        (*A)->c = *mot;
    }
    if ((*A)->c == *mot) {
        if ((*A)->c != '\0') {
            return inserer_dans_ATR(&(*A)->fils, mot + 1);
        }
        (*A)->c = '\0';
        return 1;
    } else if ((*A)->c < *mot) {
        return inserer_dans_ATR(&(*A)->droit, mot);
    } else if ((*A)->c > *mot) {
        return inserer_dans_ATR(&(*A)->gauche, mot);
    }
    return 0;
}

int dans_ATR(ATR A, char * mot) {
    if (!A) {
        return 0;
    }
    if (A->c == *mot) {
        if (A->c == '\0') {
            return 1;
        }
        return dans_ATR(A->fils, ++mot);
    } else if (A->c < *mot) {
        return dans_ATR(A->droit, mot);
    } else {
        return dans_ATR(A->gauche, mot);
    }

}

/*void supprimer_dans_ATR(ATR * A, char * mot) {
    if (*A == NULL) {
        return;
    }
    if (*mot == '\0') {
        free(*A);
        *A = NULL;
        return;
    }
    if ((*A)->c == *mot) {
        if ((*A)->gauche || (*A)->droit) {
            tmp = (*A)->gauche;
        } else if ((*A)->droit) {
            tmp = (*A)->droit;
        } else {
            tmp = (*A)->gauche;
        }
        supprimer_dans_ATR(&(*A)->fils, (++mot));
    } else {
        if ((*A)->c == '\0') {
            if (*mot > (*A)->c) {
                if ((*A)->droit) {
                    supprimer_dans_ATR(&(*A)->droit, mot);
                }
            }
        }
        if (*mot > (*A)->c) {
            if ((*A)->droit) {
                supprimer_dans_ATR(&(*A)->droit, mot);
            }
        } else {
            if ((*A)->gauche) {
                supprimer_dans_ATR(&(*A)->gauche, mot);
            }
        }
    }
}*/

void afficher_ATR_auxiliaire(ATR A, char * mot, int i) {
    if (A != NULL) {
        mot[i] = A->c;
        if (A->c == '\0') {
            printf("%s\n", mot);
        } else {
            afficher_ATR_auxiliaire(A->fils, mot, i + 1);
        }
        if (A->gauche != NULL) {
            afficher_ATR_auxiliaire(A->gauche, mot, i);
        }
        if (A->droit != NULL) {
            afficher_ATR_auxiliaire(A->droit, mot, i);
        }
    }
}

void afficher_ATR(ATR A) {
    char mot[100] = "";
    int i;
    i = 0;
    afficher_ATR_auxiliaire(A, mot, i);
}