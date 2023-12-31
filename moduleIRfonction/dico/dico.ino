#include <IRremote.hpp>

#define IR_RECEIVE_PIN 10

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop()
{
  if (IrReceiver.decode())
  {
    uint16_t command = IrReceiver.decodedIRData.command;
    Serial.println(command);
    delay(100); // wait a bit
    IrReceiver.resume();

    switch (command)
    {
    case 69:
      Serial.println("CH-");
      break;
    case 70:
      Serial.println("CH");
      break;
    case 71:
      Serial.println("CH+");
      break;

    case 67:
      Serial.println("PLAY/PAUSE");
      break;

    case 64:
      Serial.println("NEXT");
      break;
    case 68:
      Serial.println("PREV");
      break;
    case 21:
      Serial.println("VOL+");
      break;
    case 7:
      Serial.println("VOL-");
      break;
      case 9:
      Serial.println("EQ");
      break;
      case 22:
      Serial.println("0");
      break;
      case 25:
      Serial.println("100+");
      break;
      case 13:
      Serial.println("200+");
      break;
      case 12:
      Serial.println("1");
      break;
      case 24:
      Serial.println("2");
      break;
      case 94:
      Serial.println("3");
      break;
      case 8:
      Serial.println("4");
      break;
      case 28:
      Serial.println("5");
      break;
      case 90:
      Serial.println("6");
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