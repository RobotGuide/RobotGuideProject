const int DRIVER_ENA_PIN = 10;
const int DRIVER_IN1_PIN = 9;
const int DRIVER_IN2_PIN = 8;
const int DRIVER_ENB_PIN = 11;
const int DRIVER_IN3_PIN = 12;
const int DRIVER_IN4_PIN = 13;

const byte minmotor = 75;
const byte maxmotor = 255;

byte currentmotor = minmotor;

bool directionmotor = true;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(DRIVER_ENA_PIN, OUTPUT);
  pinMode(DRIVER_IN1_PIN, OUTPUT);
  pinMode(DRIVER_IN2_PIN, OUTPUT);

  pinMode(DRIVER_ENB_PIN, OUTPUT);
  pinMode(DRIVER_IN3_PIN, OUTPUT);
  pinMode(DRIVER_IN4_PIN, OUTPUT);

  digitalWrite(DRIVER_IN1_PIN, HIGH);
  digitalWrite(DRIVER_IN2_PIN, LOW);

  digitalWrite(DRIVER_IN3_PIN, LOW);
  digitalWrite(DRIVER_IN4_PIN, HIGH);
  
  analogWrite(DRIVER_ENA_PIN, currentmotor);
  analogWrite(DRIVER_ENB_PIN, currentmotor);
}

void loop()
{
  currentmotor += (directionmotor) ? 10 : -10;

  if(currentmotor > maxmotor - 1)
  {
    directionmotor = false;
  }
  else if(currentmotor < minmotor + 1)
  {
    directionmotor = true;
  }

  Serial.println(currentmotor);

  analogWrite(DRIVER_ENA_PIN, currentmotor);
  analogWrite(DRIVER_ENB_PIN, currentmotor);
  delay(750);
//  // put your main code here, to run repeatedly:
//  if(Serial.available() > 0)
//  {
//    int arg1 = Serial.readStringUntil(' ').toInt();
//    int arg2 = Serial.readStringUntil(' ').toInt();
//    byte arg3 = Serial.readStringUntil('\n').toInt();
//
//    Serial.println("---------------------");
//    Serial.println(arg1);
//    Serial.println(arg2);
//    Serial.println(arg3);
//    Serial.println("---------------------");
//
//    if(arg1 == 1)
//    {
//      if(arg2 == 1)
//      {
//        digitalWrite(DRIVER_IN1_PIN, LOW);
//        digitalWrite(DRIVER_IN2_PIN, HIGH);
//      }
//      else if(arg2 == -1)
//      {
//        digitalWrite(DRIVER_IN1_PIN, HIGH);
//        digitalWrite(DRIVER_IN2_PIN, LOW);
//      }
//      analogWrite(DRIVER_ENA_PIN, arg3);
//    }
//    else if(arg1 == 2)
//    {
//      if(arg2 == 1)
//      {
//        digitalWrite(DRIVER_IN3_PIN, LOW);
//        digitalWrite(DRIVER_IN4_PIN, HIGH);
//      }
//      else if(arg2 == -1)
//      {
//        digitalWrite(DRIVER_IN3_PIN, HIGH);
//        digitalWrite(DRIVER_IN4_PIN, LOW);
//      }
//      analogWrite(DRIVER_ENB_PIN, arg3);
//    }
//  }
}
