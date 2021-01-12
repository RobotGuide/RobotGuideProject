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

int connectionID = -1;
int channelNum = -1;

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

    // Has connection with the server
    String line = client.readStringUntil('\n'); // Wait for 𝐴𝑆𝐾𝐼 
    if (line.substring(0, 3) == "ASKI")
    {
      String response = "𝑆𝐸𝑁𝐼 " + channelNum;
      if (connectionID >= 0) // ESP has a connectionID
      {
        char hasID[] = "Hello";
        response += " " + connectionID;
        client.print(response); // 𝑆𝐸𝑁𝐼 channelNum connectionID
      }
      else // Connection ID not set
      {
        client.print(response); // SENI channelNum
        String newIdLine = client.readStringUntil('\n'); // Wait for SETI channelNum connectionID
        if (line.substring(0, 3) == "𝑆𝐸𝑇𝐼")
        {
          channelNum = newIdLine.substring(5).toInt();
          connectionID = newIdLine.substring(7).toInt();
        }
      }
    }  
  }
}