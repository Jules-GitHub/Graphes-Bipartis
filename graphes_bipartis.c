#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "assert.h"

int degre(int** graphe, int n, int i)
{
    int degre = 0;
    for (int j = 0; j < n; j++) {
        if (graphe[i][j] == 1) {
            degre++;
        }
    }
    return degre;
}

int degre_max(int** graphe, int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (degre(graphe, n, i) > max) {
            max = degre(graphe, n, i);
        }
    }
    return max;
}

bool* liste_isoles(int** graphe, int n) {
    bool* liste_isoles = malloc(n * sizeof(bool));
    for (int i = 0; i < n; i++) {
        liste_isoles[i] = (degre(graphe, n, i) == 0);
    }
    return liste_isoles;
}

int* colonne(int** matrice, int n, int m, int j) {
    int* colonne = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        colonne[i] = matrice[i][j];
    }
    return colonne;
}

int produit_scalaire(int* x, int* y, int n) {
    int produit = 0;
    for (int i = 0; i < n; i++) {
        produit += x[i] * y[i];
    }
    return produit;
}

int** produit(int** matrice1, int** matrice2, int n, int m, int p) {
    int** produit = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        produit[i] = malloc(p * sizeof(int));
        for (int j = 0; j < p; j++) {
            produit[i][j] = produit_scalaire(matrice1[i], colonne(matrice2, m, p, j), m);
        }
    }
    return produit;
}


void free_matrice(int** matrice, int n) {
    for (int i = 0; i < n; i++) {
        free(matrice[i]);
    }
    free(matrice);
}

int** exponentiation_rapide(int** matrice, int n, int p) {
    assert(p>0);
    if (p == 1) {
        return matrice;
    } else if (p % 2 == 0) {
        int** resultat = exponentiation_rapide(matrice, n, p / 2);
        int** prod = produit(resultat, resultat, n, n, n);
        free_matrice(resultat, n);
        return prod;
    } else {
        int** resultat = exponentiation_rapide(matrice, n, p - 1);
        int** prod = produit(resultat, matrice, n, n, n);
        free_matrice(resultat, n);
        return prod;
    }
}

bool somme_degres(int** graphe, int n, int* liste1, int taille1, int* liste2, int taille2) {

    int s1 = 0;
    for (int i=0; i<taille1; i++) {
        s1 += degre(graphe, n, liste1[i]);
    }

    int s2 = 0;
    for (int i=0; i<taille2; i++) {
        s2 += degre(graphe, n, liste2[i]);
    }

    return s1==s2;

}

bool est_biparti(int** graphe, int n) {

    int** copie = malloc(sizeof(int*)*n);
    for (int i=0; i<n; i++) {
        copie[i] = malloc(sizeof(int)*n);
        for (int j=0; j<n; j++) {
            copie[i][j] = graphe[i][j];
        }
    }
    
    int** carre = produit(copie, copie, n, n, n);

    int p=1;
    while (p<=n) {

        for (int j=0; j<n; j++) {
            if (copie[j][j]!=0) {
                return false;
            }
        }

        int** resultat = produit(copie, carre, n, n, n);
        free(copie);
        copie = resultat;
        p+=2;

    }

    return true;

}

void colorie(int** graphe, int* coloriage, int n, int i, int couleur) {

    coloriage[i] = couleur;
    for (int j=0; j<n; j++) {
        if (graphe[i][j] != 0 && coloriage[j] == -1) {
            colorie(graphe, coloriage, n, j, (couleur+1)%2);
        }
    }

}

int* coloriage_connexe(int** graphe, int n) {

    int* coloriage = malloc(sizeof(int)*n);
    for (int i=0; i<n; i++) {
        coloriage[i] = -1;
    }
    colorie(graphe, coloriage, n, 0, 0);
    return coloriage;

}

int* coloriage_complet(int** graphe, int n) {

    int* coloriage = malloc(sizeof(int)*n);
    for (int i=0; i<n; i++) {
        coloriage[i] = -1;
    }
    for (int i=0; i<n; i++) {
        if (coloriage[i] == -1) {
            colorie(graphe, coloriage, n, i, 0);
        }
    }
    return coloriage;

}


int main() {

    return EXIT_SUCCESS;

}
