#include "matricemove.h"

uint64_t dessin64;
Cote gravitySide;

const int dimension = 8;
int matrice[dimension][dimension];

const int row[8] = {l1, l2, l3, l4, l5, l6, l7, l8};
const int col[8] = {c1, c2, c3, c4, c5, c6, c7, c8};

void refreshScreen(int pixels[8][8])
{
    for (int thisRow = 0; thisRow < 8; thisRow++)
    {
        digitalWrite(row[thisRow], HIGH);
        for (int thisCol = 0; thisCol < 8; thisCol++)
        {
            int thisPixel = pixels[thisRow][thisCol];
            digitalWrite(col[thisCol], thisPixel);

            if (thisPixel == LOW)
            {
                digitalWrite(col[thisCol], HIGH);
            }
        }
        digitalWrite(row[thisRow], LOW);
    }
}

void hexToMatrix(uint64_t hexValue, int matrix[8][8])
{
    for (int i = 7; i >= 0; --i)
    {
        for (int j = 7; j >= 0; --j)
        {
            matrix[i][j] = (hexValue & 1) ? 1 : 0;
            hexValue >>= 1;
        }
    }
}

void invertMatrix(int matrice[8][8])
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            matrice[i][j] = (matrice[i][j] == 0) ? 1 : 0;
        }
    }
}
void imprimer_matrice(int matrice[8][8])
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            Serial.print(matrice[i][j]);
            Serial.print(" ");
        }
        Serial.println(); // Nouvelle ligne après chaque ligne de la matrice
    }
}

Cote gravityMatrix(Cote side, int bh, int dg)
{
    if (bh + dg == 2)
    {
        Serial.println("Haut");
        return HAUT;
    }
    else if (bh == 1 && dg == 0)
    {
        Serial.println("Droite");
        return DROITE;
    }
    else if (bh == 0 && dg == 1)
    {
        Serial.println("Gauche");
        return GAUCHE;
    }
    else
    {
        Serial.println("Bas");
        return BAS;
    }
}

Cote chercher_depart(Cote oldD)
{
    int zone_a[dimension / 2][dimension / 2];
    int zone_b[dimension / 2][dimension / 2];
    int zone_c[dimension / 2][dimension / 2];
    int zone_d[dimension / 2][dimension / 2];

    for (int i = 0; i < dimension / 2; i++)
    {
        for (int j = 0; j < dimension / 2; j++)
        {
            zone_a[i][j] = matrice[i][j];
            zone_b[i][j] = matrice[i][j + dimension / 2];
            zone_c[i][j] = matrice[i + dimension / 2][j];
            zone_d[i][j] = matrice[i + dimension / 2][j + dimension / 2];
        }
    }

    int nb_1_zone_a = 0;
    int nb_1_zone_b = 0;
    int nb_1_zone_c = 0;
    int nb_1_zone_d = 0;
    for (int i = 0; i < dimension / 2; i++)
    {
        for (int j = 0; j < dimension / 2; j++)
        {
            nb_1_zone_a += zone_a[i][j];
            nb_1_zone_b += zone_b[i][j];
            nb_1_zone_c += zone_c[i][j];
            nb_1_zone_d += zone_d[i][j];
        }
    }

    int maxPoints = max(max(nb_1_zone_a, nb_1_zone_b), max(nb_1_zone_c, nb_1_zone_d));
    if (maxPoints == nb_1_zone_a)
    {
        return GAUCHE;
    }
    else if (maxPoints == nb_1_zone_b)
    {
        return DROITE;
    }
    else if (maxPoints == nb_1_zone_c)
    {
        return HAUT;
    }
    else
    {
        return BAS;
    }
}

void creer_matrice()
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            matrice[i][j] = 0;
        }
    }
    matrice[dimension / 2][dimension / 2] = 1;
}

void pivoter_matrice(int matrice[dimension][dimension], int matrice_transposee[dimension][dimension], Cote direction)
{
    if (direction == BAS)
    {
        for (int i = 0; i < dimension; i++)
        {
            for (int j = 0; j < dimension; j++)
            {
                matrice_transposee[i][j] = matrice[i][j];
            }
        }
    }
    else if (direction == HAUT)
    {
        for (int i = 0; i < dimension; i++)
        {
            for (int j = 0; j < dimension; j++)
            {
                matrice_transposee[i][j] = matrice[dimension - 1 - i][dimension - 1 - j];
            }
        }
    }
    else
    {

        for (int i = 0; i < dimension; i++)
        {
            for (int j = 0; j < dimension; j++)
            {
                matrice_transposee[i][j] = matrice[j][i];
            }
        }

        if (direction == DROITE)
        {
            for (int i = 0; i < dimension; i++)
            {
                for (int j = 0; j < dimension / 2; j++)
                {
                    int temp = matrice_transposee[i][j];
                    matrice_transposee[i][j] = matrice_transposee[i][dimension - 1 - j];
                    matrice_transposee[i][dimension - 1 - j] = temp;
                }
            }
        }
        else if (direction == GAUCHE)
        {
            for (int i = 0; i < dimension / 2; i++)
            {
                for (int j = 0; j < dimension; j++)
                {
                    int temp = matrice_transposee[i][j];
                    matrice_transposee[i][j] = matrice_transposee[dimension - 1 - i][j];
                    matrice_transposee[dimension - 1 - i][j] = temp;
                }
            }
        }
    }
}

void setup()
{
    // Initialise la communication série à 9600 bauds pour la communication avec le moniteur série
    Serial.begin(9600);

    // Initialise les broches de sortie pour les lignes et colonnes de la matrice LED
    for (int thisPin = 0; thisPin < 8; thisPin++)
    {
        // Initialise les broches de colonnes (cathodes) en tant que sorties et les met à l'état HIGH pour éteindre les LED
        pinMode(col[thisPin], OUTPUT);
        pinMode(row[thisPin], OUTPUT);
        digitalWrite(col[thisPin], HIGH);
    }

    // Initialise la variable dessin64 avec une valeur hexadécimale
    dessin64 = 0x00f8fefaca8e8800;
    ;
    gravitySide = BAS;
    // Convertit la valeur hexadécimale en une matrice de 8x8
    hexToMatrix(dessin64, matrice);

    // Inverse la matrice (pivote à 180 degrés)
    invertMatrix(matrice);

    // Configure les broches 14 et 15 en INPUT_PULLUP pour les boutons
    pinMode(14, INPUT_PULLUP);
    pinMode(15, INPUT_PULLUP);
}

void loop()
{
    // Lit l'état des boutons sur les broches 14 et 15 et met à jour la variable gravitySide en fonction
    //imprimer_matrice(matrice);
    gravitySide = gravityMatrix(gravitySide, digitalRead(14), digitalRead(15));
    int tempo[8][8];

    // Pivoter la matrice en fonction de la direction détectée
    pivoter_matrice(matrice, tempo, gravitySide);
    //imprimer_matrice(tempo);
    refreshScreen(tempo);
    // Attend une seconde avant de continuer la boucle
    delay(1000);
}
