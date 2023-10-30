#include <SoftwareSerial.h>

SoftwareSerial ESP(10, 11); // TX, RX

String SSID = "ssid";
String PASS = "pass";

bool isSetup;
// AT+CWLAP  wifiscan
// AT+UART=9600,8,1,0,0 changer baud rate
// AT+CIPMUX=1, où le nombre correspond au type de connexion (0 – une seule connexion, 1 – plusieurs connexions).
// Le premier chiffre de la commande AT+CIPSERVER=1,80 est utilisé pour fermer le mode serveur (0) ou ouvrir le mode serveur (1)
// AT+CIFSR IP du module wifi ESP8266 ESP-01,
// AT+CIPSEND=0,5 envoyer 5b sur le canal 0
// AT+CIPCLOSE=0 fermer le canal pour faire apparaitre le msg
void setup()
{
    Serial.begin(9600);
    trySetup();
    if (isSetup)
    {
        ESP.begin(9600);
    }
    else
    {
        ESP.begin(115200);
        initESP();
    }

    pinMode(2, OUTPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    while (ESP.available())
    {
        String msg = ESP.readString();
        Serial.println(msg);
        int size = msg.length();
        String client = String(msg[0]);
        int indicePointVirgule = msg.indexOf("GET");
        int indice2point = msg.indexOf(':');
        String msg3 = msg.substring(indicePointVirgule + 3, indicePointVirgule + 3 + 6);
        String msg2 = msg.substring(indice2point + 1);
        Serial.println("///////////////-" + msg3 + "-//////////");
        delay(50);
        if (msg2 == "LED" || msg3 == " /LED1")
        {
            digitalWrite(2, HIGH);
            if (msg2 == "LED")
            {
                Hackclient(client, "HACK2");
            }
        }
        if (msg2 == "LEDOFF" || msg3 == " /LED0")
        {
            digitalWrite(2, LOW);
            if (msg2 == "LEDOFF")
            {
                Hackclient(client, "HACK2");
            }
        }
    }

    while (Serial.available())
    {
        String msg = Serial.readString();
        if (msg == "reset")
        {
            initESP();
        }
        else
        {
            ESP.println(msg);
        }
    }
}

void initESP()
{
    Serial.println("***** INIT ESP *****");
    commESP("AT+RESTORE", 4000);
    spacer();
    ESP.begin(115200);
    commESP("AT", 4000);
    spacer();
    commESP("AT+UART=9600,8,1,0,0", 4000);
    ESP.begin(9600);
    commESP("AT+CWMODE=1", 5000);
    spacer();
    commESP("AT+CWJAP=\"" + SSID + "\",\"" + PASS + "\"", 10000);
    spacer();
    commESP("AT+CIFSR", 1000);
    spacer();
    commESP("AT+CIPMUX=1", 1000);
    spacer();
    commESP("AT+CIPSERVER=1,80", 1000);
    spacer();
}
void trySetup()
{
    ESP.begin(9600);
    sendESP("AT");
    delay(1000);
    String msg=ESP.readString();
    Serial.println(msg);
    if (msg == NULL)
    {
        isSetup = false;
    }
    else
    {
        isSetup = true;
    }
}
void spacer()
{
    Serial.println("********************");
}

void sendESP(String cmd)
{
    ESP.println(cmd);
}

void recvESP(const int timeout)
{
    String resp = "";
    unsigned long time = millis();
    while ((time + timeout) > millis())
    {
        while (ESP.available())
        {
            char c = ESP.read();
            resp += c;
        }
    }
    Serial.print(resp);
}

void commESP(String cmd, const int timeout)
{
    sendESP(cmd);
    recvESP(timeout);
}

void Hackclient(String client, String hack)
{
    // String numClient = static_cast<String>(client);

    String lenghtHack = static_cast<String>(hack.length());
    sendESP("AT+CIPSEND=" + client + "," + lenghtHack);
    delay(500);
    sendESP(hack);
    delay(500);
    sendESP("AT+CIPCLOSE=" + client);
}
