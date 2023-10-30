
int dataPin = 10;  // DS
int clockPin = 12; // SH_CP
int latchPin = 11; // ST_CP

void setup() {
  // Initialisation des broches
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Valeur binaire représentant l'état des LEDs (par exemple, 10101010)
  byte leds = B10101010;

  // Envoie des données au 74HC595
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
 Serial.println("envoie");
  // Attente d'une seconde
  delay(1000);
}
