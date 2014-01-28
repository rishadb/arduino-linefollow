#include <Servo.h>

const int rightAnalog = 0;              // Right analog pin
const int leftAnalog = 1;               // Left analog pin
const int rightDigital = 9;             // Right digital pin
const int leftDigital = 10;             // Left digital pin

const int leftBlackAnalogValue = 36;    // Left black analog value
const int rightBlackAnalogValue = 64;   // Right black analog value

const int leftWhiteAnalogValue = 95;     // Left white abalog value
const int rightWhiteAnalogValue = 96;    // Right white analog value

// Turn left
const int lsStop = 91;                  // Left stop value
const int lsRight = 87;                 // Left servo value for right turn

// Turn right
const int rsStop = 91;                  // Right stop value
const int rsLeft = 93;                  // Right servo value for left turn

// Go straight
const int lsStr = 93;                   // Left servo value for straight
const int rsStr = 89;                   // Right servo value for straight

const int delayValue = 100;             // Delay value

Servo leftServo;                        // Left servo
Servo rightServo;                       // Right servo

void setup() {
  Serial.begin(9600);                   // Necessary to set up Serial port
  leftServo.attach(leftDigital);
  rightServo.attach(rightDigital);
}

void loop() {
  testAnalogPin();
  movement();
  //turnLeft();
  //turnRight();  
}

void turnLeft() {
  leftServo.write(lsStop);
  rightServo.write(lsRight);
  delay(delayValue);
}

void turnRight() {
  leftServo.write(rsLeft);
  rightServo.write(rsStop);
  delay(delayValue);
}

void goStraight() {
  leftServo.write(lsStr);  
  rightServo.write(rsStr);
  delay(delayValue);
}

void Stop() {
  leftServo.write(lsStop);
  rightServo.write(rsStop);
  delay(delayValue);
}

void movement() {
  // Both left and right sensors detect black
  if (leftSensorIsBlack() && rightSensorIsBlack()) {
    goStraight();
  }
  // Left sensor detects black, right sensor detects white
  else if (leftSensorIsBlack() && rightSensorIsWhite()) {
    Stop(); 
    turnLeft();
  }
  // Left sensor detects white, right sensor detects black
  else if (leftSensorIsWhite() && rightSensorIsBlack()) {
    Stop(); 
    turnRight();
  }
 // Both left and right sensors detect white
  else {
    Stop();
    while (leftSensorIsWhite() && rightSensorIsWhite()) {
      // if it doesn't find black in _____ then go right
      turnLeft();
      turnRight();
    }
  }
}

boolean leftSensorIsBlack() {
  if (analogRead(leftAnalog) < leftBlackAnalogValue) {
    return true;
  }
  else {
    return false;
  }
}

boolean rightSensorIsBlack() {
  if (analogRead(rightAnalog) < rightBlackAnalogValue) {
    return true;
  }
  else {
    return false;
  }
}

boolean leftSensorIsWhite() {
  if (analogRead(leftAnalog) > leftWhiteAnalogValue) {
    return true;
  }
  else {
    return false;
  }
}

boolean rightSensorIsWhite() {
  if (analogRead(rightAnalog) > rightWhiteAnalogValue) {
    return true;
  }
  else {
    return false;
  }
}

void testAnalogPin() {
  // Left sensor analog output
  Serial.print(analogRead(leftAnalog));
  Serial.print(' ');
  // Right sensor analog output
  Serial.print(analogRead(rightAnalog));
  Serial.print(' ');
  Serial.println();
  delay(1500);                      // Set the number to change frequency of readings.
}
