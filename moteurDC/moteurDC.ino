#include "AFMotor.h"
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 10
AF_DCMotor motor1(1); // création de l'objet "motor1"
AF_DCMotor motor2(2); // création de l'objet "motor2"

const int basicSpeedM1 = 155;
const int basicSpeedM2 = 200;
void setup()
{ // setup IR
  Serial.begin(9600);
  Serial.println("test1");
  //IrReceiver.begin(IR_RECEIVE_PIN);
  // ////setup motorr + roule tous droit 2 sec
  Serial.println("test2");
  motor1.setSpeed(basicSpeedM1);
  motor2.setSpeed(basicSpeedM2);
  motor1.run(RELEASE);
  
  
  motor2.run(RELEASE);
  delay(1000);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(2000);
  motor2.run(RELEASE);
  motor1.run(RELEASE);
  Serial.println("test3");
}

void loop()
{Serial.println("loop");
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(2000);
  motor2.run(RELEASE);
  motor1.run(RELEASE);
  delay(1000);
  if (IrReceiver.decode())
  {
    uint16_t command = IrReceiver.decodedIRData.command;
    Serial.println(command);
    delay(100); // wait a bit
    IrReceiver.resume();

    switch (command)
    {case 12:
      Serial.println("1");
      break;
      case 24:
      Serial.println("2");
      tout_droit(motor1,motor2);
      break;
      case 94:
      Serial.println("3");
      break;
      case 8:
      Serial.println("4");
      tourner_gauche(motor1,motor2);
      break;
      case 28:
      Serial.println("5");
      break;
      case 90:
      Serial.println("6");
      tourner_droite(motor1,motor2);
      break;
      case 66:
      Serial.println("7");
      break;
      case 82:
      Serial.println("8");
      break;
      case 74:
      Serial.println("9");
      break;
    default:
      Serial.println("UNDEFINED");
    }
  }
}
void tout_droit(AF_DCMotor motor1, AF_DCMotor motor2)
{
  motor1.setSpeed(basicSpeedM1);
  motor2.setSpeed(basicSpeedM2);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(1000);
  motor2.run(RELEASE);
  motor1.run(RELEASE);
}
void tourner_droite(AF_DCMotor motor1, AF_DCMotor motor2)
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor1.setSpeed(basicSpeedM1 * 0.75);
  motor2.setSpeed(basicSpeedM2 * 0.75);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  delay(1000);
  motor2.run(RELEASE);
  motor1.run(RELEASE);
}
void tourner_gauche(AF_DCMotor motor1, AF_DCMotor motor2)
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor1.setSpeed(basicSpeedM1 * 0.75);
  motor2.setSpeed(basicSpeedM2 * 0.75);
  motor2.run(BACKWARD);
  motor1.run(FORWARD);
  delay(1000);
  motor2.run(RELEASE);
  motor1.run(RELEASE);
}

//Librairies
// #include <AFMotor.h>
// //Constants
// const int motorspeed=255;
// //Parameters
// AF_DCMotor motorG(1);

// void setup() {
//  // Code d'initialisation :s'exécute une seule fois
//   Serial.begin(9600);
//   Serial.println("Test moteur");

//   motorG.setSpeed(motorspeed);
//   motorG.run(RELEASE);

// }

// void loop() {
//   //Code principal: s'exécute de manière répétitive
//   Serial.println("-------------------------------------");
//   Serial.println("Avant ");
//   motorG.run(FORWARD);
//   delay(500);
//   Serial.println("Arrière ");
//   motorG.run(BACKWARD);
//   delay(500);
//   Serial.println("Arrêt ");
//   motorG.run(RELEASE);
//   delay(1000);
// }