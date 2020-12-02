#include <Arduino.h>
// #include <SoftwareSerial.h>
// #include <ESP8266WiFi.h>
#include <SPI.h>

#include "robotguide/Communication/ApplicationLayer/Instruction/Instruction.h"
#include "robotguide/Communication/ApplicationLayer/Lexer/Lexer.h"
#include "robotguide/Communication/ApplicationLayer/Parser/Parser.h"
#include <iostream>
#define BUFFER_LENGTH 50


// LED On: Connected to wifi hotspot
// LED Blink: Connected to server 

typedef enum {
  WAIT_SERVER,
  SEND_SERVER,
  WAIT_RESPONSE,
  SEND_INSTRUCTION 
} Instruction;


Instruction inState = SEND_INSTRUCTION;

unsigned int instructionStep = 0;
String serverMsg[] = {"FORN 50\n", "TURN 90\n", "FORN 50\n", "TURN 90\n", "FORN 50\n", "TURN 90\n", "FORN 50\n", "TURN 90\n"}; // msg from server

char buffer[BUFFER_LENGTH]; // buffer, msg from uno 

// change this
const char *ssid = "Samsung Galaxy S10 Plus Hotspot";
const char *pass = "hei28!&3ja9";
void LexerTest();

void setup() {
  auto lexer = robotguide::com::al::Lexer();
  auto parser = robotguide::com::al::Parser();
  Serial.flush();
  Serial.begin(9600);

  std::cout << "AJAJA" << std::endl;
  LexerTest();
  WiFi.begin(ssid, pass);
  Serial.printf("Connecting to %s ", ssid);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected");

  pinMode(LED_BUILTIN, OUTPUT);

} 

void LexerTest()
{
  auto lexer = robotguide::com::al::Lexer();
  auto parser = robotguide::com::al::Parser();



  while(true)
  {
    std::string input = "MOVE 1.0 3.0 -3.4";

    auto tokenStream = lexer.GetTokenStream(input);
    std::cout << tokenStream.ToString() << std::endl;



    auto instructionStream = parser.GetInstructionStream(tokenStream);
    std::cout << instructionStream.ToString() << std::endl;

  }
}

void loop() {
  // use for testing communication
  WiFiClient client;
  client.setDefaultNoDelay(true);
  if (client.connect("192.168.43.142", 3030))
  {
    while (client.connected() || client.available())
    {
      if (client.available())
      {
        unsigned long time = micros();
        String line = client.readStringUntil('n');
        unsigned long a = micros() - time;
        client.print(line + "a");
        Serial.println(a);
        // Serial.println(line);
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("[connection failed!]");
    client.stop();
  }
  // end
  

  switch (inState)
  {
  case SEND_INSTRUCTION:
    {
      Serial.print(serverMsg[instructionStep]);
      instructionStep++;
      inState = WAIT_RESPONSE;
      break;
    }

  case WAIT_RESPONSE:
    {
      while(Serial.available()) 
      {
        memset(buffer, ' ', BUFFER_LENGTH);
        Serial.readBytesUntil('\n', buffer, BUFFER_LENGTH);
        char* cmd = strtok(buffer, " ");
        if(strcmp(cmd, "NAVS") == 0)
        {
          inState = instructionStep >= serverMsg->length()? WAIT_SERVER: SEND_INSTRUCTION;
        }
        else if (strcmp(cmd, "NAVF") == 0)
        {
          inState = SEND_SERVER;
        }
      } //while-loop
      
      break;
    }
  
  case WAIT_SERVER:
    // wait for new instruction from server
    {

    }
    break;

  case SEND_SERVER:
    // send message to server
    inState = WAIT_SERVER;
    break;
  }
}

