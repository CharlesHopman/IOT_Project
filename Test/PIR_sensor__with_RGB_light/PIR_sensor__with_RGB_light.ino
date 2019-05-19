//Aquaponics System - IOT Project
//Charles Hopman

//PIR sensor with RGB light

//--------------------------------------PIR Sensor Light------------------------------------------

int pirSensor = 9;
int PIRred = 2;
int PIRgreen = 3;
int PIRblue = 4;

void PIRSensorLightSetup() {
  pinMode(pirSensor, INPUT);
  pinMode(PIRred, OUTPUT);
  pinMode(PIRgreen, OUTPUT);
  pinMode(PIRblue, OUTPUT);
}

void PIRSensorLightLoop() {
  int sensorValue = digitalRead(pirSensor);
  if (sensorValue == 1) {
    analogWrite(PIRred, random(0, 255));
    analogWrite(PIRgreen, random(0, 255));
    analogWrite(PIRblue, random(0, 255));
    delay(500);
  }
  else{
    analogWrite(PIRred, 0);
    analogWrite(PIRgreen, 0);
    analogWrite(PIRblue, 0);
  }
}
void setup() {
  // put your setup code here, to run once:
  PIRSensorLightSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  PIRSensorLightLoop();
}
