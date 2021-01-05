#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>

typedef enum {
  RECEIVE_INSTRUCTION,
  RETURN_STATUS
} Instruction;

const char* ssid = "Samsung Galaxy S10 Plus Hotspot"; //insert wifi name here
const char* pass = ""; //insert wifi password here

const char* ip = ""; //insert server ip here
const int port = 3030;

WiFiClient client;

Instruction current = RECEIVE_INSTRUCTION;

void ConnectWifi();
void ConnectServer();


// Connecting to Wi-Fi: LED Blink fast
// Conneting to Server: LED Blink slower
// Connected to server and wifi: LED On
void setup() {
  Serial.flush();
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.begin(ssid, pass);
  digitalWrite(LED_BUILTIN, HIGH); // turn led off
  client.setDefaultNoDelay(true);
}

void loop() {
  ConnectWifi();
  ConnectServer();

  digitalWrite(LED_BUILTIN, LOW); // turn led on

  switch (current)
  {
  case RECEIVE_INSTRUCTION:
    if (client.available())
    {
      String line = client.readStringUntil('\n');
      Serial.print(line);
      Serial.print('\n');
    }

    current = RETURN_STATUS;
    break;

  case RETURN_STATUS:
    if (Serial.available())
    {
      String line =  Serial.readStringUntil('\n');
      client.print(line);
    }

    current = RECEIVE_INSTRUCTION;
    break;
  
  default:
    break;
  }
}

void ConnectWifi()
{
  bool led = false;
  while (WiFi.status() != WL_CONNECTED)
  {
    led = !led;
    digitalWrite(LED_BUILTIN, led); // blink led
    delay(100);
  }
}

void ConnectServer()
{
  bool led = false;
  if (!client.connected())
  {
    client.stop();
    client.connect(ip, port); // CLOSED -> ESTABLISHED
    unsigned long long time = millis() + 5000;
    while (client.status() != ESTABLISHED)
    {
      led = !led;
      digitalWrite(LED_BUILTIN, led);
      delay(300);
      if (millis() >= time)
      {
        break;
      }
    }
  }
}