#define c1 6
#define c2 7
#define c3 8
#define c4 9

#define r1 5
#define r2 4
#define r3 3
#define r4 2

int rangee[] = {r1, r2,r3,r4};
int colonne[] = {c1,c2,c3,c4};
int col_scan;
void setup()
{
    Serial.begin(9600);
    for (int i = 0; i <= 3; i++)
    {
        // Initialisation des broches
        pinMode(rangee[i], OUTPUT);
        pinMode(colonne[i], INPUT);
        digitalWrite(colonne[i], HIGH);
    }
    Serial.println("====== Clavier pret ======");
}
void loop()
{
    // Regarde si un bouton est enfoncé
    for (int i = 0; i <= 3; i++)
    {
        digitalWrite(rangee[0], HIGH);
        digitalWrite(rangee[1], HIGH);
        digitalWrite(rangee[2], HIGH);
        digitalWrite(rangee[3], HIGH);
        digitalWrite(rangee[i], LOW);
        for (int j = 0; j <= 3; j++)
        {
            col_scan = digitalRead(colonne[j]);
            if (col_scan == LOW)
            {
                // Lorsqu'un bouton est enfoncé, appel de la fonction toucherBouton
                // pour savoir quel bouton est enfoncé
                toucherBouton(i, j);
                delay(300);
            }
        }
    }
}

void toucherBouton(int i, int j)
{
    if (i == 0 && j == 0) // Bouton S1 enfoncé
        Serial.println("S1");
    if (i == 0 && j == 1) // Bouton S2 enfoncé
        Serial.println("S2");
    if (i == 0 && j == 2) // Bouton S3 enfoncé
        Serial.println("S3");
    if (i == 0 && j == 3) // Bouton S4 enfoncé
        Serial.println("S4");
    if (i == 1 && j == 0) // Bouton S5 enfoncé
        Serial.println("S5");
    if (i == 1 && j == 1) // Bouton S6 enfoncé
        Serial.println("S6");
    if (i == 1 && j == 2) // Bouton S7 enfoncé
        Serial.println("S7");
    if (i == 1 && j == 3) // Bouton S8 enfoncé
        Serial.println("S8");
    if (i == 2 && j == 0) // Bouton S9 enfoncé
        Serial.println("S9");
    if (i == 2 && j == 1) // Bouton S10 enfoncé
        Serial.println("S10");
    if (i == 2 && j == 2) // Bouton S11 enfoncé
        Serial.println("S11");
    if (i == 2 && j == 3) // Bouton S12 enfoncé
        Serial.println("S12");
    if (i == 3 && j == 0) // Bouton S13 enfoncé
        Serial.println("S13");
    if (i == 3 && j == 1) // Bouton S14 enfoncé
        Serial.println("S14");
    if (i == 3 && j == 2) // Bouton S15 enfoncé
        Serial.println("S15");
    if (i == 3 && j == 3) // Bouton S16 enfoncé
        Serial.println("S16");
}