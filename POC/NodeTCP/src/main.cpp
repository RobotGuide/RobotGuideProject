#include <ESP8266WiFi.h>
#include <SPI.h>

const char* ssid = "AndroidAPa760";
const char* password = "rzbb0008";

void setup()
{
  Serial.begin(9600);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}


void loop()
{
  WiFiClient client;
  if (client.connect("192.168.43.110", 3030))
  {
    while (client.connected() || client.available())
    {
      if (client.available())
      {
        String line = client.readString();
        Serial.println(line);
        client.print("NAVS");
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(5000);
}