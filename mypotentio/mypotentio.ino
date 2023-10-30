void setup() {
   Serial.begin(9600);  // ouvre le port série
   pinMode(A1, INPUT_PULLUP);
   pinMode(2,OUTPUT);
   
}

void loop() {
   int val = analogRead(A1);  // lit la valeur actuelle du potentiomètre
 if(val>550){
     digitalWrite(2,HIGH);
 }else{
     digitalWrite(2,LOW);
 }
   Serial.println(val); 
   delay(100);  // attend 500 ms
   

}