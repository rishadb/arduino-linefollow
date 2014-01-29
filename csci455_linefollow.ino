#include <Servo.h>

typedef enum {LEFT, RIGHT, STRAIGHT} states;
states state;

const int rightAnalog = 1;              // Right analog pin
const int leftAnalog = 0;               // Left analog pin
const int rightDigital = 9;             // Right digital pin
const int leftDigital = 10;             // Left digital pin

const int leftBlackAnalogValue = 30;    // Left black analog value = 19...10
const int rightBlackAnalogValue = 70;   // Right black analog value = 88...

const int leftWhiteAnalogValue = 52;     // Left white abalog value = 62...55
const int rightWhiteAnalogValue = 82;   // Right white analog value = 119...100

// Turn left
const int lsStop = 91;                  // Left stop value
const int lsRight = 87;                 // Left servo value for right turn

// Turn right
const int rsStop = 90;                  // Right stop value
const int rsLeft = 93;                  // Right servo value for left turn

// Go straight
const float lsStr = 92.5;                   // Left servo value for straight
const float rsStr = 89.1;                   // Right servo value for straight

const int delayValue = 20;             // Delay value

Servo leftServo;                        // Left servo
Servo rightServo;                       // Right servo

void setup() {
  Serial.begin(115200);                   // Necessary to set up Serial port
  leftServo.attach(leftDigital);
  rightServo.attach(rightDigital);
}

void loop() {
  //testAnalogPin();
  movement();
  //turnLeft();
  //turnRight();
  //goStraight();
  //Stop(); 
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
    Stop();
    goStraight();
    state = STRAIGHT;
  }
  // Left sensor detects black, right sensor detects white
  else if (leftSensorIsBlack() && rightSensorIsWhite()) {
    Stop();
    turnLeft();
    state = LEFT;
  }
  // Left sensor detects white, right sensor detects black
  else if (leftSensorIsWhite() && rightSensorIsBlack()) {
    Stop();
    turnRight();
    state = RIGHT;
  }
 // Both left and right sensors detect white
  else {
    while (leftSensorIsWhite() && rightSensorIsWhite()) {        
      if (state == RIGHT) {
        Stop();
        turnLeft();
        state = LEFT;
      }
      else if (state == LEFT) {
        Stop();
        turnRight();
        state = RIGHT;
      }
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
