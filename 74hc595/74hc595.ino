#define dataPin  10
#define latchPin 11
#define clockPin 12

byte byteToSend = 0;

void setup() {
   pinMode(latchPin, OUTPUT);
   pinMode(clockPin, OUTPUT);
   pinMode(dataPin, OUTPUT);
   digitalWrite(latchPin, HIGH);
  Serial.begin(9600);
}

void loop() {
   for (int i = 0; i < 256; i++) {
      
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, i);
      digitalWrite(latchPin, HIGH);
     Serial.print("envoie :");
     Serial.println(i);
      delay(500);
   }
 
}

