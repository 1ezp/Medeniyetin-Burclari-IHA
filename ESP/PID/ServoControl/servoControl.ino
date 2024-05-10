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

bool shouldWriteServo = false;            // For safety

#define setpointX 180                      // PID values
// #define setpointY 120
double outputX;
// double outputY;

#define KP 5.0
#define KI 0.8
#define KD 2.0

double prevErrorX = 0;                     // PID variables
double integralX = 0;
double prevErrorY = 0;
double integralY = 0;

// -------------------------------------------------------------------------
// ------------------------------Setup--------------------------------------

void setup(){

  wingServo.attach(13);                   // Servo
  // tailServo.attach();

  pinMode(LED_BUILTIN, OUTPUT);           // Pinmodes
  pinMode(15, OUTPUT);

  Serial.begin(9600);                     // Serial and I2C
  unoSerial.begin(9600);
}

// -------------------------------------------------------------------------
// -------------------------------Loop--------------------------------------

void loop(){

// ---------------------Read---------------------

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

    wingServo.write(balancedWingServoValue);
    // tailServo.write(balancedTailServoValue);

    prevErrorX = 0;
    integralX = 0;
    prevErrorY = 0;
    integralY = 0;
  }
// ---------------------Calculate the PID---------------------

  if(shouldWriteServo){
    calculatePIDForX();
    // calculatePIDForY();
  }

// ---------------------Servo---------------------

  // Write the servo values
  if(shouldWriteServo){

    wingServo.write(balancedWingServoValue);
    // tailServo.write(balancedTailServoValue);
  }

// ---------------------Debugging---------------------

  Serial.print("   X: ");
  Serial.print(x);
  Serial.print("   Servo: ");
  Serial.println(balancedWingServoValue);
  // // Serial.print("Y: ");
  // // Serial.println(y);
  // Serial.println("----------");

}

// -------------------------------------------------------------------------
// -------------------------------XPID--------------------------------------

void calculatePIDForX(){

  // Calculate error
  double error = setpointX - x;

  // Calculate integral
  integralX += error;

  // Calculate derivative
  double derivative = error - prevErrorX;

  // Calculate control signal
  outputX = KP * error + KI * integralX + KD * derivative;

  // Update previous error
  prevErrorX = error;

  // Adjust values for servo
  outputX = constrain(outputX, -180, 180);

  // Calculate servo angle
  balancedWingServoValue = balancedWingServoValue + outputX;

  // Ensure servo angle is within bounds
  balancedWingServoValue = constrain(balancedWingServoValue, 0, 180);

  Serial.print("Outout: ");
  Serial.print(outputX);
}

// -------------------------------------------------------------------------
// -------------------------------YPID--------------------------------------

// void calculatePIDForY(){

//   // Calculate error
//   double error = setpointY - y;

//   // Calculate integral
//   integralY += error;

//   // Calculate derivative
//   double derivative = error - prevErrorY;

//   // Calculate control signal
//   outputY = KP * error + KI * integralY + KD * derivative;

//   // Update previous error
//   prevErrorY = error;

//   // Adjust values for servo
//   outputY = constrain(outputY, -180, 180);

//   // Calculate servo angle
//   balancedTailServoValue = balancedTailServoValue + outputY;

//   // Ensure servo angle is within bounds
//   balancedTailServoValue = constrain(balancedTailServoValue, 0, 180);
// }
