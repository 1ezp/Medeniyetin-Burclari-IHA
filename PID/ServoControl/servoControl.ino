// This sketch has been made by github.com/DIAMOND754
// Mainly this project is for controlling 2 servo's in order to hit a target

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

#include <Servo.h>                        // Servo
Servo wingServo;
// Servo tailServo;

int balancedWingServoValue = 90;     // Servo values
// int balancedTailServoValue = 90;

int x;                                    // Variables
int pushedByX;
int xAmmountChecker = 0;
// int y;
// int pushedByY;
// int yAmmountChecker = 0;


void setup(){

  wingServo.attach(16);          // Servo
  // tailServo.attach();

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

    balancedWingServoValue = 90;         // Reset servo values
    // balancedTailServoValue = 90;

    xAmmountChecker=0;
    // yAmmountChecker=0;

    assignRandomValue();
    Serial.println("----------Started----------");
  }


  if(x > 180){

    balancedWingServoValue-=5;
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

    balancedWingServoValue+=5;
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

  //   balancedTailServoValue+=5;

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

  //   balancedTailServoValue-=5;
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
  wingServo.write(balancedWingServoValue);
  // tailServo.write(balancedTailServoValue);

  Serial.print("X: ");
  Serial.println(x);
  Serial.print("Wing: ");
  Serial.println(balancedWingServoValue);
  // Serial.print("Y: ");
  // Serial.println(y);
  Serial.println("----------");
}

void assignRandomValue(){

  x = random(0, 361);
  // y = random(0, 241);
}
