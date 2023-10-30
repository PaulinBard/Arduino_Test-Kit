#ifndef MATRICE_LED_H
#define MATRICE_LED_H

#include <Arduino.h>

// Définition des pins

#define l1 11
#define l2 8
#define l3 6
#define l4 9

#define l5 7
#define l6 10
#define l7 12
#define l8 13

#define c1 17 // ana3
#define c2 16 // ana2
#define c3 19 // ana5
#define c4 2

#define c5 4
#define c6 18 // ana4
#define c7 3
#define c8 5

#define sensor1 = 15 // ana1
#define sensor2 = 14 // ana0

// Enumération des côtés
enum Cote {
    DROITE = 1,
    GAUCHE = 2,
    HAUT = 3,
    BAS = 4
};

extern Cote gravitySide;
extern const int dimension;
extern int matrice[8][8];

void refreshScreen(int pixels[8][8]);
void hexToMatrix(uint64_t hexValue, int matrix[8][8]);
void invertMatrix(int matrice[8][8]);
void imprimer_matrice(int matrice[8][8]);
Cote gravityMatrix(Cote side, int bh, int dg);
Cote chercher_depart(Cote oldD);
void creer_matrice();
void pivoter_matrice(int matrice[8][8], Cote direction);

#endif  // MATRICE_LED_H
