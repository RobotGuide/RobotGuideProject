#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>

typedef enum {
  RECEIVE_INSTRUCTION,
  RETURN_STATUS
} Instruction;

const char* ssid = "insert wifi name here";
const char* pass = "insert wifi password here";

const char* ip = "insert server ip here";
const int port = 3030;

WiFiClient client;

Instruction current = RECEIVE_INSTRUCTION;

void setup() {

  Serial.flush();
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  bool led = false;

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    led = !led;
    digitalWrite(LED_BUILTIN, led); // blink led
    delay(500);
  }

  Serial.println("connected with Wifi"); // remove later 
  digitalWrite(LED_BUILTIN, HIGH); // turn led off

  client.setDefaultNoDelay(true);

  // Todo: check connection  
  client.connect(ip, port);
  
  
  digitalWrite(LED_BUILTIN, LOW); // turn led on

  Serial.println("connected with server"); // remove later 
}

// connection fucntion 

void loop() {

  if (!client.connected())
  {
    client.stop();
    client.connect(ip, port);
    // Todo: do reconnect stuff 
  }

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