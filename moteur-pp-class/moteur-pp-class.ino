#include "Stepper.h"

const int stepsPerRevolution = 2048;
// Câblage:
// Broche 5 à IN1 sur le pilote ULN2003
// Broche 6 à IN2 sur le pilote ULN2003
// Broche 7 à IN3 sur le pilote ULN2003
// Broche 8 à IN4 sur le pilote ULN2003
#define droite 2048 / 4
#define gauche -2048 / 4
int count = 0;
Stepper myStepper(stepsPerRevolution, 4, 6, 5, 7); // in1 in3 in2 in4

void setup()
{
  Serial.begin(9600);
  myStepper.setSpeed(10);
  //myStepper.step(200);//setup la pos de depart : position horizontal
  delay(1000);
}

void loop()
{
  move(myStepper, stepsPerRevolution, droite, count);//rouhe haut
  delay(2000);
  Serial.println(count);
  reset(myStepper, stepsPerRevolution, count);//re horizon
  delay(2000);
  Serial.println(count);
  move(myStepper, stepsPerRevolution, gauche, count);//vert haut
  delay(2000);
  Serial.println(count);
  reset(myStepper, stepsPerRevolution, count);
  delay(2000);
  Serial.println(count);
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
