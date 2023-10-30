#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C LCD(0x27, 16, 2); // setup ecran

void setup()
{
  Serial.begin(9600);
  LCD.init();
  LCD.backlight();
  LCD.setCursor(1, 0);
  LCD.print("MESSAGE");
  LCD.setCursor(4, 1);
  LCD.print("PRINT");
  delay(1000);
  LCD.clear();
}

void loop()
{
  if (Serial.available() > 0)
  { // check msg

    char message_top[17];
    char message_bot[17];
    for (int i = 0; i < sizeof(message_top); i++)
    {
      message_top[i] = ' ';
      message_bot[i] = ' ';
    }
    Serial.readBytes(message_top, 16);
    message_top[16] = '\0';

    Serial.readBytes(message_bot, 16);
    message_bot[16] = '\0';
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print(message_top);
    LCD.setCursor(0, 1);
    LCD.print(message_bot);
    delay(500);
  }
}
