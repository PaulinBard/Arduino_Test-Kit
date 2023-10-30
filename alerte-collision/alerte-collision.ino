#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "Stepper.h"

const int stepsPerRevolution = 2048;
// Câblage:
// Broche 5 à IN1 sur le pilote ULN2003
// Broche 6 à IN2 sur le pilote ULN2003
// Broche 7 à IN3 sur le pilote ULN2003
// Broche 8 à IN4 sur le pilote ULN2003
#define droite stepsPerRevolution / 4
#define gauche -stepsPerRevolution / 4
int count = 0;                                     // mettre le moteur step a la position de départ
Stepper myStepper(stepsPerRevolution, 4, 6, 5, 7); // in1 in3 in2 in4

LiquidCrystal_I2C LCD(0x27, 16, 2); // setup ecran

const byte TRIGGER_PIN = 13; // US
const byte ECHO_PIN = 12;
const byte LED_rouge = 10; // led pour proche

unsigned long startTime = 0; // timer affichage
const long myDelay = 500;
unsigned long startTimeLed = 0; // timer led
const long myDelayLed = 200;
bool onLed;
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s, temps limite pour la mesure de distance
bool safeZone;
const float SOUND_SPEED = 340.0 / 1000; // Vitesse du son dans l'air en mm/us
int controle_dg;
void setup()
{
    Serial.begin(9600);
    myStepper.setSpeed(10);
    // myStepper.step(512);// setup le depart
    pinMode(TRIGGER_PIN, OUTPUT);
    digitalWrite(TRIGGER_PIN, LOW);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LED_rouge, OUTPUT);
    LCD.init();
    LCD.backlight();
    LCD.setCursor(1, 0);
    LCD.print("MESURE");
    LCD.setCursor(4, 1);
    LCD.print("ULTRA SON");
    onLed = false;
    safeZone = false;
    delay(1000);
    controle_dg = 0;
}

void loop()
{
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    long mesure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
    float distance_mm = mesure / 2.0 * SOUND_SPEED;

    // Serial.print("distance mm : ");
    Serial.println(distance_mm);
    // Serial.println(" mm, ");
    if (distance_mm < 50.0)
    {
        safeZone = false;
    }
    else
    {
        safeZone = true;
    }
    unsigned long currentTime = millis();
    unsigned long currentTimeLed = millis();
    if (currentTimeLed - startTimeLed >= myDelayLed)
    {

        startTimeLed = currentTimeLed;
        if (distance_mm < 50.0)
        {
            // Serial.println("dist<50");
            if (onLed == false)
            {
                digitalWrite(LED_rouge, HIGH);
                onLed = true;
                // Serial.println("up");
            }
            else
            {
                onLed = false;
                digitalWrite(LED_rouge, LOW);
            }
        }
        else
        {
            digitalWrite(LED_rouge, LOW);
        }
    }

    if (currentTime - startTime >= myDelay)
    {

        startTime = currentTime;
        LCD.clear();
        LCD.setCursor(1, 0);
        LCD.print(distance_mm);
        LCD.print(" mm");
        LCD.setCursor(1, 1);
        if (safeZone)
        {
            LCD.print("SAFE MODE");
            Serial.println("SAFE MODE");
            if (controle_dg == 0)
            {
                move(myStepper, stepsPerRevolution, droite, count);
                controle_dg = 1;
            }
            if (controle_dg == 2)
            {
                reset(myStepper, stepsPerRevolution, count);
                move(myStepper, stepsPerRevolution, droite, count);
                controle_dg = 1;
            }
        }
        else
        {
            LCD.print("DANGER!!");
            Serial.println("DANGER");
            if (controle_dg == 0)
            {

                move(myStepper, stepsPerRevolution, gauche, count);
                controle_dg = 2;
            }
            if (controle_dg == 1)
            {
                reset(myStepper, stepsPerRevolution, count);
                move(myStepper, stepsPerRevolution, gauche, count);
                controle_dg = 2;
            }
        }
    }
    delay(50);
}

void move(Stepper moteur, int steprev, int nb_step, int cnt)
{
    count = (cnt + nb_step) % steprev;
    moteur.step(nb_step); // nombre de pas
    delay(50);
}

void reset(Stepper moteur, int steprev, int cnt)
{
    if (cnt > 0)
    {
        moteur.step(-cnt);
        delay(50);
    }
    else if (cnt < 0)
    {
        moteur.step(-cnt);
        delay(50);
    }
    count = 0;
    // nombre de pas
    delay(50);
}
