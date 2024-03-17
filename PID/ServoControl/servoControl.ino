// This sketch has been made by github.com/DIAMOND754
// Mainly this project is for controlling 2 servo's in order to hit a target

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

#include <Servo.h>                        // Servo
Servo wingServo;
// Servo tailServo;

#include <SoftwareSerial.h>               // SoftwareSerial for communication with arduino
SoftwareSerial unoSerial(5, 4);           // RX, TX

int balancedWingServoValue = 90;          // Servo values
// int balancedTailServoValue = 90;

int x;                                    // Variables
// int y;

bool shouldWriteServo = false;

// -------------------------------------------------------------------------
// ------------------------------Setup--------------------------------------

void setup(){

  wingServo.attach(16);                   // Servo
  // tailServo.attach();

  pinMode(LED_BUILTIN, OUTPUT);           // Pinmodes
  pinMode(15, OUTPUT);

  Serial.begin(9600);                     // Serial and I2C
  unoSerial.begin(9600);
}

// -------------------------------------------------------------------------
// -------------------------------Loop--------------------------------------

void loop(){

  if (unoSerial.available()) {            // When data available

    x = unoSerial.parseInt();

    shouldWriteServo = true;
    digitalWrite(15, HIGH);
  }
  else{

    shouldWriteServo = false;
    digitalWrite(15, LOW);

    balancedWingServoValue = 90;
    // balancedTailServoValue = 90;
  }

  if(x > 180){

    balancedWingServoValue-=5;
  }
  else if(x < 180){

    balancedWingServoValue+=5;
  }

  // if(y > 120){

  //   balancedTailServoValue+=5;
  // }
  // else if(y < 120){

  //   balancedTailServoValue-=5;
  // }

  // Keeping the values above 0 and under 180
  if(balancedWingServoValue <= 0){

    balancedWingServoValue = 0;
  }
  // if(balancedTailServoValue <= 0){

  //   balancedTailServoValue = 0;
  // }
  if(balancedWingServoValue >= 180){

    balancedWingServoValue = 180;
  }
  // if(balancedTailServoValue >= 180){

  //   balancedTailServoValue = 180;
  // }

  // Write the servo values
  if(shouldWriteServo){

    wingServo.write(balancedWingServoValue);
    // tailServo.write(balancedTailServoValue);
  }

  // Serial.print("X: ");
  // Serial.println(x);
  // Serial.print("Wing: ");
  // Serial.println(balancedWingServoValue);
  // // Serial.print("Y: ");
  // // Serial.println(y);
  // Serial.println("----------");
}
