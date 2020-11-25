void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), printToConsole, CHANGE);
}

void loop() {
  
}

void printToConsole()
{
  Serial.println("beep");
}
