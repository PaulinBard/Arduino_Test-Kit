#include "Stepper.h"

const int stepsPerRevolution = 200;

Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  myStepper.setSpeed(60);
}

void loop() {
  myStepper.step(stepsPerRevolution);
  delay(500);

  myStepper.step(-stepsPerRevolution);
  delay(500);

  myStepper.step(200);  // nombre de pas
  delay(2000);

  myStepper.step(-300); // nombre de pas
  delay(2000);
}