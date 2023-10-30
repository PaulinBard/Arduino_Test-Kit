#include <SoftwareSerial.h>

SoftwareSerial ESP(10, 11,true); // TX, RX

void setup()
{
    Serial.begin(9600);

    ESP.begin(115200);
    pinMode(2,OUTPUT);

}
void loop(){
     while (Serial.available())
    {
        String msg = Serial.readString();
      
            ESP.println(msg);
        
    }
     while (ESP.available())
    {
        String msg =ESP.readString();
            if(msg=="ON"){
                digitalWrite(2,HIGH);
            }
            if(msg=="OFF"){
                digitalWrite(2,LOW);
            }
            Serial.println(msg);
        
    }
}