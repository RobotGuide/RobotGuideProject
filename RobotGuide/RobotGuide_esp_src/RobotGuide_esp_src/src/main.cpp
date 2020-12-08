#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>


const char* ssid = "insert wifi name here";
const char* pass = "insert wifi password here";
const char* ip = "insert server ip here";
const int port = 3030;

void setup() {

  Serial.flush();
  Serial.begin(9600);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // use for testing communication
  WiFiClient client;
  client.setDefaultNoDelay(true);
  if (client.connect(ip, port))
  {
    digitalWrite(LED_BUILTIN, LOW);
    while (client.connected() || client.available())
    {
      if (client.available())
      {
       
        String line = client.readStringUntil('\n');

        line += '\n';

        Serial.print(line);
        
      }
    }
    client.stop();
  }
  else
  {
    client.stop();
  }
}