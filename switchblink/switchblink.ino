

const int redLed = 2;
const int blueLed = 3;
const int greenLed = 6;
const int btn = 4;
int btnState;
int blinkOne;
int currentBtnState;
int ledState;
unsigned long startTime = 0;
const long myDelay = 200;

void setup()
{
  pinMode(btn, INPUT_PULLUP);
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  btnState = LOW;
  blinkOne = redLed;
  ledState = LOW;
  Serial.begin(9600);
}

void loop()
{
  currentBtnState = digitalRead(btn);
  if (currentBtnState == LOW)
  {
    if (btnState != HIGH)
    {
      btnState=HIGH;
      Serial.println("le switch a changer d'etat");

      Serial.println(currentBtnState);
      if (blinkOne == redLed)
      {
        blinkOne = greenLed;
        digitalWrite(redLed, LOW);
        Serial.println("vers led vert");
      }
      else if (blinkOne == greenLed)
      {
        blinkOne = blueLed;
        digitalWrite(greenLed, LOW);
        Serial.println("vers led blue");
      }
      else
      {
        blinkOne = redLed;
        digitalWrite(blueLed, LOW);
        Serial.println("vers led red");
      }
    }
  }
  else
  {
    btnState = LOW;
  }
  ///////////////////////////////////////////////////////////// pour un switch on off
  // currentBtnState=digitalRead(btn);
  // Serial.println(currentBtnState);
  // if(currentBtnState!=btnState){
  //   Serial.println("le switch a changer d'etat");
  //   btnState=currentBtnState;
  //   if(blinkOne==redLed){
  //     blinkOne=greenLed;
  //     digitalWrite(redLed,LOW);
  //   }else if(blinkOne==greenLed){
  //     blinkOne=blueLed;
  //     digitalWrite(greenLed,LOW);
  //   }else{
  //     blinkOne=redLed;
  //     digitalWrite(blueLed,LOW);
  //   }

  // }
  unsigned long currentTime = millis();
  if (currentTime - startTime >= myDelay)
  {
    startTime = currentTime;
    if (ledState == LOW)
    {
      ledState = HIGH;
    }
    else
    {
      ledState = LOW;
    }
    digitalWrite(blinkOne, ledState);
  }
}

