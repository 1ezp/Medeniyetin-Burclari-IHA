// This sketch has been made by github.com/DIAMOND754
// This sketch is going to emulate an AI camera and sends the location of a target using (x, y) coordinates

// Currently, thhis sketch is going to work with 1 potentiometer and is going to send this data over I2C

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

const int potentiometerPin = A5;
int bilgi;

void setup(){

  pinMode(potentiometerPin, INPUT);
  Serial.begin(9600);
}

void loop(){

  bilgi = analogRead(potentiometerPin);
  bilgi = map(bilgi, 0, 1023, 0, 360);
  Serial.println(bilgi);
  delay(100);
}
