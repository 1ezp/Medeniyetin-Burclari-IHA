// This sketch has been made by github.com/DIAMOND754
// Mainly this project is for controlling servo's in order to hit a target

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

#include <Servo.h>                        // Servo
Servo rightWingServo;
// Servo leftWingServo;
// Servo rightTailServo;
// Servo lefttTailServo;

int balancedRightWingServoValue = 90;     // Servo values
int balancedLeftWingServoValue = 90;
int balancedRightTailServoValue = 90;
int balancedLefttTailServoValue = 90;

int x;                                    // Variables
int pushedByX;
int xAmmountChecker = 0;
// int y;
// int pushedByY;
// int yAmmountChecker = 0;


void setup(){

  rightWingServo.attach(16);          // Servo
  // leftWingServo.attach();
  // rightTailServo.attach();
  // lefttTailServo.attach();

  pinMode(LED_BUILTIN, OUTPUT);       // Pinmodes

  Serial.begin(9600);                 // Serial

  // Random x,y values
  assignRandomValue();
}

void loop(){

  // When we reached the target
  if(x == 180){

    Serial.println("----------Finished----------");

    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);

    balancedRightWingServoValue = 90;         // Reset servo values
    balancedLeftWingServoValue = 90;
    balancedRightTailServoValue = 90;
    balancedLefttTailServoValue = 90;

    xAmmountChecker=0;
    // yAmmountChecker=0;

    assignRandomValue();
    Serial.println("----------Started----------");
  }


  if(x > 180){

    balancedLeftWingServoValue+=5;
    balancedRightWingServoValue-=5;
    if(xAmmountChecker == 10){

      pushedByX = random(1, 50);
      x = x - pushedByX;
      xAmmountChecker=0;
    }
    else{

      xAmmountChecker++;
    }
  }
  else if(x < 180){

    balancedLeftWingServoValue-=5;
    balancedRightWingServoValue+=5;
    if(xAmmountChecker == 10){

      pushedByX = random(1, 50);
      x = x + pushedByX;
      xAmmountChecker=0;
    }
    else{

      xAmmountChecker++;
    }
  }

  // if(y > 120){

  //   balancedLefttTailServoValue+=5;
  //   balancedRightTailServoValue+=5;

  //   if(yAmmountChecker == 10){

  //     pushedByY = random(1, 50){
  //     y = y - pushedByY;
  //     yAmmountChecker=0;
  //   }
  //   else{

  //     yAmmountChecker+=1
  //   }

  // }
  // else if(y < 120){

  //   balancedLefttTailServoValue-=5;
  //   balancedRightTailServoValue-=5;
  //   if(yAmmountChecker == 50){

  //     pushedByY = random(1, 10);
  //     y = y + pushedByY;
  //     yAmmountChecker=0;
  //   }
  //   else{
  //
  //     yAmmountChecker+=1
  //   }
  // }

  // Keeping the values above 0 and under 180
  if(balancedRightWingServoValue <= 0){

    balancedRightWingServoValue = 0;
  }
  if(balancedLeftWingServoValue <= 0){

    balancedLeftWingServoValue = 0;
  }
  if(balancedRightTailServoValue <= 0){

    balancedRightTailServoValue = 0;
  }
  if(balancedLefttTailServoValue <= 0){

    balancedLefttTailServoValue = 0;
  }
  if(balancedRightWingServoValue >= 180){

    balancedRightWingServoValue = 180;
  }
  if(balancedLeftWingServoValue >= 180){

    balancedLeftWingServoValue = 180;
  }
  if(balancedRightTailServoValue >= 180){

    balancedRightTailServoValue = 180;
  }
  if(balancedLefttTailServoValue >= 180){

    balancedLefttTailServoValue = 180;
  }

  // Write the servo values
  rightWingServo.write(balancedRightWingServoValue);
  // leftWingServo.write(balancedLeftWingServoValue);
  // rightTailServo.write(balancedRightTailServoValue);
  // leftTailServo.write(balancedLefttTailServoValue);

  Serial.print("X: ");
  Serial.println(x);
  Serial.print("Wing: ");
  Serial.println(balancedRightWingServoValue);
  // Serial.print("Y: ");
  // Serial.println(y);
  Serial.println("----------");
}

void assignRandomValue(){

  x = random(0, 361);
  // y = random(0, 241);
}
