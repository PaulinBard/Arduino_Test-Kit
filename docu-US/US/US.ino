#include <LiquidCrystal_I2C.h>
#include <Wire.h>

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

const float SOUND_SPEED = 340.0 / 1000; // Vitesse du son dans l'air en mm/us

void setup()
{
  Serial.begin(9600);
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
  delay(1000);
}

void loop()
{
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  long mesure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  float distance_mm = mesure / 2.0 * SOUND_SPEED;

  //Serial.print("distance mm : ");
  Serial.println(distance_mm);
  

  unsigned long currentTime = millis();
  unsigned long currentTimeLed = millis();
  if (currentTimeLed - startTimeLed >= myDelayLed)
  {

    startTimeLed = currentTimeLed;
    if (distance_mm < 100.0)
    {
      // Serial.println("dist<100");
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
  }
  delay(50);
}
