// This sketch has been made by github.com/DIAMOND754
// This sketch is going to emulate an AI camera and sends the location of a target using (x, y) coordinates

// Currently, this sketch is going to work with 1 potentiometer and is going to send this data over I2C

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

#include <SoftwareSerial.h>
SoftwareSerial espSerial(A2, A3);

const int potentiometerPin = A0;
const int buttonPin = A1;
int bilgi;

void setup(){

  pinMode(potentiometerPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  espSerial.begin(9600);
}

void loop(){

  bilgi = analogRead(potentiometerPin);
  bilgi = map(bilgi, 0, 1023, 0, 360);
  if(digitalRead(buttonPin) == 0){

    espSerial.println(bilgi);
  }
  delay(100);
}
