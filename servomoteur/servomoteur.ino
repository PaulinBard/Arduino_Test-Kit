
#include <Servo.h>  // on inclut la bibliothèque pour piloter un servomoteur

Servo monServo;  

void setup()
{Serial.begin(9600);
    monServo.attach(11); 
}

void loop()
{monServo.write(90);// horizon
 Serial.println("horizon");
  delay(2000);
  monServo.write(0);
 Serial.println("vert");// 0 vert en haut
  delay(2000);
	
  monServo.write(180);
 Serial.println("rouge");// rouge en haut
  delay(2000);  
   
}